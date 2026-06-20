/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2017-20 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
 *                                        ,=mm=§M ]=4 yJKA"/-Nsaj  "Bw,==,,
 * This file is part of Mandelbulber.    §R.r= jw",M  Km .mM  FW ",§=ß., ,TN
 *                                     ,4R =%["w[N=7]J '"5=],""]]M,w,-; T=]M
 * Mandelbulber is free software:     §R.ß~-Q/M=,=5"v"]=Qf,'§"M= =,M.§ Rz]M"Kw
 * you can redistribute it and/or     §w "xDY.J ' -"m=====WeC=\ ""%""y=%"]"" §
 * modify it under the terms of the    "§M=M =D=4"N #"%==A%p M§ M6  R' #"=~.4M
 * GNU General Public License as        §W =, ][T"]C  §  § '§ e===~ U  !§[Z ]N
 * published by the                    4M",,Jm=,"=e~  §  §  j]]""N  BmM"py=ßM
 * Free Software Foundation,          ]§ T,M=& 'YmMMpM9MMM%=w=,,=MT]M m§;'§,
 * either version 3 of the License,    TWw [.j"5=~N[=§%=%W,T ]R,"=="Y[LFT ]N
 * or (at your option)                   TW=,-#"%=;[  =Q:["V""  ],,M.m == ]N
 * any later version.                      J§"mr"] ,=,," =="""J]= M"M"]==ß"
 *                                          §= "=C=4 §"eM "=B:m|4"]#F,§~
 * Mandelbulber is distributed in            "9w=,,]w em%wJ '"~" ,=,,ß"
 * the hope that it will be useful,                 . "K=  ,=RMMMßM"""
 * but WITHOUT ANY WARRANTY;                            .'''
 * without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with Mandelbulber. If not, see <http://www.gnu.org/licenses/>.
 *
 * ###########################################################################
 *
 * Authors: Krzysztof Marczak (buddhi1980@gmail.com)
 *
 * SSAO shader function optimized for opencl
 */

float3 SSAOBuildTangent(float3 n)
{
	float3 t = (fabs(n.z) < 0.999f) ? (float3)(0.0f, 0.0f, 1.0f) : (float3)(0.0f, 1.0f, 0.0f);
	return normalize(cross(t, n));
}

float SSAO_HemisphereOcclusion(float3 normal, float2 scr_f, float z, float aspectRatio,
	float scaleFactor, float quality, float fov, int width, int height, int randomSeed,
	__global float *zBuffer, sParamsSSAO p)
{
	float3 tangent = SSAOBuildTangent(normal);
	float3 bitangent = cross(normal, tangent);
	float occlusion = 0.0f;
	const int samples = max(p.sample_count, 4);
	const float radius = scaleFactor * p.radius_scale;
	const float bias = 0.002f * z;

	for (int s = 0; s < samples; s++)
	{
		float angle = (float)s / (float)samples * M_PI_F * 2.0f;
		if (p.random_mode)
			angle += Random(62831 / samples, &randomSeed) / 10000.0f;

		float2 dir2 = (float2)(cos(angle), sin(angle));
		float2 offset = tangent.xy * dir2.x + bitangent.xy * dir2.y;
		float2 v = scr_f + offset * radius * (float)(s + 1);
		int vx = (int)v.x;
		int vy = (int)v.y;
		if (vx < 0 || vy < 0 || vx >= width || vy >= height) continue;
		if (vx == (int)scr_f.x && vy == (int)scr_f.y) continue;

		float z2 = zBuffer[vx + vy * width];
		if (z2 > 1.0e5f) continue;

		float dz = z2 - z - bias;
		if (dz < 0.0f) occlusion += 1.0f;
	}

	return 1.0f - occlusion / (float)samples;
}

//------------------ MAIN RENDER FUNCTION --------------------
kernel void SSAO(__global float *zBuffer, __global float4 *normalBuffer,
	__global float *sineCosineBuffer, __global float *out, sParamsSSAO p)
{
	const unsigned int i = get_global_id(0);
	const int2 scr = (int2){i % p.width, i / p.width};
	const float2 scr_f = convert_float2(scr);

	float scaleFactor = (float)p.width / (p.quality * p.quality) / 2.0f;
	float aspectRatio = (float)p.width / p.height;

	float z = zBuffer[i];
	float totalAmbient = 0.0f;
	float quality = p.quality;

	if (z < 1.0e5f)
	{
		float2 scr2;
		scr2.x = ((float)scr.x / p.width - 0.5f) * aspectRatio;
		scr2.y = ((float)scr.y / p.height - 0.5f);
		scr2 *= z * p.fov;

		float3 normal = 0.0f;
		bool useNormals = false;
		if (p.use_normal_buffer && normalBuffer != 0)
		{
			normal = normalBuffer[i].xyz;
			if (dot(normal, normal) > 0.01f)
			{
				normal = normalize(normal);
				useNormals = true;
			}
		}

		if (useNormals)
		{
			int randomSeed = i;
			if (p.random_mode)
			{
				for (int r = 0; r < 3; r++)
					randomSeed = RandomInt(&randomSeed);
			}
			totalAmbient = SSAO_HemisphereOcclusion(normal, scr_f, z, aspectRatio, scaleFactor,
				quality, p.fov, p.width, p.height, randomSeed, zBuffer, p);
		}
		else
		{
			float ambient = 0.0f;
			float angleStep = M_PI_F * 2.0f / quality;
			int maxRandom = 62831 / quality;
			int randomSeed = i;

			if (p.random_mode)
			{
				for (int r = 0; r < 3; r++)
					randomSeed = RandomInt(&randomSeed);
			}

			float rRandom = 1.0f;
			if (p.random_mode) rRandom = 0.5f + Random(65536, &randomSeed) / 65536.0f;

			int rayCount = 0;

			for (int angleIndex = 0; angleIndex < quality; angleIndex++)
			{
				float angle = angleIndex;
				float2 dir;
				if (p.random_mode)
				{
					angle = angleStep * angleIndex + Random(maxRandom, &randomSeed) / 10000.0f;
					dir = (float2){cos(angle), sin(angle)};
				}
				else
				{
					dir = (float2){sineCosineBuffer[(int)angle + p.quality],
						sineCosineBuffer[(int)angle]};
				}
				float maxDiff = -1e10f;

				bool wasRay = false;
				for (float r = 1.0f; r < quality; r += rRandom)
				{
					float rr = r * r * scaleFactor;
					float2 v = scr_f + rr * dir;

					if (((int)v.x == scr.x) && ((int)v.y == scr.y)) continue;
					if (v.x < 0 || v.x > p.width - 1 || v.y < 0 || v.y > p.height - 1) continue;

					wasRay = true;

					float z2 = zBuffer[(int)v.x + (int)v.y * p.width];
					float2 v2;
					v2.x = (v.x / p.width - 0.5f) * aspectRatio;
					v2.y = (v.y / p.height - 0.5f);
					v2 *= z2 * p.fov;

					float dv = distance(scr2, v2);
					float dz = z2 - z;
					float diff = -dz / dv;

					maxDiff = max(maxDiff, diff);
				}
				float maxAngle = atan(maxDiff);
				if (wasRay)
				{
					ambient += -maxAngle / M_PI_F + 0.5f;
					rayCount++;
				}
			}

			if (rayCount > 0) totalAmbient = ambient / rayCount;
		}

		totalAmbient = max(totalAmbient, 0.0f);
	}
	out[i] = totalAmbient;
}
