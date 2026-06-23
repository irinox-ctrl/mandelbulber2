/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2014-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * sFractal struct - container for fractal formula parameters
 */

#ifndef MANDELBULBER2_SRC_FRACTAL_H_
#define MANDELBULBER2_SRC_FRACTAL_H_

#include <memory>

#include "algebra.hpp"

#include "formula/definition/all_fractal_list_enums.hpp"

#ifndef M_PI_180
#define M_PI_180 0.01745329251994329576923690768489
#endif

// forward declarations
class cParameterContainer;

const int IFS_VECTOR_COUNT = 9;
const int HYBRID_COUNT = 5;
const int MANDELBOX_FOLDS = 2;

namespace fractal
{
enum enumOCLDEMode
{
	ocl_DECalculated = 0,
	ocl_deltaDE = 1,
	ocl_noDE = 2
};
}

enum enumGeneralizedFoldBoxType
{
	generalizedFoldBoxType_foldTet = 0,
	generalizedFoldBoxType_foldCube = 1,
	generalizedFoldBoxType_foldOct = 2,
	generalizedFoldBoxType_foldDodeca = 3,
	generalizedFoldBoxType_foldOctCube = 4,
	generalizedFoldBoxType_foldIcosa = 5,
	generalizedFoldBoxType_foldBox6 = 6,
	generalizedFoldBoxType_foldBox5 = 7
};
struct sExtendedAux
{
	int i;

	CVector4 c;
	CVector4 const_c;
	CVector4 old_z;
	// CVector4 sum_z;
	double pos_neg;

	double r;
	double DE;
	double DE0;
	double dist;
	double pseudoKleinianDE;

	double actualScale;
	double actualScaleA;

	double color;
	double colorHybrid;

	double temp1000;
};

struct sFoldColor
{
	CVector3 factor;
	CVector4 factor4D;
	CVector4 difs0000;
	double factorR;
	double factorSp1;
	double factorSp2;
	double difs0;
	double difs1;
	bool auxColorEnabled;
	bool auxColorEnabledA;
	bool auxColorEnabledFalse;
	bool auxColorEnabledAFalse;
	bool auxColorEnabledBFalse;
	int startIterationsA;
	int stopIterationsA;
	int startIterationsB;
	int stopIterationsB;
	int int0;
	int int2;
};

struct sFractalGeneralizedFoldBox
{
	enumGeneralizedFoldBoxType type;
	CVector3 Nv_tet[4];
	CVector3 Nv_cube[6];
	CVector3 Nv_oct[8];
	CVector3 Nv_oct_cube[14];
	CVector3 Nv_dodeca[12];
	CVector3 Nv_icosa[20];
	CVector3 Nv_box6[8];
	CVector3 Nv_box5[7];
	int sides_tet;
	int sides_cube;
	int sides_oct;
	int sides_oct_cube;
	int sides_dodeca;
	int sides_icosa;
	int sides_box6;
	int sides_box5;
};

struct sFractalIFS
{
	bool absX;
	bool absY;
	bool absZ;
	bool enabled[IFS_VECTOR_COUNT];
	bool mengerSpongeMode;
	bool rotationEnabled;
	bool edgeEnabled;
	CRotationMatrix mainRot;
	CRotationMatrix rot[IFS_VECTOR_COUNT];
	CVector4 direction[IFS_VECTOR_COUNT];
	CVector3 edge;
	CVector4 offset;
	CVector3 rotations[IFS_VECTOR_COUNT];
	double distance[IFS_VECTOR_COUNT];
	double intensity[IFS_VECTOR_COUNT];
	CVector3 rotation;
	double scale;
};

struct sFractalMandelboxVary4D
{
	double fold;
	double minR;
	double scaleVary;
	double wadd;
	double rPower;
};

struct sFractalMandelbox
{
	CVector3 rotationMain;
	CVector3 rotation[MANDELBOX_FOLDS][3];
	sFoldColor color;
	double scale;
	double foldingLimit;
	double foldingValue;
	double foldingSphericalMin;
	double foldingSphericalFixed;
	double sharpness;
	double solid;
	double melt;
	CVector4 offset;
	bool rotationsEnabled;
	bool mainRotationEnabled;
	CRotationMatrix mainRot;
	CRotationMatrix rot[MANDELBOX_FOLDS][3];
	CRotationMatrix rotinv[MANDELBOX_FOLDS][3];

	double fR2;
	double mR2;
	double mboxFactor1;
};

struct sFractalBoxFoldBulbPow2
{
	double zFactor;
	double foldFactor;
};

struct sFractalMandelbulb
{
	double power;
	double alphaAngleOffset;
	double betaAngleOffset;
	double gammaAngleOffset;
};

struct sFractalAexion
{
	double cadd;
};

struct sFractalBuffalo
{
	bool preabsx;
	bool preabsy;
	bool preabsz;
	bool absx;
	bool absy;
	bool absz;
	bool posz;
};

// Mandalay Box V2 extended features
struct sFractalMandalay
{
	// #1 Cylinder Fold
	bool cylinderFoldEnabled;
	double cylMinR;
	double cylMix;
	int startIterationsCy;
	int stopIterationsCy;

	// #2 Multi-Sequencing Clips
	bool multiClipEnabled;
	int numClips;
	CVector4 fo2;
	CVector4 fo3;
	CVector4 fo4;
	CVector4 g2;
	CVector4 g3;
	CVector4 g4;

	// #3 Pre-Sphere Inversion (Kleinian-style)
	bool preSphereInvertEnabled;
	CVector4 invertCenter; // xyz = center, w = radius
	int startIterationsPI;
	int stopIterationsPI;

	// #4 Anisotrope Scale (per-axis)
	bool anisotropeScaleEnabled;
	CVector4 scale3D;
	int startIterationsAS;
	int stopIterationsAS;

	// #5 Z-Shear (parabolische diepte-vervorming)
	bool zShearEnabled;
	double zShearStrength;
	int startIterationsZS;
	int stopIterationsZS;

	// #6 Variable Clip Limits (adaptieve fo/g)
	bool variableClipEnabled;
	double foVary;
	double gVary;
	int startIterationsVC;
	int stopIterationsVC;

	// #7 Quaternion Pre-Rotation
	bool quatRotEnabled;
	CVector4 quatRot; // xyz = imaginary, w = real
	int startIterationsQR;
	int stopIterationsQR;

	// #8 Ellipsoïde Fold (non-spherical fold boundary)
	bool ellipsoidFoldEnabled;
	CVector4 ellipsoidAxes; // xyz = semi-axes a,b,c
	double ellipsoidMinR;

	// #9 Torus Fold
	bool torusFoldEnabled;
	double torusMajorR; // R: distance center to tube center
	double torusMinorR; // r: tube radius
	double torusFoldStrength;
	int startIterationsTF;
	int stopIterationsTF;

	// #10 Logarithmic Spherical Fold
	bool logSphericalFoldEnabled;
	double logSphericalMinR;

	// #11 Hyperbolische Box Fold
	bool hyperBoxFoldEnabled;
	double hyperBoxFoldK; // sinh/cosh steepness
	int startIterationsHB;
	int stopIterationsHB;
};

struct sFractalDonut
{
	double ringRadius;
	double ringThickness;
	double factor;
	double number;
};

//----------------------------------------------------------
struct sFractalPlatonicSolid
{
	double frequency;
	double amplitude;
	double rhoMul;
};

// mandelbulb multi
enum enumMulti_acosOrAsin
{
	multi_acosOrAsin_acos,
	multi_acosOrAsin_asin
};

enum enumMulti_atanOrAtan2
{
	multi_atanOrAtan2_atan,
	multi_atanOrAtan2_atan2
};

enum enumMulti_OrderOfXYZ
{
	multi_OrderOfXYZ_xyz,
	multi_OrderOfXYZ_xzy,
	multi_OrderOfXYZ_yxz,
	multi_OrderOfXYZ_yzx,
	multi_OrderOfXYZ_zxy,
	multi_OrderOfXYZ_zyx
};
struct sFractalMandelbulbMulti
{
	enumMulti_acosOrAsin acosOrAsin;
	enumMulti_acosOrAsin acosOrAsinA;
	enumMulti_atanOrAtan2 atanOrAtan2;
	enumMulti_atanOrAtan2 atanOrAtan2A;

	enumMulti_OrderOfXYZ orderOfXYZ;
	enumMulti_OrderOfXYZ orderOfXYZ2;
	enumMulti_OrderOfXYZ orderOfXYZC;
};

// sinTan2Trig
enum enumMulti_asinOrAcos
{
	multi_asinOrAcos_asin,
	multi_asinOrAcos_acos
};

enum enumMulti_atan2OrAtan
{
	multi_atan2OrAtan_atan2,
	multi_atan2OrAtan_atan
};

enum enumMulti_OrderOfZYX
{
	multi_OrderOfZYX_zyx,
	multi_OrderOfZYX_zxy,
	multi_OrderOfZYX_yzx,
	multi_OrderOfZYX_yxz,
	multi_OrderOfZYX_xzy,
	multi_OrderOfZYX_xyz
};
struct sFractalSinTan2Trig
{
	enumMulti_asinOrAcos asinOrAcos;
	enumMulti_atan2OrAtan atan2OrAtan;
	enumMulti_OrderOfZYX orderOfZYX;
};

// surf fold box
enum enumMulti_orderOfFolds
{
	multi_orderOfFolds_type1,
	multi_orderOfFolds_type2,
	multi_orderOfFolds_type3,
	multi_orderOfFolds_type4,
	multi_orderOfFolds_type5
};
struct sFractalSurfFolds
{
	enumMulti_orderOfFolds orderOfFolds1;
	enumMulti_orderOfFolds orderOfFolds2;
	enumMulti_orderOfFolds orderOfFolds3;
	enumMulti_orderOfFolds orderOfFolds4;
	enumMulti_orderOfFolds orderOfFolds5;
};

// asurf mod2
enum enumMulti_orderOf3Folds
{
	multi_orderOf3Folds_type1,
	multi_orderOf3Folds_type2,
	multi_orderOf3Folds_type3
};
struct sFractalASurf3Folds
{
	enumMulti_orderOf3Folds orderOf3Folds1;
	enumMulti_orderOf3Folds orderOf3Folds2;
	enumMulti_orderOf3Folds orderOf3Folds3;
};

// benesi mag transforms
enum enumMulti_orderOfTransf
{
	multi_orderOfTransf_typeT1,
	multi_orderOfTransf_typeT1Mod,
	multi_orderOfTransf_typeT2,
	multi_orderOfTransf_typeT3,
	multi_orderOfTransf_typeT4,
	multi_orderOfTransf_typeT5b,
};
struct sFractalMagTransforms
{
	enumMulti_orderOfTransf orderOfTransf1;
	enumMulti_orderOfTransf orderOfTransf2;
	enumMulti_orderOfTransf orderOfTransf3;
	enumMulti_orderOfTransf orderOfTransf4;
	enumMulti_orderOfTransf orderOfTransf5;
};

// combo3
enum enumMulti_combo3
{
	multi_combo3_type1,
	multi_combo3_type2,
	multi_combo3_type3,
};
struct sFractalCombo3
{
	enumMulti_combo3 combo3;
};

// combo4
enum enumMulti_combo4
{
	multi_combo4_type1,
	multi_combo4_type2,
	multi_combo4_type3,
	multi_combo4_type4,
};
struct sFractalCombo4
{
	enumMulti_combo4 combo4;
};

// combo5
enum enumMulti_combo5
{
	multi_combo5_type1,
	multi_combo5_type2,
	multi_combo5_type3,
	multi_combo5_type4,
	multi_combo5_type5,
};
struct sFractalCombo5
{
	enumMulti_combo5 combo5;
};

// combo6
enum enumMulti_combo6
{
	multi_combo6_type1,
	multi_combo6_type2,
	multi_combo6_type3,
	multi_combo6_type4,
	multi_combo6_type5,
	multi_combo6_type6,
};
struct sFractalCombo6
{
	enumMulti_combo6 combo6;
};

// basic combo
enum enumCombo
{
	combo_mode0,
	combo_mode1,
	combo_mode2,
	combo_mode3,
	combo_mode4,
	combo_mode5,
	combo_mode6,
	combo_mode7,
};
struct sFractalCombo
{
	enumCombo modeA;
	//		combo modeB;
	//		combo modeC;
};

// for surfbox types
struct sFractalSurfBox
{
	bool enabledX1;
	bool enabledY1;
	bool enabledZ1;
	bool enabledX2False;
	bool enabledY2False;
	bool enabledZ2False;
	bool enabledX3False;
	bool enabledY3False;
	bool enabledZ3False;
	bool enabledX4False;
	bool enabledY4False;
	bool enabledZ4False;
	bool enabledX5False;
	bool enabledY5False;
	bool enabledZ5False;
	CVector4 offset1A111;
	CVector4 offset1B111;
	CVector4 offset2A111;
	CVector4 offset2B111;
	CVector4 offset3A111;
	CVector4 offset3B111;
	CVector4 offset1A222;
	CVector4 offset1B222;
	double scale1Z1;
};

// for curvilinear
struct sFractalCpara
{
	bool enabledLinear;
	bool enabledCurves;
	bool enabledParabFalse;
	bool enabledParaAddP0;
	double para00;
	double paraA0;
	double paraB0;
	double paraC0;
	double parabOffset0;
	double para0;
	double paraA;
	double paraB;
	double paraC;
	double parabOffset;
	double parabSlope;
	double parabScale;
	int iterA;
	int iterB;
	int iterC;
};

struct sFractalAnalyticDE
{
	bool enabled;
	bool enabledFalse;
	double scale1;
	double tweak005;
	double offset0;
	double offset1;
	double offset2;
	int startIterationsA;
	int stopIterationsA;
};

// common parameters for transforming formulas
struct sFractalTransformCommon
{
	double angle0;

	double angleDegA;
	double angleDegB;
	double angleDegC;
	double cosA;
	double cosB;
	double cosC;
	double sinA;
	double sinB;
	double sinC;
	double angle45;
	double angle72;
	double alphaAngleOffset;
	double betaAngleOffset;
	double foldingValue;
	double foldingLimit;
	double invert0;
	double invert1;
	double offset;
	double offset0;
	double offsetA0;
	double offsetB0;
	double offsetC0;
	double offsetD0;
	double offsetE0;
	double offsetF0;
	double offsetR0;
	double offset0005;
	double offsetp01;
	double offsetAp01;
	double offsetBp01;
	double offsetp05;
	double offset01;
	double offsetp1;
	double offset02;
	double offset05;
	double offsetA05;
	double offsetB05;
	double offset1;
	double offsetA1;
	double offsetR1;
	double offsetT1;
	double offset105;
	double offset2;
	double offsetA2;
	double offsetE2;
	double offsetF2;
	double offsetR2;
	double offset3;
	double offset4;
	double multiplication;
	double minR0;
	double minR05;
	double minR06;
	double minR2p25;
	double maxR2d1;
	double maxMinR0factor;
	double maxMinR2factor;
	double radius1;
	double scaleNeg1;
	double scale;
	double scale0;
	double scaleA0;
	double scaleB0;
	double scaleC0;
	double scale025;
	double scale05;
	double scale08;
	double scale1;
	double scaleA1;
	double scaleB1;
	double scaleC1;
	double scaleD1;
	double scaleE1;
	double scaleF1;
	double scaleG1;
	double scale1p1;
	double scale015;
	double scale2;
	double scaleA2;
	double scale3;
	double scaleA3;
	double scaleB3;
	double scale4;
	double scale5;
	double scale6;
	double scale8;
	double scale16;
	double scale25;
	double scaleMain2;
	double scaleVary0;

	double pwr05;
	double pwr4;
	double pwr8;
	double pwr8a;
	double sqtR;
	double mboxFactor1;
	double inv0;
	double inv1;

	int startIterations;
	int startIterations250;
	int stopIterations;
	int stopIterations15;
	int stopIterations50;
	int startIterationsA;
	int stopIterationsA;
	int startIterationsB;
	int stopIterationsB;
	int startIterationsC;
	int stopIterationsC;
	int stopIterationsC1;
	int startIterationsCx;
	int stopIterationsCx;
	int startIterationsCy;
	int stopIterationsCy;
	int startIterationsCz;
	int stopIterationsCz;
	int startIterationsD;
	int stopIterationsD;
	int stopIterationsD1;
	int startIterationsE;
	int stopIterationsE;
	int startIterationsF;
	int stopIterationsF;
	int startIterationsG;
	int stopIterationsG;
	int startIterationsH;
	int stopIterationsH;
	int startIterationsI;
	int stopIterationsI;
	int startIterationsJ;
	int stopIterationsJ;
	int startIterationsK;
	int stopIterationsK;
	int startIterationsM;
	int stopIterationsM;
	int startIterationsN;
	int stopIterationsN;
	int startIterationsO;
	int stopIterationsO;
	int startIterationsP;
	int stopIterationsP;
	int stopIterationsP1;
	int startIterationsR;
	int stopIterationsR;
	int stopIterationsR1;
	int startIterationsRV;
	int stopIterationsRV;
	int startIterationsS;
	int stopIterationsS;
	int startIterationsT;
	int stopIterationsT;
	int stopIterationsT1;
	int startIterationsTM;
	int stopIterationsTM1;
	int startIterationsX;
	int stopIterationsX;
	int startIterationsY;
	int stopIterationsY;
	int startIterationsZ;
	int stopIterationsZ;
	int startIterationsZc;
	int stopIterationsZc;
	int stopIterations1;

	int intA;
	int intB;
	int int1;
	int intA1;
	int intB1;
	int int2;
	int int3;
	int int3X;
	int int3Y;
	int int3Z;
	int int6;
	int int8X;
	int int8Y;
	int int8Z;
	int int16;
	int int32;

	int multiplierMode1;
	int multiplierMode2;
	int multiplierMode3;
	int multiplierMode4;
	int multiplierMode5;

	int multiplierValueMode1;
	int multiplierValueMode2;
	int multiplierValueMode3;
	int multiplierValueMode4;
	int multiplierValueMode5;

	bool multiplierInverse1;
	bool multiplierInverse2;
	bool multiplierInverse3;
	bool multiplierInverse4;
	bool multiplierInverse5;

	double multiplierFrequency1;
	double multiplierFrequency2;
	double multiplierFrequency3;
	double multiplierFrequency4;
	double multiplierFrequency5;

	double multiplierPhase1;
	double multiplierPhase2;
	double multiplierPhase3;
	double multiplierPhase4;
	double multiplierPhase5;

	double multiplierThreshold1;
	double multiplierThreshold2;
	double multiplierThreshold3;
	double multiplierThreshold4;
	double multiplierThreshold5;

	int multiplierThresholdMode1;
	int multiplierThresholdMode2;
	int multiplierThresholdMode3;
	int multiplierThresholdMode4;
	int multiplierThresholdMode5;

	double multiplierScaleY1;
	double multiplierScaleY2;
	double multiplierScaleY3;
	double multiplierScaleY4;
	double multiplierScaleY5;

	double multiplierScaleZ1;
	double multiplierScaleZ2;
	double multiplierScaleZ3;
	double multiplierScaleZ4;
	double multiplierScaleZ5;

	bool multiplierChain1;
	bool multiplierChain2;
	bool multiplierChain3;
	bool multiplierChain4;
	bool multiplierChain5;

	double multiplierWeight1;
	double multiplierWeight2;
	double multiplierWeight3;
	double multiplierWeight4;
	double multiplierWeight5;

	double multiplierDecay1;
	double multiplierDecay2;
	double multiplierDecay3;
	double multiplierDecay4;
	double multiplierDecay5;

	double multiplierExponent1;
	double multiplierExponent2;
	double multiplierExponent3;
	double multiplierExponent4;
	double multiplierExponent5;

	double multiplierOffset1;
	double multiplierOffset2;
	double multiplierOffset3;
	double multiplierOffset4;
	double multiplierOffset5;

	double multiplierPulseWidth1;
	double multiplierPulseWidth2;
	double multiplierPulseWidth3;
	double multiplierPulseWidth4;
	double multiplierPulseWidth5;

	double multiplierHarmonics1;
	double multiplierHarmonics2;
	double multiplierHarmonics3;
	double multiplierHarmonics4;
	double multiplierHarmonics5;

	double multiplierAttack1;
	double multiplierAttack2;
	double multiplierAttack3;
	double multiplierAttack4;
	double multiplierAttack5;

	double multiplierRelease1;
	double multiplierRelease2;
	double multiplierRelease3;
	double multiplierRelease4;
	double multiplierRelease5;

	double multiplierFeedback1;
	double multiplierFeedback2;
	double multiplierFeedback3;
	double multiplierFeedback4;
	double multiplierFeedback5;

	double multiplierRadialFalloff1;
	double multiplierRadialFalloff2;
	double multiplierRadialFalloff3;
	double multiplierRadialFalloff4;
	double multiplierRadialFalloff5;

	double multiplierAngularBias1;
	double multiplierAngularBias2;
	double multiplierAngularBias3;
	double multiplierAngularBias4;
	double multiplierAngularBias5;

	double multiplierCrossCoupling1;
	double multiplierCrossCoupling2;
	double multiplierCrossCoupling3;
	double multiplierCrossCoupling4;
	double multiplierCrossCoupling5;

	double multiplierClampMin1;
	double multiplierClampMin2;
	double multiplierClampMin3;
	double multiplierClampMin4;
	double multiplierClampMin5;

	double multiplierClampMax1;
	double multiplierClampMax2;
	double multiplierClampMax3;
	double multiplierClampMax4;
	double multiplierClampMax5;

	double multiplierSoftClip1;
	double multiplierSoftClip2;
	double multiplierSoftClip3;
	double multiplierSoftClip4;
	double multiplierSoftClip5;

	double multiplierSymmetryBreak1;
	double multiplierSymmetryBreak2;
	double multiplierSymmetryBreak3;
	double multiplierSymmetryBreak4;
	double multiplierSymmetryBreak5;

	int multiplierQuantize1;
	int multiplierQuantize2;
	int multiplierQuantize3;
	int multiplierQuantize4;
	int multiplierQuantize5;

	int multiplierIterModulo1;
	int multiplierIterModulo2;
	int multiplierIterModulo3;
	int multiplierIterModulo4;
	int multiplierIterModulo5;

	int multiplierDelay1;
	int multiplierDelay2;
	int multiplierDelay3;
	int multiplierDelay4;
	int multiplierDelay5;

	int multiplierBlendMode1;
	int multiplierBlendMode2;
	int multiplierBlendMode3;
	int multiplierBlendMode4;
	int multiplierBlendMode5;

	int multiplierNoiseSeed1;
	int multiplierNoiseSeed2;
	int multiplierNoiseSeed3;
	int multiplierNoiseSeed4;
	int multiplierNoiseSeed5;

	int multiplierNoiseOctaves1;
	int multiplierNoiseOctaves2;
	int multiplierNoiseOctaves3;
	int multiplierNoiseOctaves4;
	int multiplierNoiseOctaves5;

	bool multiplierMirror1;
	bool multiplierMirror2;
	bool multiplierMirror3;
	bool multiplierMirror4;
	bool multiplierMirror5;

	bool multiplierPolarMode1;
	bool multiplierPolarMode2;
	bool multiplierPolarMode3;
	bool multiplierPolarMode4;
	bool multiplierPolarMode5;

	double multiplierClipCurve1;
	double multiplierClipCurve2;
	double multiplierClipCurve3;
	double multiplierClipCurve4;
	double multiplierClipCurve5;

	double multiplierClipKnee1;
	double multiplierClipKnee2;
	double multiplierClipKnee3;
	double multiplierClipKnee4;
	double multiplierClipKnee5;

	double multiplierClipDrive1;
	double multiplierClipDrive2;
	double multiplierClipDrive3;
	double multiplierClipDrive4;
	double multiplierClipDrive5;

	double multiplierClipAsymmetry1;
	double multiplierClipAsymmetry2;
	double multiplierClipAsymmetry3;
	double multiplierClipAsymmetry4;
	double multiplierClipAsymmetry5;

	double multiplierClipCeiling1;
	double multiplierClipCeiling2;
	double multiplierClipCeiling3;
	double multiplierClipCeiling4;
	double multiplierClipCeiling5;

	double multiplierClipFloor1;
	double multiplierClipFloor2;
	double multiplierClipFloor3;
	double multiplierClipFloor4;
	double multiplierClipFloor5;

	double multiplierClipMix1;
	double multiplierClipMix2;
	double multiplierClipMix3;
	double multiplierClipMix4;
	double multiplierClipMix5;

	int multiplierClipFoldCount1;
	int multiplierClipFoldCount2;
	int multiplierClipFoldCount3;
	int multiplierClipFoldCount4;
	int multiplierClipFoldCount5;

	int multiplierClipRectify1;
	int multiplierClipRectify2;
	int multiplierClipRectify3;
	int multiplierClipRectify4;
	int multiplierClipRectify5;

	bool multiplierClipFold1;
	bool multiplierClipFold2;
	bool multiplierClipFold3;
	bool multiplierClipFold4;
	bool multiplierClipFold5;

	double multiplierInvStrength1;
	double multiplierInvStrength2;
	double multiplierInvStrength3;
	double multiplierInvStrength4;
	double multiplierInvStrength5;

	double multiplierInvThreshold1;
	double multiplierInvThreshold2;
	double multiplierInvThreshold3;
	double multiplierInvThreshold4;
	double multiplierInvThreshold5;

	double multiplierInvDecay1;
	double multiplierInvDecay2;
	double multiplierInvDecay3;
	double multiplierInvDecay4;
	double multiplierInvDecay5;

	double multiplierInvBias1;
	double multiplierInvBias2;
	double multiplierInvBias3;
	double multiplierInvBias4;
	double multiplierInvBias5;

	double multiplierInvSmooth1;
	double multiplierInvSmooth2;
	double multiplierInvSmooth3;
	double multiplierInvSmooth4;
	double multiplierInvSmooth5;

	double multiplierInvRangeMin1;
	double multiplierInvRangeMin2;
	double multiplierInvRangeMin3;
	double multiplierInvRangeMin4;
	double multiplierInvRangeMin5;

	double multiplierInvRangeMax1;
	double multiplierInvRangeMax2;
	double multiplierInvRangeMax3;
	double multiplierInvRangeMax4;
	double multiplierInvRangeMax5;

	int multiplierInvMode1;
	int multiplierInvMode2;
	int multiplierInvMode3;
	int multiplierInvMode4;
	int multiplierInvMode5;

	int multiplierInvAxis1;
	int multiplierInvAxis2;
	int multiplierInvAxis3;
	int multiplierInvAxis4;
	int multiplierInvAxis5;

	bool multiplierInvOscillate1;
	bool multiplierInvOscillate2;
	bool multiplierInvOscillate3;
	bool multiplierInvOscillate4;
	bool multiplierInvOscillate5;
		int multiplierBurstLength1;
		int multiplierBurstLength2;
		int multiplierBurstLength3;
		int multiplierBurstLength4;
		int multiplierBurstLength5;
		int multiplierBurstGap1;
		int multiplierBurstGap2;
		int multiplierBurstGap3;
		int multiplierBurstGap4;
		int multiplierBurstGap5;
		double multiplierSphericalFalloff1;
		double multiplierSphericalFalloff2;
		double multiplierSphericalFalloff3;
		double multiplierSphericalFalloff4;
		double multiplierSphericalFalloff5;
		bool multiplierAccumulate1;
		bool multiplierAccumulate2;
		bool multiplierAccumulate3;
		bool multiplierAccumulate4;
		bool multiplierAccumulate5;
		double multiplierWrapRange1;
		double multiplierWrapRange2;
		double multiplierWrapRange3;
		double multiplierWrapRange4;
		double multiplierWrapRange5;
		int multiplierConditionalMode1;
		int multiplierConditionalMode2;
		int multiplierConditionalMode3;
		int multiplierConditionalMode4;
		int multiplierConditionalMode5;
		double multiplierConditionalThreshold1;
		double multiplierConditionalThreshold2;
		double multiplierConditionalThreshold3;
		double multiplierConditionalThreshold4;
		double multiplierConditionalThreshold5;
		int multiplierRampIn1;
		int multiplierRampIn2;
		int multiplierRampIn3;
		int multiplierRampIn4;
		int multiplierRampIn5;
		int multiplierRampOut1;
		int multiplierRampOut2;
		int multiplierRampOut3;
		int multiplierRampOut4;
		int multiplierRampOut5;
		double multiplierCylindricalBias1;
		double multiplierCylindricalBias2;
		double multiplierCylindricalBias3;
		double multiplierCylindricalBias4;
		double multiplierCylindricalBias5;
		bool multiplierSlotDisable1;
		bool multiplierSlotDisable2;
		bool multiplierSlotDisable3;
		bool multiplierSlotDisable4;
		bool multiplierSlotDisable5;
		double multiplierSlewRate1;
		double multiplierSlewRate2;
		double multiplierSlewRate3;
		double multiplierSlewRate4;
		double multiplierSlewRate5;
		double multiplierHysteresis1;
		double multiplierHysteresis2;
		double multiplierHysteresis3;
		double multiplierHysteresis4;
		double multiplierHysteresis5;
		double multiplierSoftExp1;
		double multiplierSoftExp2;
		double multiplierSoftExp3;
		double multiplierSoftExp4;
		double multiplierSoftExp5;
		double multiplierAntiAlias1;
		double multiplierAntiAlias2;
		double multiplierAntiAlias3;
		double multiplierAntiAlias4;
		double multiplierAntiAlias5;
		double multiplierDistCull1;
		double multiplierDistCull2;
		double multiplierDistCull3;
		double multiplierDistCull4;
		double multiplierDistCull5;
		double multiplierNeutralEps1;
		double multiplierNeutralEps2;
		double multiplierNeutralEps3;
		double multiplierNeutralEps4;
		double multiplierNeutralEps5;

		// Batch 1: Spatial + Temporal params
		double multiplierGradientDir1;
		double multiplierGradientDir2;
		double multiplierGradientDir3;
		double multiplierGradientDir4;
		double multiplierGradientDir5;
		double multiplierVoronoiScale1;
		double multiplierVoronoiScale2;
		double multiplierVoronoiScale3;
		double multiplierVoronoiScale4;
		double multiplierVoronoiScale5;
		double multiplierToroidalR1;
		double multiplierToroidalR2;
		double multiplierToroidalR3;
		double multiplierToroidalR4;
		double multiplierToroidalR5;
		int multiplierAngularStripes1;
		int multiplierAngularStripes2;
		int multiplierAngularStripes3;
		int multiplierAngularStripes4;
		int multiplierAngularStripes5;
		double multiplierGeoProgression1;
		double multiplierGeoProgression2;
		double multiplierGeoProgression3;
		double multiplierGeoProgression4;
		double multiplierGeoProgression5;
		int multiplierParityGate1;
		int multiplierParityGate2;
		int multiplierParityGate3;
		int multiplierParityGate4;
		int multiplierParityGate5;
		bool multiplierFibonacciStep1;
		bool multiplierFibonacciStep2;
		bool multiplierFibonacciStep3;
		bool multiplierFibonacciStep4;
		bool multiplierFibonacciStep5;

		// Batch 2: Slot interaction + Math + Artistic
		int multiplierAMSourceSlot1;
		int multiplierAMSourceSlot2;
		int multiplierAMSourceSlot3;
		int multiplierAMSourceSlot4;
		int multiplierAMSourceSlot5;
		int multiplierGateSourceSlot1;
		int multiplierGateSourceSlot2;
		int multiplierGateSourceSlot3;
		int multiplierGateSourceSlot4;
		int multiplierGateSourceSlot5;
		double multiplierPhaseLockOffset1;
		double multiplierPhaseLockOffset2;
		double multiplierPhaseLockOffset3;
		double multiplierPhaseLockOffset4;
		double multiplierPhaseLockOffset5;
		int multiplierRingModSlot1;
		int multiplierRingModSlot2;
		int multiplierRingModSlot3;
		int multiplierRingModSlot4;
		int multiplierRingModSlot5;
		int multiplierCombinator1;
		int multiplierCombinator2;
		int multiplierCombinator3;
		int multiplierCombinator4;
		int multiplierCombinator5;
		int multiplierInterpCurve1;
		int multiplierInterpCurve2;
		int multiplierInterpCurve3;
		int multiplierInterpCurve4;
		int multiplierInterpCurve5;
		double multiplierDitherQuantize1;
		double multiplierDitherQuantize2;
		double multiplierDitherQuantize3;
		double multiplierDitherQuantize4;
		double multiplierDitherQuantize5;
		bool multiplierComplexMag1;
		bool multiplierComplexMag2;
		bool multiplierComplexMag3;
		bool multiplierComplexMag4;
		bool multiplierComplexMag5;
		double multiplierPaletteIdxDrive1;
		double multiplierPaletteIdxDrive2;
		double multiplierPaletteIdxDrive3;
		double multiplierPaletteIdxDrive4;
		double multiplierPaletteIdxDrive5;
		double multiplierOrbitTrapWeight1;
		double multiplierOrbitTrapWeight2;
		double multiplierOrbitTrapWeight3;
		double multiplierOrbitTrapWeight4;
		double multiplierOrbitTrapWeight5;
		int multiplierTurbulenceLayers1;
		int multiplierTurbulenceLayers2;
		int multiplierTurbulenceLayers3;
		int multiplierTurbulenceLayers4;
		int multiplierTurbulenceLayers5;
		double multiplierKaleidoscopeBias1;
		double multiplierKaleidoscopeBias2;
		double multiplierKaleidoscopeBias3;
		double multiplierKaleidoscopeBias4;
		double multiplierKaleidoscopeBias5;
		double multiplierPhaseRandomise1;
		double multiplierPhaseRandomise2;
		double multiplierPhaseRandomise3;
		double multiplierPhaseRandomise4;
		double multiplierPhaseRandomise5;










	// Dedicated multiplier enable/value/iteration params (no conflicts with formula logic)
	bool multiplierEnabled1;
	bool multiplierEnabled2;
	bool multiplierEnabled3;
	bool multiplierEnabled4;
	bool multiplierEnabled5;

	double multiplierScale1;
	double multiplierScale2;
	double multiplierScale3;
	double multiplierScale4;
	double multiplierScale5;

	int multiplierStartIter1;
	int multiplierStartIter2;
	int multiplierStartIter3;
	int multiplierStartIter4;
	int multiplierStartIter5;

	int multiplierStopIter1;
	int multiplierStopIter2;
	int multiplierStopIter3;
	int multiplierStopIter4;
	int multiplierStopIter5;



	CVector4 additionConstant0555;
	CVector4 additionConstant0777;
	CVector4 additionConstant000;
	CVector4 additionConstantA000;
	CVector4 additionConstantP000;
	CVector4 additionConstant111;
	CVector4 additionConstantA111;
	CVector4 additionConstant222;
	CVector4 additionConstantNeg100;
	CVector4 constantMultiplier000;
	CVector4 constantMultiplier001;
	CVector4 constantMultiplier010;
	CVector4 constantMultiplier100;
	CVector4 constantMultiplierA100;
	CVector4 constantMultiplier111;
	CVector4 constantMultiplierA111;
	CVector4 constantMultiplierB111;
	CVector4 constantMultiplierC111;
	CVector4 constantMultiplier121;
	CVector4 constantMultiplier122;
	CVector4 constantMultiplier221;
	CVector4 constantMultiplier222;
	CVector4 constantMultiplier441;
	CVector4 juliaC;
	CVector4 offset000;
	CVector4 offsetA000;
	CVector4 offsetF000;
	CVector4 offset001;
	CVector4 offset002;
	CVector4 offset010;
	CVector4 offset100;
	CVector4 offset101;
	CVector4 offset110;
	CVector4 offset1105;
	CVector4 offset111;
	CVector4 offsetA111;
	CVector4 offsetB111;
	CVector4 offsetC111;
	CVector4 offset200;
	CVector4 offsetA200;
	CVector4 offset222;
	CVector4 offsetA222;
	CVector4 offset333;
	CVector4 power025;
	CVector4 power8;
	CVector4 vec111;

	CVector3 rotation; // vec3s
	CVector3 rotation2;
	CVector3 rotationXYZ;
	CVector3 rotation2XYZ;
	CVector3 rotationVary;
	CVector3 rotation44a; //.........................
	CVector3 rotation44b; //..........................

	CVector4 scaleP222;
	CVector4 scale3D000;
	CVector4 scale3D111;
	CVector4 scale3D222;
	CVector4 scale3Da222;
	CVector4 scale3Db222;
	CVector4 scale3Dc222;
	CVector4 scale3Dd222;
	CVector4 scale3D333;
	CVector4 scale3D444;

	CVector4 additionConstant0000;
	CVector4 offset0000;
	CVector4 offsetA0000;
	CVector4 offsetB0000;
	CVector4 offsetp5555;
	CVector4 offset1111;
	CVector4 offsetA1111;
	CVector4 offsetB1111;
	CVector4 offsetNeg1111;
	CVector4 offset2222;
	CVector4 additionConstant111d5;
	CVector4 constantMultiplier1220;
	CVector4 scale0000;
	CVector4 scale1111;

	CRotationMatrix rotationMatrix;
	CRotationMatrix rotationMatrix2;
	CRotationMatrix rotationMatrixXYZ;
	CRotationMatrix rotationMatrix2XYZ;
	CRotationMatrix rotationMatrixVary;
	CRotationMatrix44 rotationMatrix44; //....................

	bool addCpixelEnabled;
	bool addCpixelEnabledFalse;
	bool alternateEnabledFalse;
	bool benesiT1Enabled;
	bool benesiT1EnabledFalse;
	bool benesiT1MEnabledFalse;
	bool functionEnabled4dFalse;
	bool functionEnabledAuxCFalse;
	bool functionEnabled;
	bool functionEnabledFalse;
	bool functionEnabledx;
	bool functionEnabledy;
	bool functionEnabledz;
	bool functionEnabledw;
	bool functionEnabledxFalse;
	bool functionEnabledyFalse;
	bool functionEnabledzFalse;
	bool functionEnabledwFalse;
	bool functionEnabledAx;
	bool functionEnabledAy;
	bool functionEnabledAz;
	bool functionEnabledAw;
	bool functionEnabledAxFalse;
	bool functionEnabledAyFalse;
	bool functionEnabledAzFalse;
	bool functionEnabledAwFalse;
	bool functionEnabledBx;
	bool functionEnabledBy;
	bool functionEnabledBz;
	bool functionEnabledBxFalse;
	bool functionEnabledByFalse;
	bool functionEnabledBzFalse;
	bool functionEnabledBwFalse;
	bool functionEnabledCx;
	bool functionEnabledCy;
	bool functionEnabledCz;
	bool functionEnabledCxFalse;
	bool functionEnabledCyFalse;
	bool functionEnabledCzFalse;
	bool functionEnabledCwFalse;
	bool functionEnabledAFalse;
	bool functionEnabledBFalse;
	bool functionEnabledCFalse;
	bool functionEnabledDFalse;
	bool functionEnabledEFalse;
	bool functionEnabledFFalse;
	bool functionEnabledGFalse;
	bool functionEnabledHFalse;
	bool functionEnabledIFalse;
	bool functionEnabledJFalse;
	bool functionEnabledKFalse;
	bool functionEnabledM;
	bool functionEnabledMFalse;
	bool functionEnabledNFalse;
	bool functionEnabledOFalse;
	bool functionEnabledPFalse;
	bool functionEnabledRFalse;
	bool functionEnabledSFalse;
	bool functionEnabledSwFalse;
	bool functionEnabledTFalse;
	bool functionEnabledXFalse;
	bool functionEnabledYFalse;
	bool functionEnabledZcFalse;
	bool juliaMode;
	bool rotationEnabled;
	bool rotationEnabledFalse;
	bool rotation2EnabledFalse;
	bool sphereInversionEnabledFalse;
	bool spheresEnabled;

	// bool functionEnabledTempFalse;
};

struct sFractal
{
	sFractal() {};
	sFractal(const std::shared_ptr<cParameterContainer> par);
	void RecalculateFractalParams();

	fractal::enumFractalFormula formula;
	sFractalMandelbulb bulb;
	sFractalIFS IFS;
	sFractalMandelbox mandelbox;
	sFractalGeneralizedFoldBox genFoldBox;
	sFractalBoxFoldBulbPow2 foldingIntPow;
	sFractalMandelboxVary4D mandelboxVary4D;
	sFractalAexion aexion;
	sFractalBuffalo buffalo;
	sFractalPlatonicSolid platonicSolid;
	sFractalTransformCommon transformCommon;
	sFractalAnalyticDE analyticDE;
	sFractalMandelbulbMulti mandelbulbMulti;
	sFractalSinTan2Trig sinTan2Trig;
	sFractalSurfBox surfBox;
	sFractalSurfFolds surfFolds;
	sFractalDonut donut;
	sFoldColor foldColor;
	sFractalMagTransforms magTransf;
	sFractalCpara Cpara;
	sFractalCombo combo;
	sFractalASurf3Folds aSurf3Folds;
	sFractalCombo3 combo3;
	sFractalCombo4 combo4;
	sFractalCombo5 combo5;
	sFractalCombo6 combo6;
	sFractalMandalay mandalay;

#ifdef USE_OPENCL
//	double customParameters[15];
//	double deltaDEStep;
//	char customOCLFormulaName[100];
//	fractal::enumOCLDEMode customOCLFormulaDEMode;
#endif
};

#endif /* MANDELBULBER2_SRC_FRACTAL_H_ */
// Multiplier system v4.1 — burst/falloff/wrap/conditional
