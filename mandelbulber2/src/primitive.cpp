/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2022-23 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * definitions of primitive objects
 */

#include "primitive.hpp"

#include <cmath>
#include <QDateTime>
#include <QDebug>

#include "common_math.h"

using std::max;

sPrimitiveBasic::sPrimitiveBasic(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
{
	userObjectId = par->Get<int>(fullName + "_object_id");
	objectId = -1;
	position = par->Get<CVector3>(fullName + "_position");
	materialId = par->Get<int>(fullName + "_material_id");
	SetRotation(par->Get<CVector3>(fullName + "_rotation"));
	enable = par->Get<bool>(fullName + "_enabled");
	booleanOperator = enumPrimitiveBooleanOperator(par->Get<int>(fullName + "_boolean_operator"));
	repeat = par->Get<CVector3>(fullName + "_repeat");
	scale = par->Get<double>(fullName + "_scale");
	smoothDeCombineEnable = par->Get<bool>(fullName + "_smooth_de_combine_enable");
	smoothDeCombineDistance = par->Get<double>(fullName + "_smooth_de_combine_distance");
	primitiveScale = par->Get<CVector3>(fullName + "_prim_scale");
	coordinateSpace = par->Get<int>(fullName + "_coordinate_space");
	pivot = par->Get<CVector3>(fullName + "_pivot");
	useWorldSpacePivot = par->Get<bool>("use_world_space_pivot");

	// Load 3-point alignment parameters
	alignP1 = par->Get<CVector3>(fullName + "_align_p1");
	alignP2 = par->Get<CVector3>(fullName + "_align_p2");
	alignP3 = par->Get<CVector3>(fullName + "_align_p3");

	// Load cloner settings
	cloner.enabled = par->Get<bool>(fullName + "_cloner_enabled");
	cloner.mode = static_cast<ClonerSettings::Mode>(par->Get<int>(fullName + "_cloner_mode"));
	cloner.count = par->Get<int>(fullName + "_cloner_count");
	cloner.offset = par->Get<CVector3>(fullName + "_cloner_offset");
	cloner.radius = par->Get<double>(fullName + "_cloner_radius");
	cloner.startAngle = par->Get<double>(fullName + "_cloner_start_angle");
	cloner.endAngle = par->Get<double>(fullName + "_cloner_end_angle");
	cloner.plane = par->Get<int>(fullName + "_cloner_plane");
	cloner.gridCount = par->Get<CVector3>(fullName + "_cloner_grid_count");
	cloner.gridSize = par->Get<CVector3>(fullName + "_cloner_grid_size");

	smoothRadius = par->Get<double>(fullName + "_smooth_radius");
	mirrorX = par->Get<bool>(fullName + "_mirror_x");
	mirrorY = par->Get<bool>(fullName + "_mirror_y");
	mirrorZ = par->Get<bool>(fullName + "_mirror_z");
	// shellEnable / shellThickness: dead code — empty + wallThickness provides the same functionality
	// shellEnable = par->Get<bool>(fullName + "_shell_enable");
	// shellThickness = par->Get<double>(fullName + "_shell_thickness");

	// Load group settings
	groupId = par->Get<int>(fullName + "_group_id");
	groupName = par->Get<QString>(fullName + "_group_name");
	groupEnabled = par->Get<bool>(fullName + "_group_enabled");
	groupVisible = par->Get<bool>(fullName + "_group_visible");
	groupLocked = par->Get<bool>(fullName + "_group_locked");
	groupBooleanOperator = enumPrimitiveBooleanOperator(par->Get<int>(fullName + "_group_boolean_operator"));
	groupSmoothRadius = par->Get<double>(fullName + "_group_smooth_radius");
	groupPriority = par->Get<int>(fullName + "_group_priority");

	// Load group transformations
	groupPosition = par->Get<CVector3>(fullName + "_group_position");
	groupRotation = par->Get<CVector3>(fullName + "_group_rotation");
	groupScale = par->Get<CVector3>(fullName + "_group_scale");

	// Load per-primitive material override
	materialOverrideEnable = par->Get<bool>(fullName + "_material_override_enable");
	materialColor = par->Get<sRGB>(fullName + "_material_color");
	materialReflectance = par->Get<double>(fullName + "_material_reflectance");
	materialTransparency = par->Get<double>(fullName + "_material_transparency");
	materialSpecular = par->Get<double>(fullName + "_material_specular");
	materialRoughness = par->Get<double>(fullName + "_material_roughness");
	materialMetallic = par->Get<double>(fullName + "_material_metallic");
	materialLuminosity = par->Get<double>(fullName + "_material_luminosity");

	// Load deformation modifiers
	deformBendEnable = par->Get<bool>(fullName + "_deform_bend_enable");
	deformBendAngle = par->Get<double>(fullName + "_deform_bend_angle");
	deformBendAxis = par->Get<int>(fullName + "_deform_bend_axis");
	deformBendStrength = par->Get<double>(fullName + "_deform_bend_strength");
	deformBendMode = par->Get<int>(fullName + "_deform_bend_mode");
	deformBendKeepY = par->Get<bool>(fullName + "_deform_bend_keep_y");

	deformTwistEnable = par->Get<bool>(fullName + "_deform_twist_enable");
	deformTwistAngle = par->Get<double>(fullName + "_deform_twist_angle");
	deformTwistAxis = par->Get<int>(fullName + "_deform_twist_axis");
	deformTwistStrength = par->Get<double>(fullName + "_deform_twist_strength");
	deformTwistMode = par->Get<int>(fullName + "_deform_twist_mode");

	deformTaperEnable = par->Get<bool>(fullName + "_deform_taper_enable");
	deformTaperRate = par->Get<double>(fullName + "_deform_taper_rate");
	deformTaperAxis = par->Get<int>(fullName + "_deform_taper_axis");
	deformTaperStrength = par->Get<double>(fullName + "_deform_taper_strength");
	deformTaperCurvature = par->Get<double>(fullName + "_deform_taper_curvature");
	deformTaperMode = par->Get<int>(fullName + "_deform_taper_mode");

	// Load instance system
	isInstance = par->Get<bool>(fullName + "_is_instance");
	instanceMasterId = par->Get<int>(fullName + "_instance_master_id");
	instanceInheritTransform = par->Get<bool>(fullName + "_instance_inherit_transform");

	// Load boolean edge modification
	booleanEdgeChamfer = par->Get<double>(fullName + "_boolean_edge_chamfer");
	booleanEdgeChamferQuality = par->Get<int>(fullName + "_boolean_edge_chamfer_quality");

	// Load extended repeat settings
	repeatOffset = par->Get<CVector3>(fullName + "_repeat_offset");
	repeatFinite = par->Get<int>(fullName + "_repeat_finite");
	repeatFiniteRange = par->Get<CVector3>(fullName + "_repeat_finite_range");
	repeatRadialCount = par->Get<double>(fullName + "_repeat_radial_count");
	repeatRadialPlane = par->Get<int>(fullName + "_repeat_radial_plane");
	repeatMode = par->Get<int>(fullName + "_repeat_mode");
	repeatRotationStep = par->Get<double>(fullName + "_repeat_rotation_step");
	repeatFibonacciCount = par->Get<int>(fullName + "_repeat_fibonacci_count");
	repeatFibonacciSpread = par->Get<double>(fullName + "_repeat_fibonacci_spread");
	// Spiral repeat
	repeatSpiralStep = par->Get<CVector3>(fullName + "_repeat_spiral_step");
	repeatSpiralAngle = par->Get<CVector3>(fullName + "_repeat_spiral_angle");
	repeatSpiralRadius = par->Get<CVector3>(fullName + "_repeat_spiral_radius");
	// Wave repeat
	repeatWaveAmplitude = par->Get<CVector3>(fullName + "_repeat_wave_amplitude");
	repeatWaveFrequency = par->Get<CVector3>(fullName + "_repeat_wave_frequency");
	repeatWavePhase = par->Get<CVector3>(fullName + "_repeat_wave_phase");
	repeatWaveAxis = par->Get<int>(fullName + "_repeat_wave_axis");

	// Load effectors
	for (int i = 0; i < maxEffectors; i++)
	{
		QString effName = fullName + QString("_effector_%1").arg(i + 1);
		int effType = par->Get<int>(effName + "_type");
		bool effEnabled = par->Get<bool>(effName + "_enabled");
		if (effEnabled)
		{
			switch (effType)
			{
				case 1: // Random Effector
				{
					auto *re = new RandomEffector();
					re->enabled = true;
					re->mode = static_cast<Effector::Mode>(par->Get<int>(effName + "_mode"));
					re->strength = par->Get<double>(effName + "_strength");
					re->seed = par->Get<int>(effName + "_random_seed");
					re->positionAmp = par->Get<CVector3>(effName + "_random_position_amp");
					re->rotationAmp = par->Get<CVector3>(effName + "_random_rotation_amp");
					re->scaleAmp = par->Get<CVector3>(effName + "_random_scale_amp");
					effectors[i].reset(re);
					break;
				}
				case 2: // Step Effector
				{
					auto *se = new StepEffector();
					se->enabled = true;
					se->mode = static_cast<Effector::Mode>(par->Get<int>(effName + "_mode"));
					se->strength = par->Get<double>(effName + "_strength");
					se->positionStep = par->Get<CVector3>(effName + "_random_position_amp");
					se->rotationStep = par->Get<CVector3>(effName + "_random_rotation_amp");
					se->scaleStep = par->Get<CVector3>(effName + "_random_scale_amp");
					effectors[i].reset(se);
					break;
				}
				case 3: // Formula Effector
				{
					auto *fe = new FormulaEffector();
					fe->enabled = true;
					fe->mode = static_cast<Effector::Mode>(par->Get<int>(effName + "_mode"));
					fe->strength = par->Get<double>(effName + "_strength");
					fe->formulaPreset = par->Get<int>(effName + "_random_seed") % 4;
					effectors[i].reset(fe);
					break;
				}
				case 4: // Time Effector
				{
					auto *te = new TimeEffector();
					te->enabled = true;
					te->mode = static_cast<Effector::Mode>(par->Get<int>(effName + "_mode"));
					te->strength = par->Get<double>(effName + "_strength");
					te->timeOffset = par->Get<int>(effName + "_random_seed");
					te->timeScale = par->Get<double>(effName + "_strength");
					effectors[i].reset(te);
					break;
				}
				default:
					effectors[i].reset();
					break;
			}
		}
		else
		{
			effectors[i].reset();
		}
	}

	// DEBUG: Print shell settings
	// shellEnable is dead code — empty + wallThickness provides hollow shell functionality
}

CVector3 sPrimitiveBasic::TransformPoint(const CVector3 &_point) const
{
	CVector3 point;
	if (useWorldSpacePivot)
	{
		point = _point - pivot;
		point = rotationMatrix.RotateVector(point);
		point = point + pivot;
		point = point - position;
	}
	else
	{
		point = _point - position;
		point = rotationMatrix.RotateVector(point - pivot);
		point = point + pivot;
	}

	if (mirrorX) point.x = fabs(point.x);
	if (mirrorY) point.y = fabs(point.y);
	if (mirrorZ) point.z = fabs(point.z);

	return point;
}

CVector3 sPrimitiveBasic::ApplyDeformations(const CVector3 &point) const
{
	CVector3 result = point;

	// Bend deformation
	if (deformBendEnable && fabs(deformBendAngle) > 1e-5)
	{
		double k = deformBendAngle;
		if (deformBendAxis == 0) // bend along X
		{
			double cx = cos(k * result.x), sx = sin(k * result.x);
			result = CVector3(sx / k, result.y, result.z + (1.0 - cx) / k);
		}
		else if (deformBendAxis == 1) // bend along Y
		{
			double cy = cos(k * result.y), sy = sin(k * result.y);
			result = CVector3(result.x, sy / k, result.z + (1.0 - cy) / k);
		}
		else // bend along Z
		{
			double cz = cos(k * result.z), sz = sin(k * result.z);
			result = CVector3(result.x + (1.0 - cz) / k, result.y, sz / k);
		}
	}

	// Twist deformation
	if (deformTwistEnable && fabs(deformTwistAngle) > 1e-5)
	{
		double k, c, s;
		if (deformTwistAxis == 0) {
			k = deformTwistAngle * result.x; c = cos(k); s = sin(k);
			result = CVector3(result.x, c * result.y - s * result.z, s * result.y + c * result.z);
		}
		else if (deformTwistAxis == 1) {
			k = deformTwistAngle * result.y; c = cos(k); s = sin(k);
			result = CVector3(c * result.x - s * result.z, result.y, s * result.x + c * result.z);
		}
		else {
			k = deformTwistAngle * result.z; c = cos(k); s = sin(k);
			result = CVector3(c * result.x - s * result.y, s * result.x + c * result.y, result.z);
		}
	}

	// Taper deformation
	if (deformTaperEnable && fabs(deformTaperRate) > 1e-5)
	{
		double k;
		if (deformTaperAxis == 0) {
			k = max(1.0 + deformTaperRate * result.x, 0.01);
			result = CVector3(result.x, result.y * k, result.z * k);
		}
		else if (deformTaperAxis == 1) {
			k = max(1.0 + deformTaperRate * result.y, 0.01);
			result = CVector3(result.x * k, result.y, result.z * k);
		}
		else {
			k = max(1.0 + deformTaperRate * result.z, 0.01);
			result = CVector3(result.x * k, result.y * k, result.z);
		}
	}

	return result;
}

CVector3 sPrimitiveBasic::CalculateCloneOffset(int index) const
{
	switch (cloner.mode)
	{
		case ClonerSettings::LINEAR:
		{
			return cloner.offset * (double)index;
		}
		case ClonerSettings::RADIAL:
		{
			if (cloner.count <= 1) return CVector3(0.0, 0.0, 0.0);
			double t = (double)index / (double)(cloner.count - 1);
			double angle = cloner.startAngle + (cloner.endAngle - cloner.startAngle) * t;

			switch (cloner.plane)
			{
				case 0: // XY plane
					return CVector3(cos(angle) * cloner.radius, sin(angle) * cloner.radius, 0.0);
				case 1: // XZ plane
					return CVector3(cos(angle) * cloner.radius, 0.0, sin(angle) * cloner.radius);
				case 2: // YZ plane
					return CVector3(0.0, cos(angle) * cloner.radius, sin(angle) * cloner.radius);
				default: return CVector3(0.0, 0.0, 0.0);
			}
		}
		case ClonerSettings::GRID:
		{
			int countX = (int)cloner.gridCount.x;
			int countY = (int)cloner.gridCount.y;
			int countZ = (int)cloner.gridCount.z;

			if (countX < 1) countX = 1;
			if (countY < 1) countY = 1;
			if (countZ < 1) countZ = 1;

			int x = index % countX;
			int y = (index / countX) % countY;
			int z = index / (countX * countY);

			double stepX = cloner.gridSize.x / (countX > 1 ? countX - 1 : 1);
			double stepY = cloner.gridSize.y / (countY > 1 ? countY - 1 : 1);
			double stepZ = cloner.gridSize.z / (countZ > 1 ? countZ - 1 : 1);

			return CVector3(x * stepX, y * stepY, z * stepZ);
		}
		default: return CVector3(0.0, 0.0, 0.0);
	}
}

CVector3 sPrimitiveBasic::ApplyCloneTransform(int index, CVector3 &rotation, CVector3 &scale) const
{
	CVector3 position = CalculateCloneOffset(index);
	CVector3 rot = CVector3(0.0, 0.0, 0.0);
	CVector3 scl = CVector3(1.0, 1.0, 1.0);

	for (int i = 0; i < maxEffectors; i++)
	{
		if (effectors[i] && effectors[i]->enabled)
		{
			effectors[i]->Apply(index, position, rot, scl);
		}
	}

	rotation = rotation + rot;
	scale = CVector3(scale.x * scl.x, scale.y * scl.y, scale.z * scl.z);
	return position;
}

void sPrimitiveBasic::RandomEffector::Apply(int index, CVector3 &position, CVector3 &rotation,
	CVector3 &scale) const
{
	if (!enabled || strength < 1e-10) return;

	// Simple pseudo-random based on seed + index
	auto randFloat = [](int s, int idx, int comp) -> double {
		unsigned int x = (s * 73856093u) ^ (idx * 19349663u) ^ (comp * 83492791u);
		x = (x << 13) ^ x;
		x = x * (x * x * 15731u + 789221u) + 1376312589u;
		return ((x & 0x7fffffff) / double(0x7fffffff)) * 2.0 - 1.0; // [-1, 1]
	};

	CVector3 posOff(
		randFloat(seed, index, 0) * positionAmp.x,
		randFloat(seed, index, 1) * positionAmp.y,
		randFloat(seed, index, 2) * positionAmp.z);

	CVector3 rotOff(
		randFloat(seed, index, 3) * rotationAmp.x,
		randFloat(seed, index, 4) * rotationAmp.y,
		randFloat(seed, index, 5) * rotationAmp.z);

	CVector3 sclOff(
		1.0 + randFloat(seed, index, 6) * scaleAmp.x,
		1.0 + randFloat(seed, index, 7) * scaleAmp.y,
		1.0 + randFloat(seed, index, 8) * scaleAmp.z);

	switch (mode)
	{
		case POSITION:
			position = position + posOff * strength;
			break;
		case ROTATION:
			rotation = rotation + rotOff * strength;
			break;
		case SCALE:
			scale = CVector3(
				scale.x * (1.0 + (sclOff.x - 1.0) * strength),
				scale.y * (1.0 + (sclOff.y - 1.0) * strength),
				scale.z * (1.0 + (sclOff.z - 1.0) * strength));
			break;
		case ALL:
		default:
			position = position + posOff * strength;
			rotation = rotation + rotOff * strength;
			scale = CVector3(
				scale.x * (1.0 + (sclOff.x - 1.0) * strength),
				scale.y * (1.0 + (sclOff.y - 1.0) * strength),
				scale.z * (1.0 + (sclOff.z - 1.0) * strength));
			break;
	}
}

void sPrimitiveBasic::StepEffector::Apply(int index, CVector3 &position, CVector3 &rotation,
	CVector3 &scale) const
{
	if (!enabled || strength < 1e-10) return;

	double t = index * strength;

	CVector3 posOff(positionStep.x * t, positionStep.y * t, positionStep.z * t);
	CVector3 rotOff(rotationStep.x * t, rotationStep.y * t, rotationStep.z * t);
	CVector3 sclOff(1.0 + scaleStep.x * t, 1.0 + scaleStep.y * t, 1.0 + scaleStep.z * t);

	switch (mode)
	{
		case POSITION:
			position = position + posOff;
			break;
		case ROTATION:
			rotation = rotation + rotOff;
			break;
		case SCALE:
			scale = CVector3(
				scale.x * (1.0 + (sclOff.x - 1.0)),
				scale.y * (1.0 + (sclOff.y - 1.0)),
				scale.z * (1.0 + (sclOff.z - 1.0)));
			break;
		case ALL:
		default:
			position = position + posOff;
			rotation = rotation + rotOff;
			scale = CVector3(
				scale.x * (1.0 + (sclOff.x - 1.0)),
				scale.y * (1.0 + (sclOff.y - 1.0)),
				scale.z * (1.0 + (sclOff.z - 1.0)));
			break;
	}
}

void sPrimitiveBasic::FormulaEffector::Apply(int index, CVector3 &position, CVector3 &rotation,
	CVector3 &scale) const
{
	if (!enabled || strength < 1e-10) return;

	double fi = static_cast<double>(index);
	double sx = 0.0, sy = 0.0, sz = 0.0;
	double rx = 0.0, ry = 0.0, rz = 0.0;
	double scx = 1.0, scy = 1.0, scz = 1.0;

	switch (formulaPreset)
	{
		case 0: // sin wave along X
			sx = sin(fi * 0.5) * strength;
			break;
		case 1: // cos wave along Y
			sy = cos(fi * 0.5) * strength;
			break;
		case 2: // 3D wave
			sx = sin(fi * 0.3) * strength;
			sy = cos(fi * 0.4) * strength;
			sz = sin(fi * 0.5 + 1.0) * strength;
			break;
		case 3: // spiral
			sx = cos(fi * 0.5) * strength;
			sy = sin(fi * 0.5) * strength;
			break;
	}

	CVector3 posOff(sx, sy, sz);
	CVector3 rotOff(rx, ry, rz);
	CVector3 sclOff(scx, scy, scz);

	switch (mode)
	{
		case POSITION:
			position = position + posOff;
			break;
		case ROTATION:
			rotation = rotation + rotOff;
			break;
		case SCALE:
			scale = CVector3(
				scale.x * (1.0 + (sclOff.x - 1.0)),
				scale.y * (1.0 + (sclOff.y - 1.0)),
				scale.z * (1.0 + (sclOff.z - 1.0)));
			break;
		case ALL:
		default:
			position = position + posOff;
			rotation = rotation + rotOff;
			scale = CVector3(
				scale.x * (1.0 + (sclOff.x - 1.0)),
				scale.y * (1.0 + (sclOff.y - 1.0)),
				scale.z * (1.0 + (sclOff.z - 1.0)));
			break;
	}
}

void sPrimitiveBasic::TimeEffector::Apply(int index, CVector3 &position, CVector3 &rotation,
	CVector3 &scale) const
{
	if (!enabled || strength < 1e-10) return;

	// Use system time as animation driver
	// TODO: replace with actual render time when available
	double t = static_cast<double>(QDateTime::currentMSecsSinceEpoch()) * 0.001;
	double phase = t * timeScale + timeOffset + index * 0.1;

	CVector3 posOff(sin(phase) * strength, cos(phase * 1.3) * strength, sin(phase * 0.7) * strength);
	CVector3 rotOff(0.0, 0.0, 0.0);
	CVector3 sclOff(1.0, 1.0, 1.0);

	switch (mode)
	{
		case POSITION:
			position = position + posOff;
			break;
		case ROTATION:
			rotation = rotation + rotOff;
			break;
		case SCALE:
			scale = CVector3(
				scale.x * (1.0 + (sclOff.x - 1.0)),
				scale.y * (1.0 + (sclOff.y - 1.0)),
				scale.z * (1.0 + (sclOff.z - 1.0)));
			break;
		case ALL:
		default:
			position = position + posOff;
			rotation = rotation + rotOff;
			scale = CVector3(
				scale.x * (1.0 + (sclOff.x - 1.0)),
				scale.y * (1.0 + (sclOff.y - 1.0)),
				scale.z * (1.0 + (sclOff.z - 1.0)));
			break;
	}
}

std::vector<sPrimitiveBasic::sPrimitiveWireLine> sPrimitiveBasic::wireFrameShape = {};

void sPrimitiveBasic::InitPrimitiveWireframeShapes()
{
	sPrimitivePlane::InitPrimitiveWireframeShape();
	sPrimitiveBox::InitPrimitiveWireframeShape();
	sPrimitiveSphere::InitPrimitiveWireframeShape();
	sPrimitiveWater::InitPrimitiveWireframeShape();
	sPrimitiveCone::InitPrimitiveWireframeShape();
	sPrimitiveCylinder::InitPrimitiveWireframeShape();
	sPrimitiveTorus::InitPrimitiveWireframeShape();
	sPrimitiveCircle::InitPrimitiveWireframeShape();
	sPrimitiveRectangle::InitPrimitiveWireframeShape();
	sPrimitivePrism::InitPrimitiveWireframeShape();
	sPrimitiveEllipsoid::InitPrimitiveWireframeShape();
	sPrimitiveCapsule::InitPrimitiveWireframeShape();
	sPrimitiveHexPrism::InitPrimitiveWireframeShape();
	sPrimitiveLavaPlane::InitPrimitiveWireframeShape();
	sPrimitiveOctahedron::InitPrimitiveWireframeShape();
	sPrimitivePyramid::InitPrimitiveWireframeShape();
	sPrimitiveTerrainPlane::InitPrimitiveWireframeShape();
}

sPrimitivePlane::sPrimitivePlane(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
	size = CVector3(1.0, 1.0, 1.0);
}
sPrimitiveBasic::tWireframeShape sPrimitivePlane::wireFrameShape = {};

void sPrimitivePlane::InitPrimitiveWireframeShape()
{
	double meshSize = 1.0;

	for (int i = 0; i < wireframeSegments; i++)
	{
		double delta = (i - wireframeSegments / 2) * meshSize / (wireframeSegments / 2.0);
		wireFrameShape.push_back({{-meshSize, delta, 0.0}, {meshSize, delta, 0.0}});
		wireFrameShape.push_back({{-meshSize, -delta, 0.0}, {meshSize, -delta, 0.0}});
		wireFrameShape.push_back({{delta, -meshSize, 0.0}, {delta, meshSize, 0.0}});
		wireFrameShape.push_back({{-delta, -meshSize, 0.0}, {-delta, meshSize, 0.0}});
	}
}

sPrimitiveBox::sPrimitiveBox(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	rounding = par->Get<double>(fullName + "_rounding");
	repeat = par->Get<CVector3>(fullName + "_repeat");
	size = par->Get<CVector3>(fullName + "_size");
	limitsEnable = par->Get<bool>(fullName + "_limits_enable");
	limitsMax = par->Get<CVector3>(fullName + "_limits_max");
	limitsMin = par->Get<CVector3>(fullName + "_limits_min");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}
sPrimitiveBasic::tWireframeShape sPrimitiveBox::wireFrameShape = {};

void sPrimitiveBox::InitPrimitiveWireframeShape()
{
	wireFrameShape = {
		{{-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5}},
		{{-0.5, -0.5, -0.5}, {-0.5, 0.5, -0.5}},
		{{0.5, 0.5, -0.5}, {0.5, -0.5, -0.5}},
		{{0.5, 0.5, -0.5}, {-0.5, 0.5, -0.5}},

		{{-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5}},
		{{-0.5, -0.5, 0.5}, {-0.5, 0.5, 0.5}},
		{{0.5, 0.5, 0.5}, {0.5, -0.5, 0.5}},
		{{0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5}},

		{{-0.5, -0.5, -0.5}, {-0.5, -0.5, 0.5}},
		{{-0.5, 0.5, -0.5}, {-0.5, 0.5, 0.5}},
		{{0.5, -0.5, -0.5}, {0.5, -0.5, 0.5}},
		{{0.5, 0.5, -0.5}, {0.5, 0.5, 0.5}},

		{{0.1, 0.0, 0.0}, {-0.1, 0.0, 0.0}},
		{{0.0, 0.1, 0.0}, {0.0, -0.1, 0.0}},
		{{0.0, 0.0, 0.1}, {0.0, 0.0, -0.1}},
	};
}

sPrimitiveSphere::sPrimitiveSphere(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	radius = par->Get<double>(fullName + "_radius");
	repeat = par->Get<CVector3>(fullName + "_repeat");
	size = CVector3(radius * 2.0, radius * 2.0, radius * 2.0);
	limitsEnable = par->Get<bool>(fullName + "_limits_enable");
	limitsMax = par->Get<CVector3>(fullName + "_limits_max");
	limitsMin = par->Get<CVector3>(fullName + "_limits_min");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}

sPrimitiveBasic::tWireframeShape sPrimitiveSphere::wireFrameShape = {};

void sPrimitiveSphere::InitPrimitiveWireframeShape()
{
	double r = 0.5;
	double angleStep = 2.0 * M_PI / wireframeSegments;
	for (double alpha = -M_PI * 0.5; alpha < M_PI * 0.5; alpha += angleStep)
	{
		for (double beta = 0.0; beta < 2.0 * M_PI; beta += angleStep)
		{
			double z1 = sin(alpha) * r;
			double r1 = cos(alpha) * r;
			double x1 = r1 * cos(beta);
			double y1 = r1 * sin(beta);
			double x2 = r1 * cos(beta + angleStep);
			double y2 = r1 * sin(beta + angleStep);
			wireFrameShape.push_back({{x1, y1, z1}, {x2, y2, z1}});
			double z3 = sin(alpha + angleStep) * r;
			double r3 = cos(alpha + angleStep) * r;
			double x3 = r3 * cos(beta);
			double y3 = r3 * sin(beta);
			wireFrameShape.push_back({{x1, y1, z1}, {x3, y3, z3}});
		}
	}

	wireFrameShape.push_back({{0.1, 0.0, 0.0}, {-0.1, 0.0, 0.0}});
	wireFrameShape.push_back({{0.0, 0.1, 0.0}, {0.0, -0.1, 0.0}});
	wireFrameShape.push_back({{0.0, 0.0, 0.1}, {0.0, 0.0, -0.1}});
}

sPrimitiveWater::sPrimitiveWater(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	relativeAmplitude = par->Get<double>(fullName + "_relative_amplitude");
	length = par->Get<double>(fullName + "_length");
	animSpeed = par->Get<double>(fullName + "_anim_speed");
	animProgressionSpeed = par->Get<double>(fullName + "_anim_progression_speed");
	iterations = par->Get<int>(fullName + "_iterations");
	waveFromObjectsEnable = par->Get<bool>(fullName + "_wave_from_objects_enable");
	waveFromObjectsRelativeAmplitude =
		par->Get<double>(fullName + "_wave_from_objects_relative_amplitude");
	animFrame = par->Get<int>("frame_no");
	size = CVector3(length * 10.0, length * 10.0, length * relativeAmplitude);
	limitsEnable = par->Get<bool>(fullName + "_limits_enable");
	limitsMax = par->Get<CVector3>(fullName + "_limits_max");
	limitsMin = par->Get<CVector3>(fullName + "_limits_min");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}

sPrimitiveBasic::tWireframeShape sPrimitiveWater::wireFrameShape = {};

void sPrimitiveWater::InitPrimitiveWireframeShape()
{
	double meshSize = 1.0;

	for (int mx = 0; mx < wireframeSegments; mx++)
	{
		double deltaX1 = (mx - wireframeSegments / 2) * meshSize / (wireframeSegments / 2.0);
		double deltaX2 = (mx + 1 - wireframeSegments / 2) * meshSize / (wireframeSegments / 2.0);

		for (int my = 0; my < wireframeSegments; my++)
		{
			double deltaY1 = (my - wireframeSegments / 2) * meshSize / (wireframeSegments / 2.0);
			double deltaY2 = (my + 1 - wireframeSegments / 2) * meshSize / (wireframeSegments / 2.0);
			{
				auto wave = [](double x, double y) { return sin(x * 23.0) + cos(y * 4.3); };

				double z1 = wave(deltaX1, deltaY1);
				double z2 = wave(deltaX2, deltaY1);
				double z3 = wave(deltaX1, deltaY2);

				wireFrameShape.push_back({{deltaX1, deltaY1, z1}, {deltaX2, deltaY1, z2}});
				wireFrameShape.push_back({{deltaX1, deltaY1, z1}, {deltaX1, deltaY2, z3}});
			}
		}
	}
}

sPrimitiveCone::sPrimitiveCone(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	caps = par->Get<bool>(fullName + "_caps");
	empty = par->Get<bool>(fullName + "_empty");
	radius = par->Get<double>(fullName + "_radius");
	height = par->Get<double>(fullName + "_height");
	repeat = par->Get<CVector3>(fullName + "_repeat");
	wallNormal = CVector2<double>(1.0, radius / height);
	wallNormal.Normalize();
	size = CVector3(radius * 2.0, radius * 2.0, height);
	limitsEnable = par->Get<bool>(fullName + "_limits_enable");
	limitsMax = par->Get<CVector3>(fullName + "_limits_max");
	limitsMin = par->Get<CVector3>(fullName + "_limits_min");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}

sPrimitiveBasic::tWireframeShape sPrimitiveCone::wireFrameShape = {};

void sPrimitiveCone::InitPrimitiveWireframeShape()
{
	double r = 0.5;
	double angleStep = 2.0 * M_PI / wireframeSegments;

	for (double alpha = 0.0; alpha < 2.0 * M_PI; alpha += angleStep)
	{
		double z1 = 0.0;
		double z2 = 1.0;
		double x1 = cos(alpha) * r;
		double y1 = sin(alpha) * r;
		double x2 = cos(alpha + angleStep) * r;
		double y2 = sin(alpha + angleStep) * r;
		wireFrameShape.push_back({{x1, y1, z1}, {0.0, 0.0, z2}});
		wireFrameShape.push_back({{x1, y1, z1}, {x2, y2, z1}});
		wireFrameShape.push_back({{x1, y1, z1}, {0.0, 0.0, z1}});
	}
}

sPrimitiveCylinder::sPrimitiveCylinder(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	caps = par->Get<bool>(fullName + "_caps");
	empty = par->Get<bool>(fullName + "_empty");
	radius = par->Get<double>(fullName + "_radius");
	height = par->Get<double>(fullName + "_height");
	repeat = par->Get<CVector3>(fullName + "_repeat");
	size = CVector3(radius * 2.0, radius * 2.0, height);
	limitsEnable = par->Get<bool>(fullName + "_limits_enable");
	limitsMax = par->Get<CVector3>(fullName + "_limits_max");
	limitsMin = par->Get<CVector3>(fullName + "_limits_min");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}

sPrimitiveBasic::tWireframeShape sPrimitiveCylinder::wireFrameShape = {};

void sPrimitiveCylinder::InitPrimitiveWireframeShape()
{
	double r = 0.5;
	double angleStep = 2.0 * M_PI / wireframeSegments;

	for (double alpha = 0.0; alpha < 2.0 * M_PI; alpha += angleStep)
	{
		double z1 = -0.5;
		double z2 = 0.5;
		double x1 = cos(alpha) * r;
		double y1 = sin(alpha) * r;
		double x2 = cos(alpha + angleStep) * r;
		double y2 = sin(alpha + angleStep) * r;
		wireFrameShape.push_back({{x1, y1, z1}, {x1, y1, z2}});
		wireFrameShape.push_back({{x1, y1, z1}, {x2, y2, z1}});
		wireFrameShape.push_back({{x1, y1, z2}, {x2, y2, z2}});
		wireFrameShape.push_back({{x1, y1, z1}, {0.0, 0.0, z1}});
		wireFrameShape.push_back({{x1, y1, z2}, {0.0, 0.0, z2}});
	}

	wireFrameShape.push_back({{0.1, 0.0, 0.0}, {-0.1, 0.0, 0.0}});
	wireFrameShape.push_back({{0.0, 0.1, 0.0}, {0.0, -0.1, 0.0}});
	wireFrameShape.push_back({{0.0, 0.0, 0.1}, {0.0, 0.0, -0.1}});
}

sPrimitiveTorus::sPrimitiveTorus(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	radius = par->Get<double>(fullName + "_radius");
	radiusLPow = par->Get<double>(fullName + "_radius_lpow");
	tubeRadius = par->Get<double>(fullName + "_tube_radius");
	tubeRadiusLPow = par->Get<double>(fullName + "_tube_radius_lpow");
	repeat = par->Get<CVector3>(fullName + "_repeat");
	size = CVector3((radius + tubeRadius) * 2.0, (radius + tubeRadius) * 2.0, tubeRadius);
	limitsEnable = par->Get<bool>(fullName + "_limits_enable");
	limitsMax = par->Get<CVector3>(fullName + "_limits_max");
	limitsMin = par->Get<CVector3>(fullName + "_limits_min");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}

sPrimitiveBasic::tWireframeShape sPrimitiveTorus::wireFrameShape = {};

void sPrimitiveTorus::InitPrimitiveWireframeShape()
{
	// just cross in the center
	wireFrameShape.push_back({{0.1, 0.0, 0.0}, {-0.1, 0.0, 0.0}});
	wireFrameShape.push_back({{0.0, 0.1, 0.0}, {0.0, -0.1, 0.0}});
	wireFrameShape.push_back({{0.0, 0.0, 0.1}, {0.0, 0.0, -0.1}});
}

sPrimitiveRectangle::sPrimitiveRectangle(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	height = par->Get<double>(fullName + "_height");
	width = par->Get<double>(fullName + "_width");
	size = CVector3(width, height, 1.0);
}

sPrimitiveBasic::tWireframeShape sPrimitiveRectangle::wireFrameShape = {};

void sPrimitiveRectangle::InitPrimitiveWireframeShape()
{
	wireFrameShape = {
		{{-0.5, -0.5, 0.0}, {0.5, -0.5, 0.0}},
		{{0.5, -0.5, 0.0}, {0.5, 0.5, 0.0}},
		{{0.5, 0.5, 0.0}, {-0.5, 0.5, 0.0}},
		{{-0.5, 0.5, 0.0}, {-0.5, -0.5, 0.0}},

		{{0.1, 0.0, 0.0}, {-0.1, 0.0, 0.0}},
		{{0.0, 0.1, 0.0}, {0.0, -0.1, 0.0}},
		{{0.0, 0.0, 0.1}, {0.0, 0.0, -0.1}},
	};
}

sPrimitiveCircle::sPrimitiveCircle(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	radius = par->Get<double>(fullName + "_radius");
	size = CVector3(radius * 2.0, radius * 2.0, 1.0);
}

sPrimitiveBasic::tWireframeShape sPrimitiveCircle::wireFrameShape = {};

void sPrimitiveCircle::InitPrimitiveWireframeShape()
{
	double r = 0.5;
	double angleStep = 2.0 * M_PI / wireframeSegments;

	for (double alpha = 0.0; alpha < 2.0 * M_PI; alpha += angleStep)
	{
		double z = 0.0;
		double x1 = cos(alpha) * r;
		double y1 = sin(alpha) * r;
		double x2 = cos(alpha + angleStep) * r;
		double y2 = sin(alpha + angleStep) * r;
		wireFrameShape.push_back({{x1, y1, z}, {x2, y2, z}});
		wireFrameShape.push_back({{x1, y1, z}, {0.0, 0.0, z}});
	}
}

sPrimitivePrism::sPrimitivePrism(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	height = par->Get<double>(fullName + "_height") / 2.0;
	prismAngle = par->Get<double>(fullName + "_prism_angle") * M_PI / 180.0 / 2.0;
	triangleHeight = par->Get<double>(fullName + "_trangle_height") * sin(prismAngle);
	repeat = par->Get<CVector3>(fullName + "_repeat");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
	normals = CVector3(sin(prismAngle), cos(prismAngle), sin(prismAngle));
	size =
		CVector3(tan(prismAngle / 2.0) * triangleHeight * 4.0 / normals.x, triangleHeight / normals.x,
			height * 2.0); // FIXME correct size
}
sPrimitiveBasic::tWireframeShape sPrimitivePrism::wireFrameShape = {};

void sPrimitivePrism::InitPrimitiveWireframeShape()
{
	wireFrameShape = {
		{{0.0, 1.0, -0.5}, {0.0, 1.0, 0.5}},
		{{-0.5, 0.0, -0.5}, {-0.5, 0.0, 0.5}},
		{{0.5, 0.0, -0.5}, {0.5, 0.0, 0.5}},

		{{-0.5, 0.0, -0.5}, {0.0, 1.0, -0.5}},
		{{0.5, 0.0, -0.5}, {0.0, 1.0, -0.5}},
		{{-0.5, 0.0, -0.5}, {0.5, 0.0, -0.5}},

		{{-0.5, 0.0, 0.5}, {0.0, 1.0, 0.5}},
		{{0.5, 0.0, 0.5}, {0.0, 1.0, 0.5}},
		{{-0.5, 0.0, 0.5}, {0.5, 0.0, 0.5}},

		{{0.1, 0.0, 0.0}, {-0.1, 0.0, 0.0}},
		{{0.0, 0.1, 0.0}, {0.0, -0.1, 0.0}},
		{{0.0, 0.0, 0.1}, {0.0, 0.0, -0.1}},
	};
}

sPrimitiveEllipsoid::sPrimitiveEllipsoid(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	repeat = par->Get<CVector3>(fullName + "_repeat");
	size = par->Get<CVector3>(fullName + "_size");
	limitsEnable = par->Get<bool>(fullName + "_limits_enable");
	limitsMax = par->Get<CVector3>(fullName + "_limits_max");
	limitsMin = par->Get<CVector3>(fullName + "_limits_min");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}

sPrimitiveBasic::tWireframeShape sPrimitiveEllipsoid::wireFrameShape = {};

void sPrimitiveEllipsoid::InitPrimitiveWireframeShape()
{
	double r = 1.0;
	double angleStep = 2.0 * M_PI / wireframeSegments;
	for (double alpha = -M_PI * 0.5; alpha < M_PI * 0.5; alpha += angleStep)
	{
		for (double beta = 0.0; beta < 2.0 * M_PI; beta += angleStep)
		{
			double z1 = sin(alpha) * r;
			double r1 = cos(alpha) * r;
			double x1 = r1 * cos(beta);
			double y1 = r1 * sin(beta);
			double x2 = r1 * cos(beta + angleStep);
			double y2 = r1 * sin(beta + angleStep);
			wireFrameShape.push_back({{x1, y1, z1}, {x2, y2, z1}});
			double z3 = sin(alpha + angleStep) * r;
			double r3 = cos(alpha + angleStep) * r;
			double x3 = r3 * cos(beta);
			double y3 = r3 * sin(beta);
			wireFrameShape.push_back({{x1, y1, z1}, {x3, y3, z3}});
		}
	}

	wireFrameShape.push_back({{0.1, 0.0, 0.0}, {-0.1, 0.0, 0.0}});
	wireFrameShape.push_back({{0.0, 0.1, 0.0}, {0.0, -0.1, 0.0}});
	wireFrameShape.push_back({{0.0, 0.0, 0.1}, {0.0, 0.0, -0.1}});
}

double sPrimitivePlane::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = primitiveScale.x;
	if (primitiveScale.y < minScale) minScale = primitiveScale.y;
	if (primitiveScale.z < minScale) minScale = primitiveScale.z;
	// Apply deformations AFTER rotation
	point = ApplyDeformations(point);
	double dist = point.z;
	dist = empty ? fabs(dist) : dist;
	dist = max(dist - wallThickness, 0.0);
	return dist * minScale;
}

double sPrimitiveBox::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	CVector3 pointRepeated;
	switch (repeatMode)
	{
		case 0: pointRepeated = point.repeatMod(repeat); break;
		case 1: pointRepeated = point.repeatModMirror(repeat); break;
		case 2: pointRepeated = point.repeatModRotation(repeat, repeatRotationStep); break;
		case 3: pointRepeated = point.repeatModFibonacci(repeatFibonacciCount, repeatFibonacciSpread); break;
		case 4: pointRepeated = point.repeatModBrick(repeat); break;
		case 7: pointRepeated = point.repeatModHoneycomb(repeat); break;
		case 12: pointRepeated = point.repeatModSpiral(repeat, repeatSpiralStep, repeatSpiralAngle, repeatSpiralRadius); break;
		case 13: pointRepeated = point.repeatModWave(repeat, repeatWaveAmplitude, repeatWaveFrequency, repeatWavePhase, repeatWaveAxis); break;
		default: pointRepeated = point.repeatMod(repeat); break;
	}
	point = pointRepeated;
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = primitiveScale.x;
	if (primitiveScale.y < minScale) minScale = primitiveScale.y;
	if (primitiveScale.z < minScale) minScale = primitiveScale.z;

	// Apply deformations AFTER rotation
	point = ApplyDeformations(point);
	double boxDist = -1e10;

	if (empty)
	{
		boxDist = max(fabs(point.x) - size.x * 0.5, boxDist);
		boxDist = max(fabs(point.y) - size.y * 0.5, boxDist);
		boxDist = max(fabs(point.z) - size.z * 0.5, boxDist);
		boxDist = fabs(boxDist);
	}
	else
	{
		CVector3 boxTemp;
		boxTemp.x = max(fabs(point.x) - size.x * 0.5, 0.0);
		boxTemp.y = max(fabs(point.y) - size.y * 0.5, 0.0);
		boxTemp.z = max(fabs(point.z) - size.z * 0.5, 0.0);
		boxDist = boxTemp.Length() - rounding;
	}

	boxDist = max(boxDist - wallThickness, 0.0);

	if (limitsEnable)
	{
		CVector3 distanceAxial = max(point - limitsMax, limitsMin - point);
		double limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		boxDist = max(boxDist, limitBoxDist);
	}

	return boxDist * minScale;
}

double sPrimitiveSphere::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	CVector3 pointRepeated;
	switch (repeatMode)
	{
		case 0: pointRepeated = point.repeatMod(repeat); break;
		case 1: pointRepeated = point.repeatModMirror(repeat); break;
		case 2: pointRepeated = point.repeatModRotation(repeat, repeatRotationStep); break;
		case 3: pointRepeated = point.repeatModFibonacci(repeatFibonacciCount, repeatFibonacciSpread); break;
		case 4: pointRepeated = point.repeatModBrick(repeat); break;
		case 7: pointRepeated = point.repeatModHoneycomb(repeat); break;
		case 12: pointRepeated = point.repeatModSpiral(repeat, repeatSpiralStep, repeatSpiralAngle, repeatSpiralRadius); break;
		case 13: pointRepeated = point.repeatModWave(repeat, repeatWaveAmplitude, repeatWaveFrequency, repeatWavePhase, repeatWaveAxis); break;
		default: pointRepeated = point.repeatMod(repeat); break;
	}
	point = pointRepeated;
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = primitiveScale.x;
	if (primitiveScale.y < minScale) minScale = primitiveScale.y;
	if (primitiveScale.z < minScale) minScale = primitiveScale.z;
	// Apply deformations AFTER rotation
	point = ApplyDeformations(point);
	double dist = point.Length() - radius;
	dist = empty ? fabs(dist) : dist;
	dist = max(dist - wallThickness, 0.0);
	if (limitsEnable)
	{
		CVector3 distanceAxial = max(point - limitsMax, limitsMin - point);
		double limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist * minScale;
}

double sPrimitiveRectangle::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = primitiveScale.x;
	if (primitiveScale.y < minScale) minScale = primitiveScale.y;
	if (primitiveScale.z < minScale) minScale = primitiveScale.z;
	// Apply deformations AFTER rotation
	point = ApplyDeformations(point);
	CVector3 boxTemp;
	boxTemp.x = max(fabs(point.x) - width * 0.5, 0.0);
	boxTemp.y = max(fabs(point.y) - height * 0.5, 0.0);
	boxTemp.z = fabs(point.z);
	return boxTemp.Length() * minScale;
}

double sPrimitiveCylinder::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	CVector3 pointRepeated;
	switch (repeatMode)
	{
		case 0: pointRepeated = point.repeatMod(repeat); break;
		case 1: pointRepeated = point.repeatModMirror(repeat); break;
		case 2: pointRepeated = point.repeatModRotation(repeat, repeatRotationStep); break;
		case 3: pointRepeated = point.repeatModFibonacci(repeatFibonacciCount, repeatFibonacciSpread); break;
		case 4: pointRepeated = point.repeatModBrick(repeat); break;
		case 7: pointRepeated = point.repeatModHoneycomb(repeat); break;
		case 12: pointRepeated = point.repeatModSpiral(repeat, repeatSpiralStep, repeatSpiralAngle, repeatSpiralRadius); break;
		case 13: pointRepeated = point.repeatModWave(repeat, repeatWaveAmplitude, repeatWaveFrequency, repeatWavePhase, repeatWaveAxis); break;
		default: pointRepeated = point.repeatMod(repeat); break;
	}
	point = pointRepeated;
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = primitiveScale.x;
	if (primitiveScale.y < minScale) minScale = primitiveScale.y;
	if (primitiveScale.z < minScale) minScale = primitiveScale.z;
	// Apply deformations AFTER rotation
	point = ApplyDeformations(point);

	CVector2<double> cylTemp(point.x, point.y);
	double dist = cylTemp.Length() - radius;
	if (!caps) dist = fabs(dist);
	dist = max(fabs(point.z) - height * 0.5, dist);
	dist = empty ? fabs(dist) : dist;
	dist = max(dist - wallThickness, 0.0);
	if (limitsEnable)
	{
		CVector3 distanceAxial = max(point - limitsMax, limitsMin - point);
		double limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist * minScale;
}

double sPrimitiveCircle::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = primitiveScale.x;
	if (primitiveScale.y < minScale) minScale = primitiveScale.y;
	if (primitiveScale.z < minScale) minScale = primitiveScale.z;
	// Apply deformations AFTER rotation
	point = ApplyDeformations(point);
	CVector2<double> circleTemp(point.x, point.y);
	double distTemp = circleTemp.Length() - radius;
	distTemp = max(fabs(point.z), distTemp);
	return distTemp * minScale;
}

double sPrimitiveCone::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	CVector3 pointRepeated;
	switch (repeatMode)
	{
		case 0: pointRepeated = point.repeatMod(repeat); break;
		case 1: pointRepeated = point.repeatModMirror(repeat); break;
		case 2: pointRepeated = point.repeatModRotation(repeat, repeatRotationStep); break;
		case 3: pointRepeated = point.repeatModFibonacci(repeatFibonacciCount, repeatFibonacciSpread); break;
		case 4: pointRepeated = point.repeatModBrick(repeat); break;
		case 7: pointRepeated = point.repeatModHoneycomb(repeat); break;
		case 12: pointRepeated = point.repeatModSpiral(repeat, repeatSpiralStep, repeatSpiralAngle, repeatSpiralRadius); break;
		case 13: pointRepeated = point.repeatModWave(repeat, repeatWaveAmplitude, repeatWaveFrequency, repeatWavePhase, repeatWaveAxis); break;
		default: pointRepeated = point.repeatMod(repeat); break;
	}
	point = pointRepeated;
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = primitiveScale.x;
	if (primitiveScale.y < minScale) minScale = primitiveScale.y;
	if (primitiveScale.z < minScale) minScale = primitiveScale.z;
	// Apply deformations AFTER rotation
	point = ApplyDeformations(point);

	point.z -= height;
	double q = sqrt(point.x * point.x + point.y * point.y);
	CVector2<double> vect(q, point.z);
	double dist = wallNormal.Dot(vect);
	if (!caps) dist = fabs(dist);
	dist = max(-point.z - height, dist);
	dist = empty ? fabs(dist) : dist;
	dist = max(dist - wallThickness, 0.0);
	if (limitsEnable)
	{
		CVector3 distanceAxial = max(point - limitsMax, limitsMin - point);
		double limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist * minScale;
}

double sPrimitiveWater::PrimitiveDistance(CVector3 _point) const
{
	Q_UNUSED(_point);
	return 0.0;
}

double sPrimitiveWater::PrimitiveDistanceWater(CVector3 _point, double distanceFromAnother) const
{
	// TODO to use rendering technique from here: //https://www.shadertoy.com/view/Ms2SD1

	// NEW TRANSFORMATION ORDER: pivot as world space coordinate
	CVector3 point = _point - pivot;
	point = rotationMatrix.RotateVector(point);
	point = point + pivot;
	point = point - position;

	if (waveFromObjectsEnable)
	{
		point.x +=
			length * 20.0 * exp(-distanceFromAnother / length / 5.0) * waveFromObjectsRelativeAmplitude;
	}

	double amplitude = length * relativeAmplitude;
	double objectWave = 0.0;

	double planeDistance = point.z;
	if (planeDistance < amplitude * 10.0)
	{
		double phase = -animSpeed * animFrame * 0.1;

		if (waveFromObjectsEnable)
		{
			objectWave = sin(distanceFromAnother / length * 5.0 - phase * 2.0)
									 * exp(-distanceFromAnother / length / 5.0) * waveFromObjectsRelativeAmplitude;
		}

		double k = 0.23;
		double waveXTemp;
		double waveYTemp;
		double waveX = objectWave;
		double waveY = -objectWave;
		double p = 1.0;
		double p2 = 0.05;

		point.x += phase * 0.05
							 * (animProgressionSpeed * 3.0
									- 3.0); // 3.0 to keep compatibility and to have 0.0 stopping moving

		for (int i = 1; i <= iterations; i++)
		{
			float p3 = p * p2;
			float shift = phase / (i / 2.697 + 1.0);
			waveXTemp = sin(i + 0.4 * (waveX)*p3 + sin(k * point.y / length * p3 + shift * 0.134 * p3)
											+ point.x / length * p3 + shift * p3)
									/ p;
			waveYTemp = cos(i + 0.4 * (waveY)*p3 + sin(point.x / length * p3 + shift * 0.0179 * p3)
											+ k * point.y / length * p3 + shift * 0.023 * p3)
									/ p;
			waveX += waveXTemp;
			waveY += waveYTemp;
			p2 = p2 + (1.0 - p2 + 0.5 * sin(shift * 0.0323)) * 0.7;
			p *= 1.872;
		}

		planeDistance += (waveX + waveY) * amplitude;
	}

	planeDistance = empty ? fabs(planeDistance) : planeDistance;

	planeDistance = max(planeDistance - wallThickness, 0.0);

	if (limitsEnable)
	{
		CVector3 distanceAxial = max(point - limitsMax, limitsMin - point);
		double limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		planeDistance = max(planeDistance, limitBoxDist);
	}
	return planeDistance;
}

double sPrimitiveTorus::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	CVector3 pointRepeated;
	switch (repeatMode)
	{
		case 0: pointRepeated = point.repeatMod(repeat); break;
		case 1: pointRepeated = point.repeatModMirror(repeat); break;
		case 2: pointRepeated = point.repeatModRotation(repeat, repeatRotationStep); break;
		case 3: pointRepeated = point.repeatModFibonacci(repeatFibonacciCount, repeatFibonacciSpread); break;
		case 4: pointRepeated = point.repeatModBrick(repeat); break;
		case 7: pointRepeated = point.repeatModHoneycomb(repeat); break;
		case 12: pointRepeated = point.repeatModSpiral(repeat, repeatSpiralStep, repeatSpiralAngle, repeatSpiralRadius); break;
		case 13: pointRepeated = point.repeatModWave(repeat, repeatWaveAmplitude, repeatWaveFrequency, repeatWavePhase, repeatWaveAxis); break;
		default: pointRepeated = point.repeatMod(repeat); break;
	}
	point = pointRepeated;
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = primitiveScale.x;
	if (primitiveScale.y < minScale) minScale = primitiveScale.y;
	if (primitiveScale.z < minScale) minScale = primitiveScale.z;
	// Apply deformations AFTER rotation
	point = ApplyDeformations(point);

	double d1 = CVector2<double>(point.x, point.y).LengthPow(pow(2, radiusLPow)) - radius;
	double dist = CVector2<double>(d1, point.z).LengthPow(pow(2, tubeRadiusLPow)) - tubeRadius;

	dist = empty ? fabs(dist) : dist;
	dist = max(dist - wallThickness, 0.0);

	if (limitsEnable)
	{
		CVector3 distanceAxial = max(point - limitsMax, limitsMin - point);
		double limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist * minScale;
}

double sPrimitivePrism::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	CVector3 pointRepeated;
	switch (repeatMode)
	{
		case 0: pointRepeated = point.repeatMod(repeat); break;
		case 1: pointRepeated = point.repeatModMirror(repeat); break;
		case 2: pointRepeated = point.repeatModRotation(repeat, repeatRotationStep); break;
		case 3: pointRepeated = point.repeatModFibonacci(repeatFibonacciCount, repeatFibonacciSpread); break;
		case 4: pointRepeated = point.repeatModBrick(repeat); break;
		case 7: pointRepeated = point.repeatModHoneycomb(repeat); break;
		case 12: pointRepeated = point.repeatModSpiral(repeat, repeatSpiralStep, repeatSpiralAngle, repeatSpiralRadius); break;
		case 13: pointRepeated = point.repeatModWave(repeat, repeatWaveAmplitude, repeatWaveFrequency, repeatWavePhase, repeatWaveAxis); break;
		default: pointRepeated = point.repeatMod(repeat); break;
	}
	point = pointRepeated;
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = primitiveScale.x;
	if (primitiveScale.y < minScale) minScale = primitiveScale.y;
	if (primitiveScale.z < minScale) minScale = primitiveScale.z;
	// Apply deformations AFTER rotation
	point = ApplyDeformations(point);

	CVector3 q = fabs(point);

	double dist = max(q.z - height,
		max(q.x * normals.y + point.y * normals.z, -point.y + triangleHeight) - triangleHeight);

	dist = empty ? fabs(dist) : dist;
	dist = max(dist - wallThickness, 0.0);

	return dist * minScale;
}

double sPrimitiveEllipsoid::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	CVector3 pointRepeated;
	switch (repeatMode)
	{
		case 0: pointRepeated = point.repeatMod(repeat); break;
		case 1: pointRepeated = point.repeatModMirror(repeat); break;
		case 2: pointRepeated = point.repeatModRotation(repeat, repeatRotationStep); break;
		case 3: pointRepeated = point.repeatModFibonacci(repeatFibonacciCount, repeatFibonacciSpread); break;
		case 4: pointRepeated = point.repeatModBrick(repeat); break;
		case 7: pointRepeated = point.repeatModHoneycomb(repeat); break;
		case 12: pointRepeated = point.repeatModSpiral(repeat, repeatSpiralStep, repeatSpiralAngle, repeatSpiralRadius); break;
		case 13: pointRepeated = point.repeatModWave(repeat, repeatWaveAmplitude, repeatWaveFrequency, repeatWavePhase, repeatWaveAxis); break;
		default: pointRepeated = point.repeatMod(repeat); break;
	}
	point = pointRepeated;
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = primitiveScale.x;
	if (primitiveScale.y < minScale) minScale = primitiveScale.y;
	if (primitiveScale.z < minScale) minScale = primitiveScale.z;
	// Apply deformations AFTER rotation
	point = ApplyDeformations(point);

	float k0 = (point / size).Length();
	float k1 = (point / (size * size)).Length();
	double dist = k0 * (k0 - 1.0) / k1;

	dist = empty ? fabs(dist) : dist;
	dist = max(dist - wallThickness, 0.0);

	if (limitsEnable)
	{
		CVector3 distanceAxial = max(point - limitsMax, limitsMin - point);
		double limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist * minScale;
}

// ========== Capsule ==========
sPrimitiveCapsule::sPrimitiveCapsule(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	radius = par->Get<double>(fullName + "_radius");
	height = par->Get<double>(fullName + "_height");
	repeat = par->Get<CVector3>(fullName + "_repeat");
	limitsEnable = par->Get<bool>(fullName + "_limits_enable");
	limitsMax = par->Get<CVector3>(fullName + "_limits_max");
	limitsMin = par->Get<CVector3>(fullName + "_limits_min");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}

sPrimitiveBasic::tWireframeShape sPrimitiveCapsule::wireFrameShape = {};
void sPrimitiveCapsule::InitPrimitiveWireframeShape()
{
	double r = 1.0, h = 0.5;
	double angleStep = 2.0 * M_PI / wireframeSegments;
	for (double beta = 0.0; beta < 2.0 * M_PI; beta += angleStep)
	{
		double x1 = r * cos(beta), y1 = r * sin(beta);
		double x2 = r * cos(beta + angleStep), y2 = r * sin(beta + angleStep);
		wireFrameShape.push_back({{x1, y1, -h}, {x2, y2, -h}});
		wireFrameShape.push_back({{x1, y1, h}, {x2, y2, h}});
		wireFrameShape.push_back({{x1, y1, -h}, {x1, y1, h}});
	}
}

double sPrimitiveCapsule::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = std::min({primitiveScale.x, primitiveScale.y, primitiveScale.z});
	point = ApplyDeformations(point);
	double halfH = height * 0.5;
	point.z -= std::max(-halfH, std::min(point.z, halfH));
	double dist = CVector3(point.x, point.y, point.z).Length() - radius;
	dist = empty ? fabs(dist) : dist;
	dist = std::max(dist - wallThickness, 0.0);
	if (limitsEnable)
	{
		CVector3 distanceAxial = max(point - limitsMax, limitsMin - point);
		double limitBoxDist = std::max({distanceAxial.x, distanceAxial.y, distanceAxial.z});
		dist = std::max(dist, limitBoxDist);
	}
	return dist * minScale;
}

// ========== HexPrism ==========
sPrimitiveHexPrism::sPrimitiveHexPrism(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	height = par->Get<double>(fullName + "_height");
	repeat = par->Get<CVector3>(fullName + "_repeat");
	size = par->Get<CVector3>(fullName + "_size");
	limitsEnable = par->Get<bool>(fullName + "_limits_enable");
	limitsMax = par->Get<CVector3>(fullName + "_limits_max");
	limitsMin = par->Get<CVector3>(fullName + "_limits_min");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}

sPrimitiveBasic::tWireframeShape sPrimitiveHexPrism::wireFrameShape = {};
void sPrimitiveHexPrism::InitPrimitiveWireframeShape()
{
	double r = 1.0, h = 0.5;
	for (int i = 0; i < 6; i++)
	{
		double a1 = i * M_PI / 3.0, a2 = (i + 1) * M_PI / 3.0;
		double x1 = r * cos(a1), y1 = r * sin(a1);
		double x2 = r * cos(a2), y2 = r * sin(a2);
		wireFrameShape.push_back({{x1, y1, -h}, {x2, y2, -h}});
		wireFrameShape.push_back({{x1, y1, h}, {x2, y2, h}});
		wireFrameShape.push_back({{x1, y1, -h}, {x1, y1, h}});
	}
}

double sPrimitiveHexPrism::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = std::min({primitiveScale.x, primitiveScale.y, primitiveScale.z});
	point = ApplyDeformations(point);
	double r = size.x;
	CVector3 absP(fabs(point.x), fabs(point.y), fabs(point.z));
	double k = -0.8660254037844386; // -sqrt(3)/2
	double px = absP.x, py = absP.y;
	double t = 2.0 * std::min(k * px + 0.5 * py, 0.0);
	px -= t * k;
	py -= t * 0.5;
	px -= std::max(-r, std::min(px, r));
	double d2d = sqrt(px * px + std::max(py - r, 0.0) * std::max(py - r, 0.0))
		* ((py - r > 0.0) ? 1.0 : -1.0);
	double dist = std::max(d2d, absP.z - height * 0.5);
	dist = empty ? fabs(dist) : dist;
	dist = std::max(dist - wallThickness, 0.0);
	if (limitsEnable)
	{
		CVector3 distanceAxial = max(point - limitsMax, limitsMin - point);
		double limitBoxDist = std::max({distanceAxial.x, distanceAxial.y, distanceAxial.z});
		dist = std::max(dist, limitBoxDist);
	}
	return dist * minScale;
}

// ========== LavaPlane ==========
sPrimitiveLavaPlane::sPrimitiveLavaPlane(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	waveHeight = par->Get<double>(fullName + "_lava_wave_height");
	waveScale = par->Get<double>(fullName + "_lava_wave_scale");
	waveOctaves = par->Get<int>(fullName + "_lava_wave_octaves");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}

sPrimitiveBasic::tWireframeShape sPrimitiveLavaPlane::wireFrameShape = {};
void sPrimitiveLavaPlane::InitPrimitiveWireframeShape()
{
	double s = 2.0;
	wireFrameShape.push_back({{-s, -s, 0}, {s, -s, 0}});
	wireFrameShape.push_back({{s, -s, 0}, {s, s, 0}});
	wireFrameShape.push_back({{s, s, 0}, {-s, s, 0}});
	wireFrameShape.push_back({{-s, s, 0}, {-s, -s, 0}});
}

double sPrimitiveLavaPlane::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	point = ApplyDeformations(point);
	double displacement = 0.0;
	double freq = 1.0 / std::max(waveScale, 1e-10);
	double amp = waveHeight;
	for (int i = 0; i < waveOctaves; i++)
	{
		displacement += amp * sin(point.x * freq) * cos(point.y * freq);
		freq *= 2.0;
		amp *= 0.5;
	}
	double dist = point.z - displacement;
	dist = empty ? fabs(dist) : dist;
	return dist;
}

// ========== Octahedron ==========
sPrimitiveOctahedron::sPrimitiveOctahedron(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	size = par->Get<CVector3>(fullName + "_size");
	repeat = par->Get<CVector3>(fullName + "_repeat");
	limitsEnable = par->Get<bool>(fullName + "_limits_enable");
	limitsMax = par->Get<CVector3>(fullName + "_limits_max");
	limitsMin = par->Get<CVector3>(fullName + "_limits_min");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}

sPrimitiveBasic::tWireframeShape sPrimitiveOctahedron::wireFrameShape = {};
void sPrimitiveOctahedron::InitPrimitiveWireframeShape()
{
	double s = 1.0;
	CVector3 top(0, 0, s), bot(0, 0, -s);
	CVector3 v[4] = {{s, 0, 0}, {0, s, 0}, {-s, 0, 0}, {0, -s, 0}};
	for (int i = 0; i < 4; i++)
	{
		int j = (i + 1) % 4;
		wireFrameShape.push_back({v[i], v[j]});
		wireFrameShape.push_back({top, v[i]});
		wireFrameShape.push_back({bot, v[i]});
	}
}

double sPrimitiveOctahedron::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = std::min({primitiveScale.x, primitiveScale.y, primitiveScale.z});
	point = ApplyDeformations(point);
	double s = size.x;
	CVector3 absP(fabs(point.x), fabs(point.y), fabs(point.z));
	double dist = (absP.x + absP.y + absP.z - s) * 0.57735026919;
	dist = empty ? fabs(dist) : dist;
	dist = std::max(dist - wallThickness, 0.0);
	if (limitsEnable)
	{
		CVector3 distanceAxial = max(point - limitsMax, limitsMin - point);
		double limitBoxDist = std::max({distanceAxial.x, distanceAxial.y, distanceAxial.z});
		dist = std::max(dist, limitBoxDist);
	}
	return dist * minScale;
}

// ========== Pyramid ==========
sPrimitivePyramid::sPrimitivePyramid(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	height = par->Get<double>(fullName + "_height");
	baseSize = par->Get<double>(fullName + "_base_size");
	size = par->Get<CVector3>(fullName + "_size");
	repeat = par->Get<CVector3>(fullName + "_repeat");
	limitsEnable = par->Get<bool>(fullName + "_limits_enable");
	limitsMax = par->Get<CVector3>(fullName + "_limits_max");
	limitsMin = par->Get<CVector3>(fullName + "_limits_min");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}

sPrimitiveBasic::tWireframeShape sPrimitivePyramid::wireFrameShape = {};
void sPrimitivePyramid::InitPrimitiveWireframeShape()
{
	double s = 1.0, h = 1.0;
	CVector3 apex(0, 0, h);
	CVector3 v[4] = {{-s, -s, 0}, {s, -s, 0}, {s, s, 0}, {-s, s, 0}};
	for (int i = 0; i < 4; i++)
	{
		wireFrameShape.push_back({v[i], v[(i + 1) % 4]});
		wireFrameShape.push_back({apex, v[i]});
	}
}

double sPrimitivePyramid::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	point.x /= primitiveScale.x;
	point.y /= primitiveScale.y;
	point.z /= primitiveScale.z;
	double minScale = std::min({primitiveScale.x, primitiveScale.y, primitiveScale.z});
	point = ApplyDeformations(point);
	double h = std::max(height, 1e-10);
	double b = std::max(baseSize, 1e-10) * 0.5;
	double m2 = h * h / (b * b);
	CVector3 absP(fabs(point.x), fabs(point.y), point.z);
	absP.x -= std::max(-b, std::min(absP.x, b));
	absP.y -= std::max(-b, std::min(absP.y, b));
	double d1 = std::max(absP.x, absP.y);
	double d2 = (point.z - h) * m2 / sqrt(m2 + 1.0);
	double distBase = -point.z;
	double dist = std::max(d1, std::max(d2, distBase));
	dist = empty ? fabs(dist) : dist;
	dist = std::max(dist - wallThickness, 0.0);
	if (limitsEnable)
	{
		CVector3 distanceAxial = max(point - limitsMax, limitsMin - point);
		double limitBoxDist = std::max({distanceAxial.x, distanceAxial.y, distanceAxial.z});
		dist = std::max(dist, limitBoxDist);
	}
	return dist * minScale;
}

// ========== TerrainPlane ==========
// Types: 0=Sand, 1=Mud, 2=Ice, 3=Grass, 4=Rock, 5=Snow,
//        6=Magma, 7=Crystal, 8=Moss, 9=Volcanic, 10=Dunes, 11=Coral
sPrimitiveTerrainPlane::sPrimitiveTerrainPlane(
	const QString &fullName, const std::shared_ptr<cParameterContainer> par)
		: sPrimitiveBasic(fullName, par)
{
	empty = par->Get<bool>(fullName + "_empty");
	terrainType = par->Get<int>(fullName + "_terrain_type");
	amplitude = par->Get<double>(fullName + "_amplitude");
	frequency = par->Get<double>(fullName + "_frequency");
	octaves = par->Get<int>(fullName + "_octaves");
	roughness = par->Get<double>(fullName + "_roughness");
	lacunarity = par->Get<double>(fullName + "_lacunarity");
	erosion = par->Get<double>(fullName + "_erosion");
	detailScale = par->Get<double>(fullName + "_detail_scale");
	wallThickness = par->Get<double>(fullName + "_wall_thickness");
}

sPrimitiveBasic::tWireframeShape sPrimitiveTerrainPlane::wireFrameShape = {};
void sPrimitiveTerrainPlane::InitPrimitiveWireframeShape()
{
	double s = 2.0;
	wireFrameShape.push_back({{-s, -s, 0}, {s, -s, 0}});
	wireFrameShape.push_back({{s, -s, 0}, {s, s, 0}});
	wireFrameShape.push_back({{s, s, 0}, {-s, s, 0}});
	wireFrameShape.push_back({{-s, s, 0}, {-s, -s, 0}});
	wireFrameShape.push_back({{-s, -s, 0}, {s, s, 0}});
	wireFrameShape.push_back({{s, -s, 0}, {-s, s, 0}});
}

static double terrainHash(double x, double y)
{
	double n = sin(x * 127.1 + y * 311.7) * 43758.5453123;
	return n - floor(n);
}

static double terrainNoise(double x, double y)
{
	double ix = floor(x), iy = floor(y);
	double fx = x - ix, fy = y - iy;
	fx = fx * fx * (3.0 - 2.0 * fx);
	fy = fy * fy * (3.0 - 2.0 * fy);
	double a = terrainHash(ix, iy);
	double b = terrainHash(ix + 1, iy);
	double c = terrainHash(ix, iy + 1);
	double d = terrainHash(ix + 1, iy + 1);
	return a + (b - a) * fx + (c - a) * fy + (a - b - c + d) * fx * fy;
}

static double terrainFBM(double x, double y, int octs, double rough, double lac)
{
	double value = 0.0, amp = 1.0, freq = 1.0, maxAmp = 0.0;
	for (int i = 0; i < octs; i++)
	{
		value += amp * (terrainNoise(x * freq, y * freq) * 2.0 - 1.0);
		maxAmp += amp;
		amp *= rough;
		freq *= lac;
	}
	return value / std::max(maxAmp, 1e-10);
}

double sPrimitiveTerrainPlane::PrimitiveDistance(CVector3 _point) const
{
	CVector3 point = TransformPoint(_point);
	point = ApplyDeformations(point);

	double freq = std::max(frequency, 1e-10);
	double px = point.x * freq;
	double py = point.y * freq;
	double displacement = 0.0;

	switch (terrainType)
	{
		case 0: // Sand
		{
			displacement = amplitude * terrainFBM(px, py, octaves, 0.4, lacunarity);
			displacement += sin(px * 8.0 + py * 3.0) * amplitude * 0.15 * detailScale;
			break;
		}
		case 1: // Mud
		{
			double base = terrainFBM(px * 0.5, py * 0.5, octaves, roughness, lacunarity);
			double cracks = fabs(terrainFBM(px * 3.0, py * 3.0, 3, 0.5, 2.0));
			displacement = amplitude * (base * 0.7 - cracks * 0.3 * detailScale);
			break;
		}
		case 2: // Ice
		{
			double flat = terrainFBM(px, py, octaves, 0.3, lacunarity) * 0.1;
			double crack = pow(fabs(terrainFBM(px * 4.0, py * 4.0, 4, 0.5, 2.0)), 3.0);
			displacement = amplitude * (flat - crack * detailScale * 0.5);
			break;
		}
		case 3: // Grass
		{
			double base = terrainFBM(px, py, octaves, roughness, lacunarity);
			double micro = terrainFBM(px * 10.0, py * 10.0, 3, 0.6, 2.0) * detailScale * 0.2;
			displacement = amplitude * (base + micro);
			break;
		}
		case 4: // Rock
		{
			displacement = amplitude * terrainFBM(px, py, octaves, roughness, lacunarity);
			double sharp = terrainFBM(px * 2.0, py * 2.0, 4, 0.7, 2.5);
			displacement += amplitude * fabs(sharp) * detailScale * 0.3;
			break;
		}
		case 5: // Snow
		{
			displacement = amplitude * terrainFBM(px * 0.7, py * 0.7, octaves, 0.35, lacunarity);
			displacement += sin(px * 2.0 + py * 0.5) * amplitude * 0.2;
			break;
		}
		case 6: // Magma
		{
			double turb = 0.0, tFreq2 = 1.0, tAmp = 1.0;
			for (int i = 0; i < octaves; i++)
			{
				turb += tAmp * fabs(terrainNoise(px * tFreq2, py * tFreq2) * 2.0 - 1.0);
				tAmp *= roughness;
				tFreq2 *= lacunarity;
			}
			displacement = amplitude * turb * (1.0 - erosion * 0.5);
			break;
		}
		case 7: // Crystal
		{
			double n = terrainFBM(px, py, octaves, roughness, lacunarity);
			double ds = std::max(detailScale, 1e-10);
			displacement = amplitude * floor(n * 6.0 * ds) / (6.0 * ds);
			break;
		}
		case 8: // Moss
		{
			double base = terrainFBM(px * 0.8, py * 0.8, octaves, 0.5, lacunarity);
			double bumps = pow(0.5 + 0.5 * terrainFBM(px * 5.0, py * 5.0, 3, 0.4, 2.0), 2.0);
			displacement = amplitude * (base * 0.6 + bumps * 0.4 * detailScale);
			break;
		}
		case 9: // Volcanic
		{
			double n = terrainFBM(px, py, octaves, roughness, lacunarity);
			double er = std::max(erosion, 0.01);
			double shaped = (n > 0.0) ? pow(n, 0.5 + er) : -pow(-n, 0.5 + er);
			displacement = amplitude * shaped;
			break;
		}
		case 10: // Dunes
		{
			double mainWave = sin(px * 3.0 + py * 1.5) * 0.5 + 0.5;
			mainWave = pow(mainWave, 1.5);
			double detail = terrainFBM(px * 4.0, py * 4.0, 3, 0.4, 2.0) * detailScale * 0.15;
			displacement = amplitude * (mainWave + detail);
			break;
		}
		case 11: // Coral
		{
			double n1 = terrainFBM(px, py, octaves, roughness, lacunarity);
			double n2 = terrainFBM(px + 5.2, py + 1.3, octaves, roughness, lacunarity);
			double warp = terrainFBM(px + n1 * 2.0, py + n2 * 2.0, 3, 0.5, 2.0);
			displacement = amplitude * warp * detailScale;
			break;
		}
		default:
			displacement = amplitude * terrainFBM(px, py, octaves, roughness, lacunarity);
			break;
	}

	double dist = point.z - displacement;
	dist = empty ? fabs(dist) : dist;
	return dist;
}
