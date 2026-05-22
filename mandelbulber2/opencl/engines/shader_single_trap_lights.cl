/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2014-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
 *                                        ,=mm=§M ]=4 yJKA"/-Nsaj  "Bw,==,,
 * This file is part of Mandelbulber.    §R.r= jw",M  Km .mM  FW ",§=ß., ,TN
 *                                     ,4R =%["w[N=7]J '"5=],","]]M,w,-; T=]M
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
 * Single Trap Lights — OpenCL shader
 */

float SingleTrapLightDistanceCl(float3 point, __global const sSingleTrapLightLayerCl *layer, float animSize)
{
	float3 delta = point - layer->position.xyz;
	delta = Matrix33MulFloat3(layer->mRotRotation, delta);

	float dist = 0.0f;
	switch (layer->shape)
	{
		case 0: // point
			dist = length(delta) - animSize;
			break;
		case 1: // line
			dist = length(delta.yz) - animSize;
			break;
		case 2: // circle
		{
			float lengthYZ = length(delta.yz) - animSize;
			dist = length((float2)(lengthYZ, delta.x));
			break;
		}
		case 3: // square
		{
			float dy = max(fabs(fabs(delta.y) - animSize), fabs(delta.z) - animSize);
			float dz = max(fabs(fabs(delta.z) - animSize), fabs(delta.y) - animSize);
			float deltaRect = min(dy, dz);
			dist = length((float2)(deltaRect, delta.x));
			break;
		}
		case 4: // sphere
		{
			dist = length(delta) - animSize;
			break;
		}
		case 5: // cube
		{
			float size = animSize;
			float dy_x = max(fabs(fabs(delta.y) - size), fabs(delta.z) - size);
			float dz_x = max(fabs(fabs(delta.z) - size), fabs(delta.y) - size);
			float dx_z = max(fabs(fabs(delta.y) - size), fabs(delta.x) - size);
			float deltaRectYZ = min(dy_x, dz_x);
			float distYZ = length((float2)(deltaRectYZ, fabs(fabs(delta.x) - size)));
			float distXZ = length((float2)(dx_z, fabs(fabs(delta.z) - size)));
			dist = min(distYZ, distXZ);
			break;
		}
		case 6: // torus
		{
			float q = length(delta.yz) - animSize;
			dist = length((float2)(q, delta.x)) - layer->size2;
			break;
		}
		case 7: // capsule
		{
			float3 a = (float3)(0.0f, -animSize, 0.0f);
			float3 b = (float3)(0.0f, animSize, 0.0f);
			float3 pa = delta - a;
			float3 ba = b - a;
			float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0f, 1.0f);
			dist = length(pa - ba * h) - layer->size2;
			break;
		}
		case 8: // ring
		{
			float l = length(delta.yz);
			dist = fabs(l - animSize) - layer->size2;
			break;
		}
		case 9: // ellipse
		{
			float k = sqrt((delta.y * delta.y) / (animSize * animSize) + (delta.z * delta.z) / (layer->size2 * layer->size2));
			if (k < 1e-10f) k = 1e-10f;
			dist = length((float2)(delta.y, delta.z)) / k - animSize;
			break;
		}
		case 10: // cross
		{
			float sx = animSize;
			float sy = layer->size2;
			float sz = layer->size2;
			float d1 = length(delta.yz) - sy;
			d1 = length((float2)(d1, delta.x)) - sx;
			float d2 = length(delta.xz) - sz;
			d2 = length((float2)(d2, delta.y)) - sy;
			float d3 = length(delta.xy) - sx;
			d3 = length((float2)(d3, delta.z)) - sz;
			dist = min(min(d1, d2), d3);
			break;
		}
		case 11: // cylinder
		{
			float d1 = length(delta.yz) - animSize;
			float d2 = fabs(delta.x) - layer->size2;
			float dx = max(d1, 0.0f);
			float dy = max(d2, 0.0f);
			dist = sqrt(dx * dx + dy * dy) + min(max(d1, d2), 0.0f);
			break;
		}
		case 12: // plane
		{
			dist = fabs(delta.x) - animSize;
			break;
		}
		case 13: // disc
		{
			float l = length(delta.yz);
			float d1 = l - animSize;
			float d2 = fabs(delta.x) - layer->size2;
			float dx = max(d1, 0.0f);
			float dy = max(d2, 0.0f);
			dist = sqrt(dx * dx + dy * dy) + min(max(d1, d2), 0.0f);
			break;
		}
		case 14: // cone
		{
			float2 q = (float2)(length(delta.yz), delta.x);
			float2 tip = (float2)(0.0f, -animSize);
			float2 base = (float2)(layer->size2, animSize); // size=base radius, size2=height in CPU; here animSize used for base radius
			float2 cb = tip - base;
			float h = clamp(dot(q - base, cb) / dot(cb, cb), 0.0f, 1.0f);
			dist = length(q - base - cb * h);
			break;
		}
		case 15: // hexagon
		{
			const float k = 1.732050807f;
			float2 p = (float2)(fabs(delta.z), fabs(delta.y));
			float d2 = max(p.x * k + p.y * 0.5f, p.y) - animSize;
			float dx = fabs(delta.x) - layer->size2;
			float dOut = length(max((float2)(d2, dx), 0.0f));
			float dIn = min(max(d2, dx), 0.0f);
			dist = dOut + dIn;
			break;
		}
		case 16: // triangle
		{
			const float k = 1.732050807f;
			float2 p = (float2)(fabs(delta.z), delta.y);
			float d2 = max(p.x * k + p.y, -p.y + p.x * k) * 0.5f - animSize;
			float dx = fabs(delta.x) - layer->size2;
			float dOut = length(max((float2)(d2, dx), 0.0f));
			float dIn = min(max(d2, dx), 0.0f);
			dist = dOut + dIn;
			break;
		}
		case 17: // rounded box
		{
			float3 q = fabs(delta) - animSize + layer->size2;
			dist = length(max(q, 0.0f)) + min(max(q.x, max(q.y, q.z)), 0.0f) - layer->size2;
			break;
		}
		case 18: // diamond (octahedron)
		{
			dist = (fabs(delta.x) + fabs(delta.y) + fabs(delta.z) - animSize) / 1.732050807f;
			break;
		}
		case 19: // hollow sphere
		{
			dist = fabs(length(delta) - animSize);
			break;
		}
		case 20: // hollow cube
		{
			float3 q = fabs(delta) - animSize;
			dist = fabs(length(max(q, 0.0f)) + min(max(q.x, max(q.y, q.z)), 0.0f));
			break;
		}
		case 21: // ellipsoid
		{
			float3 r = (float3)((animSize + layer->size2) * 0.5f, animSize, layer->size2);
			float3 p = delta / r;
			dist = (length(p) - 1.0f) * min(r.x, min(r.y, r.z));
			break;
		}
		case 22: // superellipsoid
		{
			float3 r = (float3)((animSize + layer->size2) * 0.5f, animSize, layer->size2);
			float n = 4.0f;
			dist = pow(pow(fabs(delta.x / r.x), n) + pow(fabs(delta.y / r.y), n)
						 + pow(fabs(delta.z / r.z), n), 1.0f / n) - 1.0f;
			break;
		}
		case 23: // star 5
		{
			float angle = atan2(delta.z, delta.y);
			float r = length((float2)(delta.y, delta.z));
			float starR = animSize * (0.5f + 0.5f * cos(5.0f * angle)) * 0.6f + animSize * 0.2f;
			float d2 = r - starR;
			float dx = fabs(delta.x) - layer->size2;
			float dOut = length(max((float2)(d2, dx), 0.0f));
			float dIn = min(max(d2, dx), 0.0f);
			dist = dOut + dIn;
			break;
		}
		case 24: // star 6
		{
			float angle = atan2(delta.z, delta.y);
			float r = length((float2)(delta.y, delta.z));
			float starR = animSize * (0.5f + 0.5f * cos(6.0f * angle)) * 0.6f + animSize * 0.2f;
			float d2 = r - starR;
			float dx = fabs(delta.x) - layer->size2;
			float dOut = length(max((float2)(d2, dx), 0.0f));
			float dIn = min(max(d2, dx), 0.0f);
			dist = dOut + dIn;
			break;
		}
		case 25: // gear
		{
			float angle = atan2(delta.z, delta.y);
			float r = length((float2)(delta.y, delta.z));
			float teeth = 8.0f;
			float gearR = animSize * (0.7f + 0.3f * cos(teeth * angle));
			float d2 = r - gearR;
			float dx = fabs(delta.x) - layer->size2;
			float dOut = length(max((float2)(d2, dx), 0.0f));
			float dIn = min(max(d2, dx), 0.0f);
			dist = dOut + dIn;
			break;
		}
		case 26: // heart
		{
			float y = delta.y / animSize;
			float z = delta.z / animSize;
			float d2 = pow(y * y + z * z - 1.0f, 3.0f) - y * y * z * z * z;
			d2 = (d2 > 0.0f ? 1.0f : -1.0f) * pow(fabs(d2), 1.0f / 6.0f) * animSize;
			float dx = fabs(delta.x) - layer->size2;
			float dOut = length(max((float2)(d2, dx), 0.0f));
			float dIn = min(max(d2, dx), 0.0f);
			dist = dOut + dIn;
			break;
		}
	}
	if (layer->edgeSoftness > 1e-10f)
	{
		float es = layer->edgeSoftness * 2.5f;
		dist = sqrt(dist * dist + es * es) - es;
	}
	return dist / layer->thickness;
}

float3 SingleTrapLightsShader(__constant sClInConstants *consts, sShaderInputDataCl *input,
	sClCalcParams *calcParam)
{
	float3 result = 0.0f;
	int layerCount = 0;

	if (!consts->params.singleTrapLights.enabled) return result;

	bool needOrbitColor = false;
	int soloL = consts->params.singleTrapLights.soloLayerIndex;
	for (int j = 0; j < consts->params.singleTrapLights.activeLayerCount; j++)
	{
		if (soloL > 0 && soloL != j + 1) continue;
		__global const sSingleTrapLightLayerCl *lj = &consts->params.singleTrapLights.layers[j];
		if (lj->enabled != 0 && lj->coloringMode == 2)
		{
			needOrbitColor = true;
			break;
		}
	}
	float orbitTrapRForColor = 0.0f;
	if (needOrbitColor)
	{
		float3 orbitTrapAdjusted;
		if (consts->params.common.fakeLightsOrbitTrapPreTransformed)
		{
			orbitTrapAdjusted = consts->params.common.fakeLightsOrbitTrap;
		}
		else
		{
			float3 baseOrbitTrap = consts->params.common.fakeLightsOrbitTrap;
			int posMode = consts->params.common.fakeLightsPositionMode;
			sFakeLightsModeParamsCl modeParams = consts->params.common.fakeLightsModes[posMode];
			float3 transformedTrap = Matrix33MulFloat3(modeParams.mRot, baseOrbitTrap * modeParams.scale)
				+ modeParams.offset;

			if (posMode == 1)
			{
				orbitTrapAdjusted = consts->params.camera + transformedTrap;
			}
			else if (posMode == 2)
			{
				orbitTrapAdjusted = consts->params.target + transformedTrap;
			}
			else if (posMode == 4)
			{
				orbitTrapAdjusted = transformedTrap;
				float angle = modeParams.rotation.y * M_PI_F / 180.0f;
				float3 pathOffset = (float3){cos(angle) * modeParams.pathRadius, 0.0f,
					sin(angle) * modeParams.pathRadius};
				orbitTrapAdjusted += pathOffset;
			}
			else if (posMode == 5)
			{
				orbitTrapAdjusted = transformedTrap;
				float angle = modeParams.rotation.y * M_PI_F / 180.0f;
				float yOffset = angle * modeParams.pathRadius * 0.1f;
				float3 pathOffset = (float3){cos(angle) * modeParams.pathRadius, yOffset,
					sin(angle) * modeParams.pathRadius};
				orbitTrapAdjusted += pathOffset;
			}
			else if (posMode == 6)
			{
				orbitTrapAdjusted = transformedTrap;
				float angle = modeParams.rotation.y * M_PI_F / 180.0f;
				float3 pathOffset = (float3){cos(angle) * modeParams.pathRadius, 0.0f,
					sin(angle) * modeParams.pathRadius};
				orbitTrapAdjusted = consts->params.target + orbitTrapAdjusted + pathOffset;
			}
			else
			{
				orbitTrapAdjusted = transformedTrap;
			}
		}

		float3 originalOrbitTrap = calcParam->orbitTrap;
		int originalOrbitTrapIndex = calcParam->orbitTrapIndex;
		calcParam->orbitTrapIndex = 0;
		calcParam->orbitTrap = orbitTrapAdjusted;
		formulaOut outOrbit = Fractal(consts, input->point, calcParam, calcModeOrbitTrap, NULL, -1);
		orbitTrapRForColor = outOrbit.orbitTrapR;
		calcParam->orbitTrap = originalOrbitTrap;
		calcParam->orbitTrapIndex = originalOrbitTrapIndex;
	}

	for (int i = 0; i < consts->params.singleTrapLights.activeLayerCount; i++)
	{
		__global const sSingleTrapLightLayerCl *layer = &consts->params.singleTrapLights.layers[i];
		if (!layer->enabled) continue;
		if (soloL > 0 && soloL != i + 1) continue;

		float3 effectivePosition = layer->position.xyz;
		if (!layer->preTransformed)
		{
			if (layer->positionMode == 1) effectivePosition += consts->params.camera;
			else if (layer->positionMode == 2) effectivePosition += consts->params.common.fractalPosition;
			else if (layer->positionMode == 3) effectivePosition += consts->params.target;
		}
		// Apply animation
		float time = (float)consts->params.frameNo;
		float animSize = layer->size;
		if (layer->animOrbitSpeed != 0.0f || layer->animPulsateSpeed != 0.0f)
		{
			float orbitAngle = time * layer->animOrbitSpeed * 0.01f + i * 0.7f;
			effectivePosition.x += cos(orbitAngle) * layer->animOrbitRadius;
			effectivePosition.y += sin(orbitAngle) * layer->animOrbitRadius;

			float pulsate = 1.0f + sin(time * layer->animPulsateSpeed * 0.1f + i * 1.3f) * layer->animPulsateAmount;
			animSize *= pulsate;
		}

		if (layer->maxDistance > 1e-30f)
		{
			float rs = fabs(layer->relativeSize);
			float sz = max(fabs(animSize), fabs(layer->size2)) * rs + fabs(layer->edgeSoftness) * rs;
			float margin = sz + layer->maxDistance * rs + fabs(layer->animOrbitRadius);
			float3 dC = input->point - effectivePosition;
			if (length(dC) > margin * 2.8f) continue;
		}

		float3 adjustedPoint = input->point - effectivePosition + layer->position.xyz * layer->relativeSize;
		float3 scaledPoint = adjustedPoint / layer->relativeSize;
		float rawDist = SingleTrapLightDistanceCl(scaledPoint, layer, animSize) * layer->relativeSize;
		float dist = rawDist;
		if (dist < 0.0f) dist = 0.0f;

		// Soft fade to maxDistance; maxDistance <= 0 → no cap.
		float maxDistFade = layer->maxDistance;
		float fade = 1.0f;
		if (maxDistFade > 1e-30f && dist > 0.0f)
		{
			float tFade = dist / maxDistFade;
			if (tFade >= 1.0f) continue;
			tFade = tFade * tFade * (3.0f - 2.0f * tFade);
			fade = 1.0f - tFade;
		}

		float blur = layer->blur;
		float distForFalloff = dist;
		if (blur > 1e-20f)
		{
			float blurScale = blur * (0.4f + 0.65f * fabs(layer->relativeSize));
			distForFalloff = sqrt(dist * dist + blurScale * blurScale);
		}
		float effectiveSharpening =
			layer->sharpening / (1.0f + blur * 1.75f + blur * blur * 0.4f);
		float effectiveDist = distForFalloff;
		float falloff;
		int ft = layer->falloffType;
		if (ft == 1)
		{
			falloff = 1.0f / (1.0f + effectiveDist * effectiveDist * effectiveSharpening);
		}
		else if (ft == 2)
		{
			falloff = max(0.0f, 1.0f - effectiveDist * sqrt(effectiveSharpening) * 1.35f);
		}
		else if (ft == 3)
		{
			falloff = exp(-effectiveDist * sqrt(effectiveSharpening) * 1.15f);
		}
		else if (ft == 4)
		{
			float edge = 1.0f / sqrt(effectiveSharpening + 1e-10f);
			float tFall = effectiveDist / edge;
			if (tFall >= 1.0f) falloff = 0.0f;
			else if (tFall <= 0.0f) falloff = 1.0f;
			else falloff = 1.0f - tFall * tFall * (3.0f - 2.0f * tFall);
		}
		else
		{
			falloff = exp(-effectiveDist * effectiveDist * effectiveSharpening);
		}
		if (layer->softness > 1e-10f && distForFalloff > 0.0f)
			falloff *= exp(-distForFalloff * layer->softness * 1.2f);
		float solidBoost = (rawDist < 0.0f) ? layer->solidIntensity : 1.0f;
		float innerGlow = 1.0f;
		if (rawDist < 0.0f)
		{
			float depth = min(1.0f, -rawDist / 2.0f);
			innerGlow = 1.0f + layer->softness * depth * 3.2f;
		}
		float intensity = layer->intensity * layer->visibility * falloff * solidBoost * innerGlow * fade;

		float gradT = 0.0f;
		if (layer->coloringMode == 2)
		{
			float mdBlend = max(layer->maxDistance, 1e-20f);
			gradT = orbitTrapRForColor / (orbitTrapRForColor + mdBlend);
		}
		else if (layer->maxDistance > 1e-30f)
		{
			gradT = dist / layer->maxDistance;
			if (gradT > 1.0f) gradT = 1.0f;
		}
		if (gradT > 1.0f) gradT = 1.0f;
		float3 layerColor =
			layer->color.xyz * (1.0f - gradT) + layer->gradientColor.xyz * gradT;
		if (layer->coloringMode == 1 || layer->coloringMode == 2)
		{
			layerColor *= (1.0f - gradT);
		}

		float3 contrib = intensity * layerColor;
		int combine = consts->params.singleTrapLights.combineMode;
		if (combine == 1)
		{
			result.x = max(result.x, contrib.x);
			result.y = max(result.y, contrib.y);
			result.z = max(result.z, contrib.z);
		}
		else if (combine == 2)
		{
			result = result + contrib - result * contrib;
		}
		else if (combine == 3)
		{
			result = (result * (float)(layerCount) + contrib) / (float)(layerCount + 1);
			layerCount++;
		}
		else if (combine == 4)
		{
			if (layerCount == 0) result = contrib;
			else result = result * contrib;
			layerCount++;
		}
		else
		{
			result += contrib;
		}
	}

	return result;
}
