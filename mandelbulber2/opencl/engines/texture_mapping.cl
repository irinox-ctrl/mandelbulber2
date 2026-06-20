/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2018-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * contains texture mapping fuction
 * used in the full_engine_cl
 */

#ifdef USE_TEXTURES
float2 TextureMapping(float3 inPoint, float3 normalVector, __global sObjectDataCl *objectData,
	__global sMaterialCl *material, float3 *textureVectorX, float3 *textureVectorY)
{
	float2 textureCoordinates;
	float3 point = inPoint;
	if (!material->textureFractalize)
	{
		point = point - objectData->position;
		point = Matrix33MulFloat3(objectData->rotationMatrix, point);
		point = modRepeat(point, objectData->repeat);
		point /= objectData->size;
	}

	point = Matrix33MulFloat3(material->rotMatrixTexture, point);
	normalVector = Matrix33MulFloat3(objectData->rotationMatrix, normalVector);

	switch (material->textureMappingType)
	{

		case mappingPlanar:
		{
#ifdef USE_PLANAR_MAPPING
			textureCoordinates = (float2){point.x, point.y};
			textureCoordinates.x /= -material->textureScale.x;
			textureCoordinates.y /= material->textureScale.y;
			textureCoordinates.x -= material->textureCenter.x;
			textureCoordinates.y -= material->textureCenter.y;

#ifdef USE_NORMAL_MAP_TEXTURE
			if (textureVectorX && textureVectorY)
			{
				float3 texX = (float3){1.0f, 0.0f, 0.0f};
				texX = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texX);
				texX = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texX);
				*textureVectorX = texX;

				float3 texY = (float3){0.0f, -1.0f, 0.0f};
				texY = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texY);
				texY = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texY);
				*textureVectorY = texY;
			}
#endif
#endif
			break;
		}

		case mappingCylindrical:
		{
#ifdef USE_CYLINDRICAL_MAPPING
			float alphaTexture = fmod(GetAlpha(point) + 2.0f * M_PI_F, 2.0f * M_PI_F);
			textureCoordinates.x = alphaTexture / (2.0f * M_PI_F);
			textureCoordinates.y = -point.z;
			textureCoordinates.x /= material->textureScale.x;
			textureCoordinates.y /= material->textureScale.y;
			textureCoordinates.x -= material->textureCenter.x;
			textureCoordinates.y -= material->textureCenter.y;

#ifdef USE_NORMAL_MAP_TEXTURE
			if (textureVectorX && textureVectorY)
			{
				float3 texY = (float3){0.0f, 0.0f, 1.0f};
				float3 texX = cross(point, texY);
				texX = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texX);
				texX = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texX);
				*textureVectorX = texX;
				texY = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texY);
				texY = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texY);
				*textureVectorY = texY;
			}
#endif
#endif
			break;
		}

		case mappingSpherical:
		{
#ifdef USE_SPHERICAL_MAPPING
			float alphaTexture = fmod(GetAlpha(point) + 2.0f * M_PI_F, 2.0f * M_PI_F);
			float betaTexture = -GetBeta(point);
			textureCoordinates.x = alphaTexture / (2.0f * M_PI_F);
			textureCoordinates.y = betaTexture / M_PI_F;
			textureCoordinates.x /= material->textureScale.x;
			textureCoordinates.y /= material->textureScale.y;
			textureCoordinates.x -= material->textureCenter.x;
			textureCoordinates.y -= material->textureCenter.y;

#ifdef USE_NORMAL_MAP_TEXTURE
			if (textureVectorX && textureVectorY)
			{
				float3 texY = (float3){0.0f, 0.0f, -1.0f};
				float3 texX = cross(texY, point);
				texX = normalize(texX);
				texY = cross(texX, point);

				texX = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texX);
				texX = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texX);
				*textureVectorX = texX;
				texY = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texY);
				texY = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texY);
				*textureVectorY = texY;
			}
#endif
#endif
			break;
		}

		case mappingCubic:
		{
#ifdef USE_CUBIC_MAPPING
			point /= material->textureScale;
			point -= material->textureCenter;

			float3 texX, texY;
			if (fabs(normalVector.x) > fabs(normalVector.y))
			{
				if (fabs(normalVector.x) > fabs(normalVector.z))
				{
					// x
					if (normalVector.x > 0.0f)
						textureCoordinates = (float2){point.y, -point.z};
					else
						textureCoordinates = (float2){-point.y, -point.z};

#ifdef USE_NORMAL_MAP_TEXTURE
					if (textureVectorX && textureVectorY)
					{
						if (normalVector.x > 0.0f)
						{
							texX = (float3){0.0f, -1.0f, 0.0f};
							texY = (float3){0.0f, 0.0f, 1.0f};
						}
						else
						{
							texX = (float3)(0.0f, 1.0f, 0.0f);
							texY = (float3)(0.0f, 0.0f, 1.0f);
						}
					}
#endif
				}
				else
				{
					// z
					if (normalVector.z > 0.0f)
						textureCoordinates = (float2){-point.x, point.y};
					else
						textureCoordinates = (float2){point.x, point.y};

#ifdef USE_NORMAL_MAP_TEXTURE
					if (textureVectorX && textureVectorY)
					{
						if (normalVector.z > 0.0f)
						{
							texX = (float3){1.0f, 0.0f, 0.0f};
							texY = (float3){0.0f, -1.0f, 0.0f};
						}
						else
						{
							texX = (float3){-1.0f, 0.0f, 0.0f};
							texY = (float3){0.0f, -1.0f, 0.0f};
						}
					}
#endif
				}
			}
			else
			{
				if (fabs(normalVector.y) > fabs(normalVector.z))
				{
					// y
					if (normalVector.y > 0.0f)
						textureCoordinates = (float2){-point.x, -point.z};
					else
						textureCoordinates = (float2){point.x, -point.z};

#ifdef USE_NORMAL_MAP_TEXTURE
					if (textureVectorX && textureVectorY)
					{
						if (normalVector.y > 0.0f)
						{
							texX = (float3){1.0f, 0.0f, 0.0f};
							texY = (float3){0.0f, 0.0f, 1.0f};
						}
						else
						{
							texX = (float3){-1.0f, 0.0f, 0.0f};
							texY = (float3){0.0f, 0.0f, 1.0f};
						}
					}
#endif
				}
				else
				{
					// z
					if (normalVector.z > 0.0f)
						textureCoordinates = (float2){-point.x, point.y};
					else
						textureCoordinates = (float2){point.x, point.y};

#ifdef USE_NORMAL_MAP_TEXTURE
					if (textureVectorX && textureVectorY)
					{
						if (normalVector.z > 0.0f)
						{
							texX = (float3){1.0f, 0.0f, 0.0f};
							texY = (float3){0.0f, -1.0f, 0.0f};
						}
						else
						{
							texX = (float3){-1.0f, 0.0f, 0.0f};
							texY = (float3){0.0f, -1.0f, 0.0f};
						}
					}
#endif
				}
			}

#ifdef USE_NORMAL_MAP_TEXTURE
			if (textureVectorX && textureVectorY)
			{
				texX = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texX);
				texX = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texX);
				*textureVectorX = texX;
				texY = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texY);
				texY = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texY);
				*textureVectorY = texY;
			}
#endif
#endif
			break;
		}

		case mappingTriplanar:
		{
#ifdef USE_TRIPLANAR_MAPPING
			// Verbeterde triplanar met Whiteout blending (naadlozer dan standaard)
			// blendSharpness: hogere waarde = scherpere overgangen tussen assen
			float3 absNormal = fabs(normalVector);
			float blendSharpness = 4.0f; // verhoogd van 2.0 voor scherpere projecties
			float wx = pow(absNormal.x, blendSharpness);
			float wy = pow(absNormal.y, blendSharpness);
			float wz = pow(absNormal.z, blendSharpness);
			float wSum = wx + wy + wz;
			if (wSum < 1e-10f) wSum = 1e-10f;
			wx /= wSum;
			wy /= wSum;
			wz /= wSum;

			// Whiteout blending: elke as gebruikt zijn eigen normaalcomponent
			// Geeft betere naadaansluiting dan eenvoudige gewogen som
			float2 texX_plane = (float2){
				point.y / -material->textureScale.x - material->textureCenter.x,
				point.z / material->textureScale.y - material->textureCenter.y};
			float2 texY_plane = (float2){
				point.x / -material->textureScale.x - material->textureCenter.x,
				point.z / material->textureScale.y - material->textureCenter.y};
			float2 texZ_plane = (float2){
				point.x / -material->textureScale.x - material->textureCenter.x,
				point.y / material->textureScale.y - material->textureCenter.y};

			textureCoordinates = texX_plane * wx + texY_plane * wy + texZ_plane * wz;

#ifdef USE_NORMAL_MAP_TEXTURE
			if (textureVectorX && textureVectorY)
			{
				// Gewogen normal map tangenten voor correcte bumps in overgangszone
				float3 texXvec = (float3){0.0f, wx, 0.0f} + (float3){wy, 0.0f, 0.0f} + (float3){wz, 0.0f, 0.0f};
				float3 texYvec = (float3){0.0f, 0.0f, wx} + (float3){0.0f, 0.0f, wy} + (float3){0.0f, wy, 0.0f};
				if (length(texXvec) > 1e-10f) texXvec = normalize(texXvec);
				if (length(texYvec) > 1e-10f) texYvec = normalize(texYvec);
				texXvec = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texXvec);
				texXvec = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texXvec);
				*textureVectorX = texXvec;
				texYvec = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texYvec);
				texYvec = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texYvec);
				*textureVectorY = texYvec;
			}
#endif
#endif
			break;
		}

		case mappingTriplanarStochastic:
		{
#ifdef USE_TRIPLANAR_STOCHASTIC_MAPPING
			// Stochastic triplanar: willekeurige rotatie per tegel elimineert herhalingspatronen
			// Methode: hash-gebaseerde 2D rotatie per as, geblend met normale triplanar gewichten
			float3 absNormal = fabs(normalVector);
			float blendSharpness = 4.0f;
			float wx = pow(absNormal.x, blendSharpness);
			float wy = pow(absNormal.y, blendSharpness);
			float wz = pow(absNormal.z, blendSharpness);
			float wSum = wx + wy + wz;
			if (wSum < 1e-10f) wSum = 1e-10f;
			wx /= wSum; wy /= wSum; wz /= wSum;

			// Hash-gebaseerde rotatie per tegel - geen lambda (OpenCL C)
			// X-as projectie (YZ vlak)
			float2 pX = (float2){point.y / material->textureScale.x, point.z / material->textureScale.y};
			float2 tileX = floor(pX);
			float angleX = fract(sin(dot(tileX, (float2){127.1f, 311.7f})) * 43758.5453f) * 2.0f * M_PI_F;
			float2 fracX = pX - tileX - 0.5f;
			float2 texX_plane = (float2){
				fracX.x * cos(angleX) - fracX.y * sin(angleX),
				fracX.x * sin(angleX) + fracX.y * cos(angleX)} - material->textureCenter.xy;

			// Y-as projectie (XZ vlak)
			float2 pY = (float2){point.x / material->textureScale.x, point.z / material->textureScale.y};
			float2 tileY = floor(pY);
			float angleY = fract(sin(dot(tileY, (float2){127.1f, 311.7f})) * 43758.5453f) * 2.0f * M_PI_F;
			float2 fracY = pY - tileY - 0.5f;
			float2 texY_plane = (float2){
				fracY.x * cos(angleY) - fracY.y * sin(angleY),
				fracY.x * sin(angleY) + fracY.y * cos(angleY)} - material->textureCenter.xy;

			// Z-as projectie (XY vlak)
			float2 pZ = (float2){point.x / material->textureScale.x, point.y / material->textureScale.y};
			float2 tileZ = floor(pZ);
			float angleZ = fract(sin(dot(tileZ, (float2){127.1f, 311.7f})) * 43758.5453f) * 2.0f * M_PI_F;
			float2 fracZ = pZ - tileZ - 0.5f;
			float2 texZ_plane = (float2){
				fracZ.x * cos(angleZ) - fracZ.y * sin(angleZ),
				fracZ.x * sin(angleZ) + fracZ.y * cos(angleZ)} - material->textureCenter.xy;

			textureCoordinates = texX_plane * wx + texY_plane * wy + texZ_plane * wz;

#ifdef USE_NORMAL_MAP_TEXTURE
			if (textureVectorX && textureVectorY)
			{
				*textureVectorX = (float3){cos(angleZ), sin(angleZ), 0.0f};
				*textureVectorY = (float3){-sin(angleZ), cos(angleZ), 0.0f};
			}
#endif
#endif
			break;
		}

		case mappingCylindricalFractal:
		{
#ifdef USE_CYLINDRICAL_FRACTAL_MAPPING
			// Cylindrisch op de geaccumuleerde fractal-z (volgt de fractalstructuur)
			// Gebruikt atan2 en lengte van de fractal-iteratievector
			float r = length(point.xy);
			if (r < 1e-15f) r = 1e-15f;
			float alpha = fmod(atan2(point.y, point.x) + 2.0f * M_PI_F, 2.0f * M_PI_F);
			textureCoordinates.x = alpha / (2.0f * M_PI_F);
			textureCoordinates.y = -point.z / (r + 1e-10f); // z genormaliseerd op radius
			textureCoordinates.x /= material->textureScale.x;
			textureCoordinates.y /= material->textureScale.y;
			textureCoordinates -= material->textureCenter.xy;

#ifdef USE_NORMAL_MAP_TEXTURE
			if (textureVectorX && textureVectorY)
			{
				float3 texY = (float3){0.0f, 0.0f, 1.0f};
				float3 texX = cross(point, texY);
				if (length(texX) > 1e-10f) texX = normalize(texX);
				texX = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texX);
				texX = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texX);
				*textureVectorX = texX;
				texY = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texY);
				texY = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texY);
				*textureVectorY = texY;
			}
#endif
#endif
			break;
		}

		case mappingSphericalFractal:
		{
#ifdef USE_SPHERICAL_FRACTAL_MAPPING
			// Sferisch op de geaccumuleerde fractal-z
			// theta/phi gebaseerd op de richting van de fractal-iteratievector
			float r = length(point);
			if (r < 1e-15f) r = 1e-15f;
			float phi = atan2(point.y, point.x);           // azimuth -PI..PI
			float theta = acos(clamp(point.z / r, -1.0f, 1.0f)); // inclinatie 0..PI
			textureCoordinates.x = (phi + M_PI_F) / (2.0f * M_PI_F);
			textureCoordinates.y = theta / M_PI_F;
			textureCoordinates.x /= material->textureScale.x;
			textureCoordinates.y /= material->textureScale.y;
			textureCoordinates -= material->textureCenter.xy;

#ifdef USE_NORMAL_MAP_TEXTURE
			if (textureVectorX && textureVectorY)
			{
				float3 texYvec = (float3){0.0f, 0.0f, -1.0f};
				float3 texXvec = cross(texYvec, point);
				if (length(texXvec) > 1e-10f) texXvec = normalize(texXvec);
				texYvec = cross(texXvec, point);
				if (length(texYvec) > 1e-10f) texYvec = normalize(texYvec);
				texXvec = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texXvec);
				texXvec = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texXvec);
				*textureVectorX = texXvec;
				texYvec = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texYvec);
				texYvec = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texYvec);
				*textureVectorY = texYvec;
			}
#endif
#endif
			break;
		}

		case mappingOcta:
		{
#ifdef USE_OCTA_MAPPING
			// Octa (octahedron) projectie: naadloze 8-vlaksprojektie voor bolvormige fractals
			// Alle 8 octanten projiciëren op hetzelfde vlak zonder seams
			float3 n = point;
			float r = length(n);
			if (r > 1e-10f) n /= r;
			// Octahedral mapping: vouw alle octanten naar het positieve kwadrant
			float3 absN = fabs(n);
			// L1-normaliseer (octahedron projectie)
			float l1 = absN.x + absN.y + absN.z;
			if (l1 < 1e-10f) l1 = 1e-10f;
			float2 uv = (float2){n.x, n.y} / l1;
			// Herspiegel onderste hemisfeer
			if (n.z < 0.0f)
			{
				float2 absUV = fabs(uv);
				uv = (float2){
					copysign(1.0f - absUV.y, uv.x),
					copysign(1.0f - absUV.x, uv.y)};
			}
			textureCoordinates.x = uv.x / material->textureScale.x - material->textureCenter.x;
			textureCoordinates.y = uv.y / material->textureScale.y - material->textureCenter.y;

#ifdef USE_NORMAL_MAP_TEXTURE
			if (textureVectorX && textureVectorY)
			{
				*textureVectorX = normalize((float3){1.0f - absN.z, 0.0f, -n.x});
				*textureVectorY = normalize((float3){0.0f, 1.0f - absN.z, -n.y});
			}
#endif
#endif
			break;
		}

		case mappingCamera:
		{
#ifdef USE_CAMERA_MAPPING
			// Camera projectie: textuur geprojecteerd vanuit het camerastandpunt
			// objectData->position wordt hergebruikt als camerarichting
			// point is al getransformeerd; we gebruiken alleen XY voor projectie
			float3 camDir = normalize(objectData->position); // camerarichting als projectieas
			if (length(camDir) < 1e-10f) camDir = (float3){0.0f, 0.0f, 1.0f};
			// Bouw orthonormaal camerakader
			float3 camUp = (float3){0.0f, 1.0f, 0.0f};
			if (fabs(dot(camDir, camUp)) > 0.99f) camUp = (float3){1.0f, 0.0f, 0.0f};
			float3 camRight = normalize(cross(camDir, camUp));
			camUp = normalize(cross(camRight, camDir));
			// Projecteer point op cameravlak
			textureCoordinates.x = dot(point, camRight) / material->textureScale.x - material->textureCenter.x;
			textureCoordinates.y = dot(point, camUp) / material->textureScale.y - material->textureCenter.y;

#ifdef USE_NORMAL_MAP_TEXTURE
			if (textureVectorX && textureVectorY)
			{
				*textureVectorX = camRight;
				*textureVectorY = camUp;
			}
#endif
#endif
			break;
		}

		case mappingEquirectangular:
		{
#ifdef USE_EQUIRECTANGULAR_MAPPING
			float r = length(point);
			if (r < 1e-15f) r = 1e-15f;
			float longitude = atan2(point.y, point.x);
			float latitude = asin(clamp(point.z / r, -1.0f, 1.0f));

			textureCoordinates.x = (longitude + M_PI_F) / (2.0f * M_PI_F);
			textureCoordinates.y = (latitude + M_PI_F / 2.0f) / M_PI_F;
			textureCoordinates.x /= material->textureScale.x;
			textureCoordinates.y /= material->textureScale.y;
			textureCoordinates.x -= material->textureCenter.x;
			textureCoordinates.y -= material->textureCenter.y;

#ifdef USE_NORMAL_MAP_TEXTURE
			if (textureVectorX && textureVectorY)
			{
				float3 texYvec = (float3){0.0f, 0.0f, -1.0f};
				float3 texXvec = cross(texYvec, point);
				texXvec = normalize(texXvec);
				texYvec = cross(texXvec, point);

				texXvec = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texXvec);
				texXvec = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texXvec);
				*textureVectorX = texXvec;
				texYvec = Matrix33MulFloat3(TransposeMatrix(objectData->rotationMatrix), texYvec);
				texYvec = Matrix33MulFloat3(TransposeMatrix(material->rotMatrixTexture), texYvec);
				*textureVectorY = texYvec;
			}
#endif
#endif
			break;
		}
	}
	return textureCoordinates;
}
#endif // USE_TEXTURES

