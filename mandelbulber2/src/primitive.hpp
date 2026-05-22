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

#ifndef MANDELBULBER2_SRC_PRIMITIVE_HPP_
#define MANDELBULBER2_SRC_PRIMITIVE_HPP_

#include <memory>
#include <vector>

#include "algebra.hpp"
#include "object_data.hpp"
#include "object_types.hpp"
#include "parameters.hpp"

enum enumPrimitiveBooleanOperator
{
	primBooleanOperatorAND = 0,
	primBooleanOperatorOR = 1,
	primBooleanOperatorSUB = 2,
	primBooleanOperatorRevSUB = 3,
	primBooleanOperatorSmoothOR = 4,
	primBooleanOperatorSmoothAND = 5,
	primBooleanOperatorSmoothSUB = 6
};

struct sPrimitiveBasic : cObjectData
{
	sPrimitiveBasic(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool enable = false;
	int objectId = 0;
	int userObjectId = 0;
	enumPrimitiveBooleanOperator booleanOperator = primBooleanOperatorOR;
	CVector3 primitiveScale = CVector3(1.0, 1.0, 1.0);
	int coordinateSpace = 0;
	CVector3 pivot = CVector3(0.0, 0.0, 0.0);
	bool useWorldSpacePivot = false;

	// 3-point alignment
	CVector3 alignP1 = CVector3(0.0, 0.0, 0.0);
	CVector3 alignP2 = CVector3(1.0, 0.0, 0.0);
	CVector3 alignP3 = CVector3(0.0, 1.0, 0.0);

	// Cloner settings
	struct ClonerSettings
	{
		bool enabled = false;
		enum Mode
		{
			LINEAR = 0,
			RADIAL = 1,
			GRID = 2
		} mode = LINEAR;
		int count = 1;
		CVector3 offset = CVector3(1.0, 0.0, 0.0);
		double radius = 5.0;
		double startAngle = 0.0;
		double endAngle = 2.0 * M_PI;
		int plane = 0; // 0=XY, 1=XZ, 2=YZ
		CVector3 gridCount = CVector3(3, 3, 3);
		CVector3 gridSize = CVector3(10.0, 10.0, 10.0);
	} cloner;

	double smoothRadius = 0.1;
	bool mirrorX = false;
	bool mirrorY = false;
	bool mirrorZ = false;
	bool shellEnable = false;
	double shellThickness = 0.1;

	// Group support
	int groupId = 0;                          // 0 = no group, >0 = member of group N
	QString groupName;                        // custom name for this group
	bool groupEnabled = true;                 // enable/disable entire group
	bool groupVisible = true;                 // show/hide entire group
	bool groupLocked = false;                 // prevent editing of group members
	int groupBooleanOperator = primBooleanOperatorOR;  // how the GROUP combines with scene
	double groupSmoothRadius = 0.1;           // smooth blend radius for group boolean operation
	bool isGroupFirst = false;                // true if first primitive in its group
	int groupPriority = 0;                    // rendering order (higher = later)

	// Group transformations (applied to entire group)
	CVector3 groupPosition = CVector3(0.0, 0.0, 0.0);
	CVector3 groupRotation = CVector3(0.0, 0.0, 0.0);
	CVector3 groupScale = CVector3(1.0, 1.0, 1.0);

	// Per-Primitive Material Override
	bool materialOverrideEnable = false;          // enable custom material for this primitive
	sRGB materialColor = sRGB(128, 128, 128);     // custom color override
	double materialReflectance = 0.0;             // reflectivity (0.0-1.0)
	double materialTransparency = 0.0;            // transparency (0.0-1.0)
	double materialSpecular = 1.0;                // specular intensity
	double materialRoughness = 0.1;               // surface roughness
	double materialMetallic = 0.0;                // metallic property (0.0-1.0)
	double materialLuminosity = 0.0;              // emission/glow (0.0-10.0)

	// Deformation Modifiers
	bool deformBendEnable = false;                // enable bend modifier
	double deformBendAngle = 0.0;                 // bend angle in radians per unit
	int deformBendAxis = 1;                       // 0=X, 1=Y, 2=Z
	double deformBendStrength = 1.0;              // strength multiplier
	int deformBendMode = 0;                       // 0=Limited, 1=Unlimited, 2=Within Box
	bool deformBendKeepY = false;                 // preserve Y-axis length

	bool deformTwistEnable = false;               // enable twist modifier
	double deformTwistAngle = 0.0;                // twist amount (radians per unit length)
	int deformTwistAxis = 1;                      // 0=X, 1=Y, 2=Z
	double deformTwistStrength = 1.0;             // strength multiplier
	int deformTwistMode = 0;                      // 0=Limited, 1=Unlimited, 2=Within Box

	bool deformTaperEnable = false;               // enable taper modifier
	double deformTaperRate = 0.0;                 // taper rate (scale change per unit)
	int deformTaperAxis = 1;                      // 0=X, 1=Y, 2=Z
	double deformTaperStrength = 1.0;             // strength multiplier
	double deformTaperCurvature = 0.0;            // curvature applied to taper
	int deformTaperMode = 0;                      // 0=Limited, 1=Unlimited, 2=Within Box

	// Instance System
	bool isInstance = false;                      // true if this is an instance (not master)
	int instanceMasterId = -1;                    // ID of master primitive (-1 = none)
	bool instanceInheritTransform = true;         // inherit position/rotation/scale from master

	// Boolean target
	int booleanTargetGroupId = -1;                // -1 = global accumulator, >=0 = target specific group

	// Boolean Edge Modification
	double booleanEdgeChamfer = 0.0;              // chamfer/bevel radius on boolean edges
	int booleanEdgeChamferQuality = 4;            // quality/smoothness of chamfer (2-16)

	// Extended repeat settings
	CVector3 repeatOffset = CVector3(0.0, 0.0, 0.0);       // phase/offset for linear repeat
	int repeatFinite = 0;                                  // 0=infinite (current), 1=finite (clamp outside range)
	CVector3 repeatFiniteRange = CVector3(10.0, 10.0, 10.0); // range within which copies appear (for finite)
	double repeatRadialCount = 0.0;                        // angles for rotational space folding
	int repeatRadialPlane = 0;                             // 0=XY, 1=XZ, 2=YZ
	double scale = 1.0;
	int repeatMode = 0;
	double repeatRotationStep = 30.0;
	int repeatFibonacciCount = 21;
	double repeatFibonacciSpread = 1.0;
	// Spiral repeat
	CVector3 repeatSpiralStep = CVector3(1.0, 1.0, 1.0);
	CVector3 repeatSpiralAngle = CVector3(0.0, 0.0, 0.0);
	CVector3 repeatSpiralRadius = CVector3(1.0, 1.0, 1.0);
	// Wave repeat
	CVector3 repeatWaveAmplitude = CVector3(0.5, 0.5, 0.5);
	CVector3 repeatWaveFrequency = CVector3(1.0, 1.0, 1.0);
	CVector3 repeatWavePhase = CVector3(0.0, 0.0, 0.0);
	int repeatWaveAxis = 0;

	virtual ~sPrimitiveBasic() = default;
	virtual double PrimitiveDistance(CVector3 _point) const = 0;

	// Transform point using pivot + rotation + position
	CVector3 TransformPoint(const CVector3 &_point) const;

	// Apply bend, twist, taper deformations to point
	CVector3 ApplyDeformations(const CVector3 &point) const;

	// Calculate clone offset for given index
	CVector3 CalculateCloneOffset(int index) const;

	// Effectors (MoGraph style)
	struct Effector
	{
		bool enabled = false;
		enum Mode { POSITION = 0, ROTATION = 1, SCALE = 2, ALL = 3 } mode = ALL;
		double strength = 1.0;
		virtual ~Effector() = default;
		virtual void Apply(int index, CVector3 &position, CVector3 &rotation, CVector3 &scale) const = 0;
	};

	struct RandomEffector : Effector
	{
		int seed = 0;
		CVector3 positionAmp = CVector3(1.0, 1.0, 1.0);
		CVector3 rotationAmp = CVector3(30.0, 30.0, 30.0);
		CVector3 scaleAmp = CVector3(0.2, 0.2, 0.2);
		void Apply(int index, CVector3 &position, CVector3 &rotation, CVector3 &scale) const override;
	};

	struct StepEffector : Effector
	{
		CVector3 positionStep = CVector3(1.0, 0.0, 0.0);
		CVector3 rotationStep = CVector3(0.0, 0.0, 0.0);
		CVector3 scaleStep = CVector3(0.0, 0.0, 0.0);
		void Apply(int index, CVector3 &position, CVector3 &rotation, CVector3 &scale) const override;
	};

	struct FormulaEffector : Effector
	{
		int formulaPreset = 0; // 0=sin(index), 1=cos(index*2), 2=wave, 3=spiral
		void Apply(int index, CVector3 &position, CVector3 &rotation, CVector3 &scale) const override;
	};

	struct TimeEffector : Effector
	{
		double timeOffset = 0.0;
		double timeScale = 1.0;
		void Apply(int index, CVector3 &position, CVector3 &rotation, CVector3 &scale) const override;
	};

	static constexpr int maxEffectors = 4;
	std::shared_ptr<Effector> effectors[maxEffectors];

	// Apply clone transform: base offset + effectors
	CVector3 ApplyCloneTransform(int index, CVector3 &rotation, CVector3 &scale) const;

	struct sPrimitiveWireLine
	{
		CVector3 p1;
		CVector3 p2;
	};

	typedef std::vector<sPrimitiveWireLine> tWireframeShape;

	static tWireframeShape wireFrameShape;
	static const int wireframeSegments = 24;
	virtual const tWireframeShape &GetWireFrameShape() { return wireFrameShape; }
	static void InitPrimitiveWireframeShapes();
};

struct sPrimitivePlane : sPrimitiveBasic
{
	sPrimitivePlane(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveBox : sPrimitiveBasic
{
	sPrimitiveBox(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	bool limitsEnable;
	double rounding;
	CVector3 repeat;
	CVector3 limitsMax;
	CVector3 limitsMin;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveSphere : sPrimitiveBasic
{
	sPrimitiveSphere(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	bool limitsEnable;
	double radius;
	CVector3 repeat;
	CVector3 limitsMax;
	CVector3 limitsMin;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveCone : sPrimitiveBasic
{
	sPrimitiveCone(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	bool caps;
	bool limitsEnable;
	double radius;
	double height;
	CVector2<double> wallNormal;
	CVector3 repeat;
	CVector3 limitsMax;
	CVector3 limitsMin;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveCylinder : sPrimitiveBasic
{
	sPrimitiveCylinder(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	bool caps;
	bool limitsEnable;
	double radius;
	double height;
	CVector3 repeat;
	CVector3 limitsMax;
	CVector3 limitsMin;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveTorus : sPrimitiveBasic
{
	sPrimitiveTorus(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	bool limitsEnable;
	double radius;
	double radiusLPow;
	double tubeRadius;
	double tubeRadiusLPow;
	CVector3 repeat;
	CVector3 limitsMax;
	CVector3 limitsMin;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveCircle : sPrimitiveBasic
{
	sPrimitiveCircle(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	double radius;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveRectangle : sPrimitiveBasic
{
	sPrimitiveRectangle(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	double height;
	double width;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitivePrism : sPrimitiveBasic
{
	sPrimitivePrism(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	double triangleHeight;
	double height;
	double prismAngle;
	CVector3 normals;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveEllipsoid : sPrimitiveBasic
{
	sPrimitiveEllipsoid(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	bool limitsEnable;
	CVector3 repeat;
	CVector3 limitsMax;
	CVector3 limitsMin;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveWater : sPrimitiveBasic
{
	sPrimitiveWater(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	bool waveFromObjectsEnable;
	bool limitsEnable;
	double relativeAmplitude;
	double animSpeed;
	double animProgressionSpeed;
	double length;
	double waveFromObjectsRelativeAmplitude;
	int iterations;
	int animFrame;
	double PrimitiveDistance(CVector3 _point) const override;
	double PrimitiveDistanceWater(CVector3 _point, double distanceFromAnother) const;
	CVector3 limitsMax;
	CVector3 limitsMin;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveCapsule : sPrimitiveBasic
{
	sPrimitiveCapsule(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	double radius;
	double height;
	bool limitsEnable;
	CVector3 repeat;
	CVector3 limitsMax;
	CVector3 limitsMin;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveHexPrism : sPrimitiveBasic
{
	sPrimitiveHexPrism(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	double height;
	bool limitsEnable;
	CVector3 repeat;
	CVector3 limitsMax;
	CVector3 limitsMin;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveLavaPlane : sPrimitiveBasic
{
	sPrimitiveLavaPlane(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	double waveHeight;
	double waveScale;
	int waveOctaves;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveOctahedron : sPrimitiveBasic
{
	sPrimitiveOctahedron(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	bool limitsEnable;
	CVector3 repeat;
	CVector3 limitsMax;
	CVector3 limitsMin;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitivePyramid : sPrimitiveBasic
{
	sPrimitivePyramid(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	double height;
	double baseSize;
	bool limitsEnable;
	CVector3 repeat;
	CVector3 limitsMax;
	CVector3 limitsMin;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

struct sPrimitiveTerrainPlane : sPrimitiveBasic
{
	sPrimitiveTerrainPlane(const QString &fullName, const std::shared_ptr<cParameterContainer> par);
	bool empty;
	int terrainType;
	double amplitude;
	double frequency;
	int octaves;
	double roughness;
	double lacunarity;
	double erosion;
	double detailScale;
	double PrimitiveDistance(CVector3 _point) const override;

	static tWireframeShape wireFrameShape;
	static void InitPrimitiveWireframeShape();
	virtual const tWireframeShape &GetWireFrameShape() override { return wireFrameShape; }
};

#endif /* MANDELBULBER2_SRC_PRIMITIVE_HPP_ */
