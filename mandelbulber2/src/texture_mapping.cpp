/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2016-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * global method TextureMapping() - coordinate transformer for textures
 *
 * For the given parameters TextureMapping(...) determines the point x-y
 * on the texture to use for processing
 */

#include "texture_mapping.hpp"

#include "material.h"
#include "object_data.hpp"
#include "texture_enums.hpp"

CVector2<float> TextureMapping(CVector3 inPoint, CVector3 normalVector,
	const cObjectData &objectData, const cMaterial *material, CVector3 *textureVectorX,
	CVector3 *textureVectorY)
{
	CVector2<float> textureCoordinates;
	CVector3 point = inPoint;
	if (!material->textureFractalize)
	{
		point = point - objectData.position;
		point = objectData.rotationMatrix.RotateVector(point);
		point = point.repeatMod(objectData.repeat);
		point /= objectData.size;
	}
	point = material->rotMatrixTexture.RotateVector(point);

	normalVector = objectData.rotationMatrix.RotateVector(normalVector);

	switch (material->textureMappingType)
	{
		case texture::mappingPlanar:
		{
			textureCoordinates = CVector2<float>(point.x, point.y);
			textureCoordinates.x /= -material->textureScale.x;
			textureCoordinates.y /= material->textureScale.y;
			textureCoordinates.x -= material->textureCenter.x;
			textureCoordinates.y -= material->textureCenter.y;

			if (textureVectorX && textureVectorY)
			{
				CVector3 texX(1.0, 0.0, 0.0);
				texX = objectData.rotationMatrix.Transpose().RotateVector(texX);
				texX = material->rotMatrixTexture.Transpose().RotateVector(texX);
				*textureVectorX = texX;

				CVector3 texY(0.0, -1.0, 0.0);
				texY = objectData.rotationMatrix.Transpose().RotateVector(texY);
				texY = material->rotMatrixTexture.Transpose().RotateVector(texY);
				*textureVectorY = texY;
			}
			break;
		}
		case texture::mappingCylindrical:
		{
			double alphaTexture = fmod(point.GetAlpha() + 2.0 * M_PI, 2.0 * M_PI);
			textureCoordinates.x = alphaTexture / (2.0 * M_PI);
			textureCoordinates.y = -point.z;
			textureCoordinates.x /= material->textureScale.x;
			textureCoordinates.y /= material->textureScale.y;
			textureCoordinates.x -= material->textureCenter.x;
			textureCoordinates.y -= material->textureCenter.y;

			if (textureVectorX && textureVectorY)
			{
				CVector3 texY(0.0, 0.0, 1.0);
				CVector3 texX = point.Cross(texY);
				texX = objectData.rotationMatrix.Transpose().RotateVector(texX);
				texX = material->rotMatrixTexture.Transpose().RotateVector(texX);
				*textureVectorX = texX;
				texY = objectData.rotationMatrix.Transpose().RotateVector(texY);
				texY = material->rotMatrixTexture.Transpose().RotateVector(texY);
				*textureVectorY = texY;
			}

			break;
		}
		case texture::mappingSpherical:
		{
			double alphaTexture = fmod(point.GetAlpha() + 2.0 * M_PI, 2.0 * M_PI);
			double betaTexture = -point.GetBeta();
			textureCoordinates.x = alphaTexture / (2.0 * M_PI);
			textureCoordinates.y = betaTexture / M_PI;
			textureCoordinates.x /= material->textureScale.x;
			textureCoordinates.y /= material->textureScale.y;
			textureCoordinates.x -= material->textureCenter.x;
			textureCoordinates.y -= material->textureCenter.y;

			if (textureVectorX && textureVectorY)
			{
				CVector3 texY(0.0, 0.0, -1.0);
				CVector3 texX = texY.Cross(point);
				texX.Normalize();
				texY = texX.Cross(point);

				texX = objectData.rotationMatrix.Transpose().RotateVector(texX);
				texX = material->rotMatrixTexture.Transpose().RotateVector(texX);
				*textureVectorX = texX;
				texY = objectData.rotationMatrix.Transpose().RotateVector(texY);
				texY = material->rotMatrixTexture.Transpose().RotateVector(texY);
				*textureVectorY = texY;
			}

			break;
		}
		case texture::mappingCubic:
		{
			point /= material->textureScale;
			point -= material->textureCenter;

			CVector3 texX;
			CVector3 texY;

			if (fabs(normalVector.x) > fabs(normalVector.y))
			{
				if (fabs(normalVector.x) > fabs(normalVector.z))
				{
					// x
					if (normalVector.x > 0)
						textureCoordinates = CVector2<float>(point.y, -point.z);
					else
						textureCoordinates = CVector2<float>(-point.y, -point.z);

					if (textureVectorX && textureVectorY)
					{
						if (normalVector.x > 0)
						{
							texX = CVector3(0.0, -1.0, 0.0);
							texY = CVector3(0.0, 0.0, 1.0);
						}
						else
						{
							texX = CVector3(0.0, 1.0, 0.0);
							texY = CVector3(0.0, 0.0, 1.0);
						}
					}
				}
				else
				{
					// z
					if (normalVector.z > 0)
						textureCoordinates = CVector2<float>(-point.x, point.y);
					else
						textureCoordinates = CVector2<float>(point.x, point.y);

					if (textureVectorX && textureVectorY)
					{
						if (normalVector.z > 0)
						{
							texX = CVector3(1.0, 0.0, 0.0);
							texY = CVector3(0.0, -1.0, 0.0);
						}
						else
						{
							texX = CVector3(-1.0, 0.0, 0.0);
							texY = CVector3(0.0, -1.0, 0.0);
						}
					}
				}
			}
			else
			{
				if (fabs(normalVector.y) > fabs(normalVector.z))
				{
					// y
					if (normalVector.y > 0)
						textureCoordinates = CVector2<float>(-point.x, -point.z);
					else
						textureCoordinates = CVector2<float>(point.x, -point.z);

					if (textureVectorX && textureVectorY)
					{
						if (normalVector.y > 0)
						{
							texX = CVector3(1.0, 0.0, 0.0);
							texY = CVector3(0.0, 0.0, 1.0);
						}
						else
						{
							texX = CVector3(-1.0, 0.0, 0.0);
							texY = CVector3(0.0, 0.0, 1.0);
						}
					}
				}
				else
				{
					// z
					if (normalVector.z > 0)
						textureCoordinates = CVector2<float>(-point.x, point.y);
					else
						textureCoordinates = CVector2<float>(point.x, point.y);

					if (textureVectorX && textureVectorY)
					{
						if (normalVector.z > 0)
						{
							texX = CVector3(1.0, 0.0, 0.0);
							texY = CVector3(0.0, -1.0, 0.0);
						}
						else
						{
							texX = CVector3(-1.0, 0.0, 0.0);
							texY = CVector3(0.0, -1.0, 0.0);
						}
					}
				}
			}

			if (textureVectorX && textureVectorY)
			{
				texX = objectData.rotationMatrix.Transpose().RotateVector(texX);
				texX = material->rotMatrixTexture.Transpose().RotateVector(texX);
				*textureVectorX = texX;
				texY = objectData.rotationMatrix.Transpose().RotateVector(texY);
				texY = material->rotMatrixTexture.Transpose().RotateVector(texY);
				*textureVectorY = texY;
			}

			break;
		}
		case texture::mappingTriplanar:
		{
			CVector3 absNormal(fabs(normalVector.x), fabs(normalVector.y), fabs(normalVector.z));
			double blendSharpness = 2.0;
			double wx = pow(absNormal.x, blendSharpness);
			double wy = pow(absNormal.y, blendSharpness);
			double wz = pow(absNormal.z, blendSharpness);
			double wSum = wx + wy + wz;
			if (wSum < 1e-10) wSum = 1e-10;
			wx /= wSum;
			wy /= wSum;
			wz /= wSum;

			CVector2<float> texX_plane(point.y / -material->textureScale.x - material->textureCenter.x,
				point.z / material->textureScale.y - material->textureCenter.y);
			CVector2<float> texY_plane(point.x / -material->textureScale.x - material->textureCenter.x,
				point.z / material->textureScale.y - material->textureCenter.y);
			CVector2<float> texZ_plane(point.x / -material->textureScale.x - material->textureCenter.x,
				point.y / material->textureScale.y - material->textureCenter.y);

			textureCoordinates = texX_plane * wx + texY_plane * wy + texZ_plane * wz;

			if (textureVectorX && textureVectorY)
			{
				CVector3 texXvec, texYvec;
				if (absNormal.x >= absNormal.y && absNormal.x >= absNormal.z)
				{
					texXvec = CVector3(0.0, 1.0, 0.0);
					texYvec = CVector3(0.0, 0.0, 1.0);
				}
				else if (absNormal.y >= absNormal.z)
				{
					texXvec = CVector3(1.0, 0.0, 0.0);
					texYvec = CVector3(0.0, 0.0, 1.0);
				}
				else
				{
					texXvec = CVector3(1.0, 0.0, 0.0);
					texYvec = CVector3(0.0, 1.0, 0.0);
				}
				texXvec = objectData.rotationMatrix.Transpose().RotateVector(texXvec);
				texXvec = material->rotMatrixTexture.Transpose().RotateVector(texXvec);
				*textureVectorX = texXvec;
				texYvec = objectData.rotationMatrix.Transpose().RotateVector(texYvec);
				texYvec = material->rotMatrixTexture.Transpose().RotateVector(texYvec);
				*textureVectorY = texYvec;
			}
			break;
		}
		case texture::mappingEquirectangular:
		{
			double r = point.Length();
			if (r < 1e-15) r = 1e-15;
			double longitude = atan2(point.y, point.x);
			double sinVal = point.z / r;
			if (sinVal < -1.0) sinVal = -1.0;
			if (sinVal > 1.0) sinVal = 1.0;
			double latitude = asin(sinVal);

			textureCoordinates.x = (longitude + M_PI) / (2.0 * M_PI);
			textureCoordinates.y = (latitude + M_PI / 2.0) / M_PI;
			textureCoordinates.x /= material->textureScale.x;
			textureCoordinates.y /= material->textureScale.y;
			textureCoordinates.x -= material->textureCenter.x;
			textureCoordinates.y -= material->textureCenter.y;

			if (textureVectorX && textureVectorY)
			{
				CVector3 texYvec(0.0, 0.0, -1.0);
				CVector3 texXvec = texYvec.Cross(point);
				texXvec.Normalize();
				texYvec = texXvec.Cross(point);

				texXvec = objectData.rotationMatrix.Transpose().RotateVector(texXvec);
				texXvec = material->rotMatrixTexture.Transpose().RotateVector(texXvec);
				*textureVectorX = texXvec;
				texYvec = objectData.rotationMatrix.Transpose().RotateVector(texYvec);
				texYvec = material->rotMatrixTexture.Transpose().RotateVector(texYvec);
				*textureVectorY = texYvec;
			}
			break;
		}
	}
	return textureCoordinates;
}
