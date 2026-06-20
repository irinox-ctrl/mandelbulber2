/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2014-19 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * list of fractal formulas
 */

#include "all_fractal_list.hpp"

#include "legacy_fractal_transforms.hpp"

QList<cAbstractFractal *> newFractalList;

using namespace fractal;
void DefineFractalList(QList<cAbstractFractal *> *fractalList)
{
	//====================== FRACTAL LIST - START ==================
	fractalList->append(new cFractalNone());
#ifdef USE_OPENCL
	fractalList->append(new cFractalCustom());
#endif
	//------------------------ ANALYTIC DE FORMULAS ----------------------
	// ----- Logarithmic -------
	fractalList->append(new cFractalAexion());
	fractalList->append(new cFractalAexion4dV2());

	// Benesi formulas
	fractalList->append(new cFractalBenesiPineTree());
	fractalList->append(new cFractalBenesi());
	fractalList->append(new cFractalBenesiPwr2Mandelbulb());
	fractalList->append(new cFractalBenesiT1PineTree());

	// boxBulb formulas
	fractalList->append(new cFractalBoxFoldBulbPow2V2());
	fractalList->append(new cFractalBoxFoldBulbPow2V3());
	fractalList->append(new cFractalBoxFoldBulbMenger());
	fractalList->append(new cFractalBoxFoldQuat());
	fractalList->append(new cFractalBoxFold4dBulbPow2());
	fractalList->append(new cFractalBoxFoldBulbV4());

	fractalList->append(new cFractalBristorbrot());
	fractalList->append(new cFractalBristorbrot2());
	fractalList->append(new cFractalBristorbrot4d());
	fractalList->append(new cFractalBuffalo());

	// Nested sin() formulas
	fractalList->append(new cFractalCoastalbrot());

	// hypercomlex
	fractalList->append(new cFractalHypercomplex());
	fractalList->append(new cFractalHypercomplexV2());
	fractalList->append(new cFractalIqBulb());
	fractalList->append(new cFractalLkmitch());
	fractalList->append(new cFractalMakin3d2());

	// Mandelbulb formulas
	fractalList->append(new cFractalMandelbar());
	fractalList->append(new cFractalMandelbarV2());
	fractalList->append(new cFractalMandelbarV3());

	fractalList->append(new cFractalMandelbulb());
	fractalList->append(new cFractalMandelbulb2());
	fractalList->append(new cFractalMandelbulb3());
	fractalList->append(new cFractalMandelbulb4());
	fractalList->append(new cFractalMandelbulbAbs());
	fractalList->append(new cFractalMandelbulbAbsPower2());
	fractalList->append(new cFractalMandelbulbAtan2Power2());
	fractalList->append(new cFractalMandelbulbBermarte());
	fractalList->append(new cFractalMandelbulbEye());
	fractalList->append(new cFractalMandelbulbIqPow8());
	fractalList->append(new cFractalMandelbulbIqV2());
	fractalList->append(new cFractalMandelbulbJuliabulb());
	fractalList->append(new cFractalMandelbulbKali());
	fractalList->append(new cFractalMandelbulbKaliMulti());
	fractalList->append(new cFractalMandelbulbKosalos());
	fractalList->append(new cFractalMandelbulbKosalosV2());
	fractalList->append(new cFractalMandelbulbLambda());
	fractalList->append(new cFractalModulusMandelbulb());
	fractalList->append(new cFractalMandelbulbMulti());
	fractalList->append(new cFractalMandelbulbMulti2());
	fractalList->append(new cFractalMandelbulbPlusZ());
	fractalList->append(new cFractalMandelbulbPower1234());
	fractalList->append(new cFractalMandelbulbPower2());
	fractalList->append(new cFractalMandelbulbPow2V1());
	fractalList->append(new cFractalMandelbulbPow2V2());
	fractalList->append(new cFractalMandelbulbPow2V3());
	fractalList->append(new cFractalMandelbulbPupuku());
	fractalList->append(new cFractalMandelbulbQuadrat());
	fractalList->append(new cFractalMandelbulbQuat());
	fractalList->append(new cFractalMandelbulbSinCos());
	fractalList->append(new cFractalMandelbulbSinCosV2());
	fractalList->append(new cFractalMandelbulbSinCosV3());
	fractalList->append(new cFractalMandelbulbSinCosV4());
	fractalList->append(new cFractalMandelbulbVaryPowerV1());
	fractalList->append(new cFractalMandelcup());
	fractalList->append(new cFractalMandelnest());
	fractalList->append(new cFractalMandelnestFull());
	fractalList->append(new cFractalMandelnestV2());
	fractalList->append(new cFractalMandelnest4d());
	fractalList->append(new cFractalMandeltorus());
	fractalList->append(new cFractalMandeltorusV2());

	// Msltoe formulas
	fractalList->append(new cFractalMsltoeSym2Mod());
	fractalList->append(new cFractalMsltoeSym3Mod());
	fractalList->append(new cFractalEiffieMsltoe());
	fractalList->append(new cFractalMsltoeSym3Mod2());
	fractalList->append(new cFractalMsltoeSym3Mod3());
	fractalList->append(new cFractalMsltoeSym3Mod4());
	fractalList->append(new cFractalMsltoeSym3Mod5());
	fractalList->append(new cFractalMsltoeSym3Mod6());
	fractalList->append(new cFractalMsltoeSym4Mod());
	fractalList->append(new cFractalMsltoeSym4Mod1());
	fractalList->append(new cFractalMsltoeToroidal());
	fractalList->append(new cFractalMsltoeToroidalV2());
	fractalList->append(new cFractalMsltoeToroidalMulti());




	// Quaternion formulas
	fractalList->append(new cFractalQuaternion());
	fractalList->append(new cFractalQuaternion3d());
	fractalList->append(new cFractalQuaternion4d());
	fractalList->append(new cFractalQuaternionCubic4d());

	// Quick Dudley formulas
	fractalList->append(new cFractalQuickDudley());
	fractalList->append(new cFractalQuickDudleyMod());

	// Riemann formulas
	fractalList->append(new cFractalRiemannSphereHoboldPow4());
	fractalList->append(new cFractalRiemannSphereHoboldPow8());
	fractalList->append(new cFractalRiemannSphereHoboldMulti());
	fractalList->append(new cFractalRiemannSphereMsltoeV1());
	fractalList->append(new cFractalRiemannSphereMsltoeV2());

	fractalList->append(new cFractalXenodreambuie());
	fractalList->append(new cFractalXenodreambuieV2());
	fractalList->append(new cFractalXenodreambuieV3());

	// ----- Linear -------

	// Abox formulas
	fractalList->append(new cFractalAboxMod1());
	fractalList->append(new cFractalAboxMod2());
	fractalList->append(new cFractalAboxMod11());
	fractalList->append(new cFractalAboxMod12());
	fractalList->append(new cFractalAboxMod13());
	fractalList->append(new cFractalAboxMod14());
	fractalList->append(new cFractalAboxMod15());
	fractalList->append(new cFractalAboxModKali());
	fractalList->append(new cFractalAboxModKaliEiffie());
	fractalList->append(new cFractalAboxModKaliV2());
	fractalList->append(new cFractalAboxModKaliV3());
	fractalList->append(new cFractalAboxDonut4d());
	fractalList->append(new cFractalAboxDonut4dV2());
	fractalList->append(new cFractalAboxKlein());
	fractalList->append(new cFractalAboxSphere4d());
	fractalList->append(new cFractalAboxSmooth());
	fractalList->append(new cFractalAboxSurfBox());
	fractalList->append(new cFractalAboxTetra());
	fractalList->append(new cFractalAboxTetra4d());
	fractalList->append(new cFractalAboxVSIcen1());
	fractalList->append(new cFractalAbox4d());

	// Amazing Surf formulas
	fractalList->append(new cFractalAmazingIfs());
	fractalList->append(new cFractalAmazingSurf());
	fractalList->append(new cFractalAmazingSurfMod1());
	fractalList->append(new cFractalAmazingSurfMod2());
	fractalList->append(new cFractalAmazingSurfMod3());
	fractalList->append(new cFractalAmazingSurfMod4());
	fractalList->append(new cFractalAmazingSurfKlein());
	fractalList->append(new cFractalAmazingSurfKleinV2());
	fractalList->append(new cFractalAmazingSurfM3d());
	fractalList->append(new cFractalAmazingSurfMulti());

	fractalList->append(new cFractalBenesiMagTransforms());

	// Collatz formulas
	fractalList->append(new cFractalCollatz());
	fractalList->append(new cFractalCollatzMod());

	// Folds and IFS
	fractalList->append(new cFractalFoldBoxMod1());
	fractalList->append(new cFractalGeneralizedFoldBox());
	fractalList->append(new cFractalIfsGen());
	fractalList->append(new cFractalIfsXY());
	fractalList->append(new cFractalKaleidoscopicIfs());
	fractalList->append(new cFractalKalisets1());
	fractalList->append(new cFractalKochIfs());

	fractalList->append(new cFractalMandalayBoxV1());
	fractalList->append(new cFractalMandalayBoxV2());
	fractalList->append(new cFractalMandalayKIFS());

	// Mandelbox formulas
	fractalList->append(new cFractalMandelbox());
	fractalList->append(new cFractalMandelboxFast());
	fractalList->append(new cFractalMandelboxMenger());
	fractalList->append(new cFractalMandelboxSmooth());
	fractalList->append(new cFractalMandelboxVariable());
	fractalList->append(new cFractalMandelboxVaryScale4d());

	// Menger formulas
	fractalList->append(new cFractalMengerSponge());
	fractalList->append(new cFractalMengerChebyshev());
	fractalList->append(new cFractalMengerCrossKIFS());
	fractalList->append(new cFractalMengerCrossMod1());
	fractalList->append(new cFractalMengerMod1());
	fractalList->append(new cFractalModulusMengerSponge());
	fractalList->append(new cFractalMengerMiddleMod());
	fractalList->append(new cFractalMengerOcto());
	fractalList->append(new cFractalMengerPrismShape());
	fractalList->append(new cFractalMengerPrismShape2());
	fractalList->append(new cFractalMengerPolyFold());
	fractalList->append(new cFractalMengerPwr2Poly());
	fractalList->append(new cFractalMengerPyramid());
	fractalList->append(new cFractalMengerSmooth());
	fractalList->append(new cFractalMengerSmoothMod1());
	fractalList->append(new cFractalMengerSmoothChebyshev());
	fractalList->append(new cFractalMengerV4());
	fractalList->append(new cFractalMengerV5());
	fractalList->append(new cFractalMenger3());
	fractalList->append(new cFractalMenger3M3d());
	fractalList->append(new cFractalMenger4d());
	fractalList->append(new cFractalMenger4dMod1());
	fractalList->append(new cFractalMenger4dMod2());

	fractalList->append(new cFractalMixPinski4d());
	fractalList->append(new cFractalSierpinski3d());
	fractalList->append(new cFractalSierpinski3dV2());
	fractalList->append(new cFractalSierpinski3dV3());
	fractalList->append(new cFractalSierpinski3dV4());
	fractalList->append(new cFractalSierpinski4d());
	fractalList->append(new cFractalSpheretreeV4());
	fractalList->append(new cFractalVicsek());

	// ----- JosLeys-Kleinian -----
	fractalList->append(new cFractalJosKleinian());
	fractalList->append(new cFractalJosKleinianV2());

	// ----- Pseudo Kleinian ----
	fractalList->append(new cFractalPseudoKleinian());
	fractalList->append(new cFractalPseudoKleinianMod1());
	fractalList->append(new cFractalPseudoKleinianMod2());
	fractalList->append(new cFractalPseudoKleinianMod4());
	fractalList->append(new cFractalPseudoKleinianMod5());


	// ----- custom DE - dIFS formulas------
	fractalList->append(new cFractalDIFSAmazingIfs());
	fractalList->append(new cFractalDIFSBoxV1());
	fractalList->append(new cFractalDIFSBoxDiagonalV1());
	fractalList->append(new cFractalDIFSBoxDiagonalV3());
	fractalList->append(new cFractalDIFSCylinder());
	fractalList->append(new cFractalDIFSEllipsoid());
	fractalList->append(new cFractalDIFSGreekIfs());
	fractalList->append(new cFractalDIFSHextgrid2());
	fractalList->append(new cFractalDIFSMenger());
	fractalList->append(new cFractalDIFSMsltoeDonut());
	fractalList->append(new cFractalDIFSPrism());
	fractalList->append(new cFractalDIFSSphere());
	fractalList->append(new cFractalDIFSTorus());
	fractalList->append(new cFractalDIFSMultiV1());

	// ---- custom DE - dIFS transforms----
	fractalList->append(new cFractalTransfDIFSAmazingIfs());
	fractalList->append(new cFractalTransfDIFSBox());
	fractalList->append(new cFractalTransfDIFSBoxV2());
	fractalList->append(new cFractalTransfDIFSBoxV3());
	fractalList->append(new cFractalTransfDIFSBoxFrame());
	fractalList->append(new cFractalTransfDIFSCayley2());
	fractalList->append(new cFractalTransfDIFSChessboard());
	fractalList->append(new cFractalTransfDIFSClipCustom());
	fractalList->append(new cFractalTransfDIFSClipPlane());
	fractalList->append(new cFractalTransfDIFSCylinder());
	fractalList->append(new cFractalTransfDIFSCylinderV2());
	fractalList->append(new cFractalTransfDIFSDiamond());
	fractalList->append(new cFractalTransfDIFSEllipsoid());
	fractalList->append(new cFractalTransfDIFSGearV1());
	fractalList->append(new cFractalTransfDIFSGrid());
	fractalList->append(new cFractalTransfDIFSGridV2());
	fractalList->append(new cFractalTransfDIFSGridV3());
	fractalList->append(new cFractalTransfDIFSHeart());
	fractalList->append(new cFractalTransfDIFSHelix());
	fractalList->append(new cFractalTransfDIFSHelixV2());
	fractalList->append(new cFractalTransfDIFSHelixMenger());
	fractalList->append(new cFractalTransfDIFSHextgrid2());
	fractalList->append(new cFractalTransfDIFSHexprism());
	fractalList->append(new cFractalTransfDIFSHexprismV2());
	fractalList->append(new cFractalTransfDIFSOctahedron());
	fractalList->append(new cFractalTransfDIFSOctahedronV2());
	fractalList->append(new cFractalTransfDIFSPiriform());
	fractalList->append(new cFractalTransfDIFSPolyhedra());
	fractalList->append(new cFractalTransfDIFSPolyhedraV2());
	fractalList->append(new cFractalTransfDIFSPrism());
	fractalList->append(new cFractalTransfDIFSPrismV2());
	fractalList->append(new cFractalTransfDIFSSphere());
	fractalList->append(new cFractalTransfDIFSSphereGrid());
	fractalList->append(new cFractalTransfDIFSSphereGridV2());
	fractalList->append(new cFractalTransfDIFSSphereGridV3());
	fractalList->append(new cFractalTransfDIFSSpring());
	fractalList->append(new cFractalTransfDIFSSupershape());
	fractalList->append(new cFractalTransfDIFSSupershapeV2());
	fractalList->append(new cFractalTransfDIFSTorus());
	fractalList->append(new cFractalTransfDIFSTorusV2());
	fractalList->append(new cFractalTransfDIFSTorusV3());
	fractalList->append(new cFractalTransfDIFSTorusV4());
	fractalList->append(new cFractalTransfDIFSTube());
	fractalList->append(new cFractalTransfDIFSTorusGrid());
	fractalList->append(new cFractalTransfDIFSTorusMenger());
	fractalList->append(new cFractalTransfDIFSTorusTwist());
	fractalList->append(new cFractalTransfDIFSTriGrid());

	fractalList->append(new cFractalTransfDIFSHybridColor());

	// ---- custom DE - non-dIFS Formulas----
	fractalList->append(new cFractalFoldCutCube());
	fractalList->append(new cFractalJosKleinianV3());
	fractalList->append(new cFractalJosKleinianV4());
	fractalList->append(new cFractalKoch());
	fractalList->append(new cFractalKochV2());
	fractalList->append(new cFractalKochV3());
	fractalList->append(new cFractalKochV4());
	fractalList->append(new cFractalKochV5());
	fractalList->append(new cFractalKnotV1());
	fractalList->append(new cFractalKnotV2());
	fractalList->append(new cFractalMengerV2());
	fractalList->append(new cFractalMengerV3());
	fractalList->append(new cFractalMengerV6());
    fractalList->append(new cFractalMengerV7());
	fractalList->append(new cFractalOctahedron());
	fractalList->append(new cFractalPseudoKleinianStdDE());
	fractalList->append(new cFractalPseudoKleinianMod3());
	fractalList->append(new cFractalPseudoKleinianMod6());
	fractalList->append(new cFractalPseudoKleinian4d());
	fractalList->append(new cFractalSphereCluster());
	fractalList->append(new cFractalSphereClusterV2());
	fractalList->append(new cFractalSphereClusterV3());
	fractalList->append(new cFractalSpheretree());
	fractalList->append(new cFractalSpheretreeV2());
    fractalList->append(new cFractalSpheretreeV5());
	fractalList->append(new cFractalTransfDEControls());
	fractalList->append(new cFractalTransfDELinearCube());

	//------------------------ DELTA DE FORMULAS ------------------------

	// ----- Logarithmic -----
	fractalList->append(new cFractalAexionOctopusMod());

	fractalList->append(new cFractalIdes());
	fractalList->append(new cFractalIdes2());

	fractalList->append(new cFractalMandelbulbTails());
	fractalList->append(new cFractalMandelbulbTailsV2());
	fractalList->append(new cFractalNewtonPow3());
	fractalList->append(new cFractalRiemannBulbMsltoeMod2());
	fractalList->append(new cFractalRiemannSphereMsltoe());
	fractalList->append(new cFractalRiemannSphereMsltoeM3d());

	fractalList->append(new cFractalScatorPower2Real());
	fractalList->append(new cFractalScatorPower2Imaginary());

	// ----- Linear -----
	fractalList->append(new cFractalBoxFoldBulbPow2());
	fractalList->append(new cFractalMsltoeDonut());


	//-------------------------- Transforms -----------------------------------

	// Abs Transforms
	fractalList->append(new cFractalTransfAbsAddConditional());
	fractalList->append(new cFractalTransfAbsAddConditional2());
	fractalList->append(new cFractalTransfAbsAddConstant());
	fractalList->append(new cFractalTransfAbsAddConstantV2());
	fractalList->append(new cFractalTransfAbsAddConstant4d());
	fractalList->append(new cFractalTransfAbsAddTgladFold());
	fractalList->append(new cFractalTransfAbsAddTgladFold4d());
	fractalList->append(new cFractalTransfAbsAddMulti());
	fractalList->append(new cFractalTransfAbsAddMulti4d());
	fractalList->append(new cFractalTransfNegAbsAddConstant());
	fractalList->append(new cFractalTransfAbsAddConditional4d());
	fractalList->append(new cFractalTransfAbsRecFoldXY());
	fractalList->append(new cFractalTransfAbsSym3());

	// Add Transforms
	fractalList->append(new cFractalTransfAddConstant());
	fractalList->append(new cFractalTransfAddConstant4d());
	fractalList->append(new cFractalTransfAddConstantMod1());
	fractalList->append(new cFractalTransfAddConstantMod2());
	fractalList->append(new cFractalTransfAddConstantMod3());
	fractalList->append(new cFractalTransfAddConstantRotV1());
	fractalList->append(new cFractalTransfAddConstantVaryV1());
	fractalList->append(new cFractalTransfAddNorm());
	fractalList->append(new cFractalTransfAddExp2Z());
	fractalList->append(new cFractalTransfAddScaleRotate());
	fractalList->append(new cFractalTransfAddSphericalInvert());

	// Add Cpixel Transforms
	fractalList->append(new cFractalTransfAddCpixel());
	fractalList->append(new cFractalTransfAddCpixel4d());
	fractalList->append(new cFractalTransfAddCpixelAxisSwap());
	fractalList->append(new cFractalTransfAddCpixelRotated());
	fractalList->append(new cFractalTransfAddCpixelCxCyAxisSwap());
	fractalList->append(new cFractalTransfAddCpixelInvert());
	fractalList->append(new cFractalTransfAddCpixelScator());
	fractalList->append(new cFractalTransfAddCpixelSinOrCos());
	fractalList->append(new cFractalTransfAddCpixelSphereFold());
	fractalList->append(new cFractalTransfAddCpixelSymmetrical());
	fractalList->append(new cFractalTransfAddCpixelTile());
	fractalList->append(new cFractalTransfAddCpixelVaryV1());

	// Benesi Transforms
	fractalList->append(new cFractalTransfBenesiT1());
	fractalList->append(new cFractalTransfBenesiT1Mod());
	fractalList->append(new cFractalTransfBenesiT2());
	fractalList->append(new cFractalTransfBenesiT3());
	fractalList->append(new cFractalTransfBenesiT4());
	fractalList->append(new cFractalTransfBenesiT5b());
	fractalList->append(new cFractalTransfBenesiCubeSphere());
	fractalList->append(new cFractalTransfBenesiSphereCube());
	fractalList->append(new cFractalTransfBenesiMagForward());
	fractalList->append(new cFractalTransfBenesiMagBackward());

	fractalList->append(new cFractalTransfBlockify());
	fractalList->append(new cFractalTransfBlockifyV2());

	// Box Fold Transforms
	fractalList->append(new cFractalTransfBoxFold());
	fractalList->append(new cFractalTransfBoxFold4d());
	fractalList->append(new cFractalTransfBoxFold4dTglad());
	fractalList->append(new cFractalTransfBoxFold4dInfy());
	fractalList->append(new cFractalTransfBoxFoldVaryV1());
	fractalList->append(new cFractalTransfBoxFoldXYZ());

	fractalList->append(new cFractalTransfBoxOffset());
	fractalList->append(new cFractalTransfBoxTiling4d());
	fractalList->append(new cFractalTransfBoxTilingV2());
	fractalList->append(new cFractalTransfBoxTilingV3());
	fractalList->append(new cFractalTransfBoxWrap4d());
	fractalList->append(new cFractalTransfCayley2V1());
	fractalList->append(new cFractalTransfClamp4d());
	fractalList->append(new cFractalTransfDiagonalFold());
	fractalList->append(new cFractalTransfDotFold());
	fractalList->append(new cFractalTransfFoldingTetra3d());
	fractalList->append(new cFractalTransfGnarl());
	fractalList->append(new cFractalTransfIterationWeight());
	fractalList->append(new cFractalTransfIterationWeight4d());
	fractalList->append(new cFractalTransfInitial4d());
	fractalList->append(new cFractalTransfInvCylindrical());
	fractalList->append(new cFractalTransfJuliabox());
	fractalList->append(new cFractalTransfJuliaboxV2());
	fractalList->append(new cFractalTransfLinCombineCXYZ());
	fractalList->append(new cFractalTransfLowResMode());
	fractalList->append(new cFractalTransfMandalayFoldV1());
	fractalList->append(new cFractalTransfMandalayFoldV2());
	fractalList->append(new cFractalTransfMandalayFold4d());
	fractalList->append(new cFractalTransfMengerFold());
	fractalList->append(new cFractalTransfMengerFoldV2());
	fractalList->append(new cFractalTransfMultipleAngle());
	fractalList->append(new cFractalTransfOctoFold());
	fractalList->append(new cFractalTransfOffsetSCurve4d());
	fractalList->append(new cFractalTransfParabFold());
	fractalList->append(new cFractalTransfPlatonicSolid());
	fractalList->append(new cFractalTransfPolyFoldAtan());
	fractalList->append(new cFractalTransfPolyFoldAtan2());
	fractalList->append(new cFractalTransfPolyFoldAtan2Iter());
	fractalList->append(new cFractalTransfPolyFoldSymXY());
	fractalList->append(new cFractalTransfPolyFoldSymMulti());
	fractalList->append(new cFractalTransfPolyXYFoldV1());
	fractalList->append(new cFractalTransfPwr2Polynomial());
	fractalList->append(new cFractalTransfQuadraticFold4d());
	fractalList->append(new cFractalTransfQuaternionFold());

	// R Power Transforms
	fractalList->append(new cFractalTransfRpow3());
	fractalList->append(new cFractalTransfRPower());
	fractalList->append(new cFractalTransfReciprocal3());
	fractalList->append(new cFractalTransfReciprocal4d());

	// Rotation Transforms
	fractalList->append(new cFractalTransfRotation());
	fractalList->append(new cFractalTransfRotationM3d());
	fractalList->append(new cFractalTransfRotation4d());
	fractalList->append(new cFractalTransfRotateAboutVec3());
	fractalList->append(new cFractalTransfRotationChebyshev());
	fractalList->append(new cFractalTransfRotationIterControls());
	fractalList->append(new cFractalTransfRotationVaryV1());
	fractalList->append(new cFractalTransfRotationFoldingPlane());
	fractalList->append(new cFractalTransfRotationFolding());

	// Scale Transforms
	fractalList->append(new cFractalTransfScale());
	fractalList->append(new cFractalTransfScaleOffset());
	fractalList->append(new cFractalTransfScaleOffsetV2());
	fractalList->append(new cFractalTransfScaleVaryV212());
	fractalList->append(new cFractalTransfScaleVaryMulti());
	fractalList->append(new cFractalTransfScaleVaryV1());
	fractalList->append(new cFractalTransfScaleVaryVCL());
	fractalList->append(new cFractalTransfScale3d());
	fractalList->append(new cFractalTransfScale4d());

	// Trig Transforms
	fractalList->append(new cFractalTransfSinAdd());
	fractalList->append(new cFractalTransfSinOrCos());
	fractalList->append(new cFractalTransfSinAndCos());
	fractalList->append(new cFractalTransfSinAndCosMax());
	fractalList->append(new cFractalTransfSincos());
	fractalList->append(new cFractalTransfSincosV2());
	fractalList->append(new cFractalTransfSincosHelix());
	fractalList->append(new cFractalTransfSinTan());
	fractalList->append(new cFractalTransfSinYM3d());

	fractalList->append(new cFractalTransfSmooth());
	fractalList->append(new cFractalTransfSmoothV2());

	// Spherical Transforms
	fractalList->append(new cFractalTransfSphericalCoordInvs());
	fractalList->append(new cFractalTransfSphericalFold());
	fractalList->append(new cFractalTransfSphericalFold4d());
	fractalList->append(new cFractalTransfSphericalFold4dV2());
	fractalList->append(new cFractalTransfSphericalFoldAbox());
	fractalList->append(new cFractalTransfSphericalFoldCHS());
	fractalList->append(new cFractalTransfSphericalFoldCuboid());
	fractalList->append(new cFractalTransfSphericalFoldParab());
	fractalList->append(new cFractalTransfSphericalFoldPnorm());
	fractalList->append(new cFractalTransfSphericalFoldSmooth());
	fractalList->append(new cFractalTransfSphericalFoldVaryV1());
	fractalList->append(new cFractalTransfSphericalFoldVaryVCL());
	fractalList->append(new cFractalTransfSphericalFoldV1());
	fractalList->append(new cFractalTransfSphericalFoldV2());
	fractalList->append(new cFractalTransfSphericalFoldV3());
	fractalList->append(new cFractalTransfSphericalFoldXYZBias());
	fractalList->append(new cFractalTransfSphericalInv());
	fractalList->append(new cFractalTransfSphericalInvV2());
	fractalList->append(new cFractalTransfSphericalInvV3());
	fractalList->append(new cFractalTransfSphericalInvV4());
	fractalList->append(new cFractalTransfSphericalInvPnorm());
	fractalList->append(new cFractalTransfSphericalInvC());
	fractalList->append(new cFractalTransfSphericalPwrFold());
	fractalList->append(new cFractalTransfSphericalOffset());
	fractalList->append(new cFractalTransfSphericalOffsetVCL());


	fractalList->append(new cFractalTransfStepXY());

	// Surf Transforms
	fractalList->append(new cFractalTransfSurfBoxFold());
	fractalList->append(new cFractalTransfSurfBoxFoldV2());
	fractalList->append(new cFractalTransfSurfBoxFoldV24d());
	fractalList->append(new cFractalTransfSurfFoldMulti());
	fractalList->append(new cFractalTransfZvectorAxisSwap());


	// ------------------ hybrid color trial -----------------------
	fractalList->append(new cFractalTransfHybridColor());
	fractalList->append(new cFractalTransfHybridColor2());

	// ---------- experimental do not use -----------------------
	fractalList->append(new cFractalTesting());
	fractalList->append(new cFractalTestingLog());
	fractalList->append(new cFractalTesting4d());
	fractalList->append(new cFractalTestingTransform());
	fractalList->append(new cFractalTestingTransform2());


	fractalList->append(new cFractalEiffieCar());
	fractalList->append(new cFractalMsltoeToroidalV3());
	fractalList->append(new cFractalMandelbulbPow2V4());

	fractalList->append(new cFractalPseudoKleinianMod7());
	fractalList->append(new cFractalTinkerTowers());

	fractalList->append(new cFractalTransfSupershape());
	fractalList->append(new cFractalScatorPower2StdR());
	fractalList->append(new cFractalScatorPower2());
	fractalList->append(new cFractalScatorTest());
	fractalList->append(new cFractalTransfDemoScaleV2());
	fractalList->append(new cFractalTransfWizardDemo());




	// ---- 3x3lion V1-V500 formulas ----
	fractalList->append(new cFractalThreex3MonomialJulia());
	fractalList->append(new cFractalThreex3PolynomialJuliaDegree3());
	fractalList->append(new cFractalThreex3PolynomialJuliaDegree4());
	fractalList->append(new cFractalThreex3PolynomialJuliaDegree5());
	fractalList->append(new cFractalThreex3GeneralPolynomialJulia());
	fractalList->append(new cFractalThreex3RationalFunctionJulia());
	fractalList->append(new cFractalThreex3NewtonMethodFractal());
	fractalList->append(new cFractalThreex3HalleyMethodFractal());
	fractalList->append(new cFractalThreex3HouseholderMethodFractal());
	fractalList->append(new cFractalThreex3SecantMethodFractal());
	fractalList->append(new cFractalThreex3ChebyshevPolynomialJulia());
	fractalList->append(new cFractalThreex3LegendrePolynomialJulia());
	fractalList->append(new cFractalThreex3HermitePolynomialJulia());
	fractalList->append(new cFractalThreex3LaguerrePolynomialJulia());
	fractalList->append(new cFractalThreex3GegenbauerPolynomialJulia());
	fractalList->append(new cFractalThreex3JacobiPolynomialJulia());
	fractalList->append(new cFractalThreex3ZernikePolynomialJulia());
	fractalList->append(new cFractalThreex3BesselFunctionJuliaV18());
	fractalList->append(new cFractalThreex3HypergeometricFunctionJulia());
	fractalList->append(new cFractalThreex3ConfluentHypergeometricJulia());
	fractalList->append(new cFractalThreex3RiemannZetaJuliaV21());
	fractalList->append(new cFractalThreex3DirichletLFunctionJulia());
	fractalList->append(new cFractalThreex3DedekindEtaJulia());
	fractalList->append(new cFractalThreex3ModularJFunctionJulia());
	fractalList->append(new cFractalThreex3WeierstrassPFunctionJulia());
	fractalList->append(new cFractalThreex3ThetaFunctionJulia());
	fractalList->append(new cFractalThreex3EisensteinSeriesJulia());
	fractalList->append(new cFractalThreex3HeckeEigenformJulia());
	fractalList->append(new cFractalThreex3MaassFormJulia());
	fractalList->append(new cFractalThreex3AutomorphicFormJulia());
	fractalList->append(new cFractalThreex3GaloisRepresentationJulia());
	fractalList->append(new cFractalThreex3PAdicJulia());
	fractalList->append(new cFractalThreex3BerkovichJulia());
	fractalList->append(new cFractalThreex3ArithmeticDynamicsJulia());
	fractalList->append(new cFractalThreex3HeightsJulia());
	fractalList->append(new cFractalThreex3CanonicalHeightJulia());
	fractalList->append(new cFractalThreex3EquidistributionJulia());
	fractalList->append(new cFractalThreex3ComplexMultiplicationJulia());
	fractalList->append(new cFractalThreex3ShimuraVarietyJuliaV39());
	fractalList->append(new cFractalThreex3DrinfeldModuleJulia());
	fractalList->append(new cFractalThreex3AndersonTMotiveJulia());
	fractalList->append(new cFractalThreex3ShtukaJulia());
	fractalList->append(new cFractalThreex3LanglandsCorrespondenceJulia());
	fractalList->append(new cFractalThreex3GeometricLanglandsJulia());
	fractalList->append(new cFractalThreex3MotivicJuliaV45());
	fractalList->append(new cFractalThreex3MixedMotiveJuliaV46());
	fractalList->append(new cFractalThreex3PeriodJulia());
	fractalList->append(new cFractalThreex3HodgeStructureJulia());
	fractalList->append(new cFractalThreex3MixedHodgeStructureJulia());
	fractalList->append(new cFractalThreex3HodgeTateStructureJulia());
	fractalList->append(new cFractalThreex3ExponentialJulia());
	fractalList->append(new cFractalThreex3LogarithmicJulia());
	fractalList->append(new cFractalThreex3SineJulia());
	fractalList->append(new cFractalThreex3CosineJulia());
	fractalList->append(new cFractalThreex3TangentJulia());
	fractalList->append(new cFractalThreex3CotangentJulia());
	fractalList->append(new cFractalThreex3SecantJulia());
	fractalList->append(new cFractalThreex3CosecantJulia());
	fractalList->append(new cFractalThreex3HyperbolicSineJulia());
	fractalList->append(new cFractalThreex3HyperbolicCosineJulia());
	fractalList->append(new cFractalThreex3HyperbolicTangentJulia());
	fractalList->append(new cFractalThreex3InverseSineJulia());
	fractalList->append(new cFractalThreex3InverseCosineJulia());
	fractalList->append(new cFractalThreex3InverseTangentJulia());
	fractalList->append(new cFractalThreex3GudermannianJulia());
	fractalList->append(new cFractalThreex3InverseGudermannianJulia());
	fractalList->append(new cFractalThreex3LambertWJulia());
	fractalList->append(new cFractalThreex3GammaFunctionJulia());
	fractalList->append(new cFractalThreex3LogGammaJulia());
	fractalList->append(new cFractalThreex3DigammaJulia());
	fractalList->append(new cFractalThreex3PolygammaJulia());
	fractalList->append(new cFractalThreex3RiemannZetaJuliaV72());
	fractalList->append(new cFractalThreex3HurwitzZetaJulia());
	fractalList->append(new cFractalThreex3LerchTranscendentJulia());
	fractalList->append(new cFractalThreex3PolylogarithmJulia());
	fractalList->append(new cFractalThreex3DilogarithmJulia());
	fractalList->append(new cFractalThreex3TrilogarithmJulia());
	fractalList->append(new cFractalThreex3ClausenFunctionJulia());
	fractalList->append(new cFractalThreex3KummerFunctionJulia());
	fractalList->append(new cFractalThreex3WhittakerFunctionJulia());
	fractalList->append(new cFractalThreex3ParabolicCylinderJulia());
	fractalList->append(new cFractalThreex3AiryFunctionJulia());
	fractalList->append(new cFractalThreex3BesselFunctionJuliaV83());
	fractalList->append(new cFractalThreex3ModifiedBesselJulia());
	fractalList->append(new cFractalThreex3HankelFunctionJulia());
	fractalList->append(new cFractalThreex3StruveFunctionJulia());
	fractalList->append(new cFractalThreex3AngerWeberJulia());
	fractalList->append(new cFractalThreex3LommelFunctionJulia());
	fractalList->append(new cFractalThreex3KelvinFunctionJulia());
	fractalList->append(new cFractalThreex3ScorerFunctionJulia());
	fractalList->append(new cFractalThreex3ErrorFunctionJulia());
	fractalList->append(new cFractalThreex3FresnelIntegralJulia());
	fractalList->append(new cFractalThreex3ExponentialIntegralJulia());
	fractalList->append(new cFractalThreex3LogarithmicIntegralJulia());
	fractalList->append(new cFractalThreex3SineIntegralJulia());
	fractalList->append(new cFractalThreex3CosineIntegralJulia());
	fractalList->append(new cFractalThreex3HyperbolicSineIntegralJulia());
	fractalList->append(new cFractalThreex3HyperbolicCosineIntegralJulia());
	fractalList->append(new cFractalThreex3DawsonIntegralJulia());
	fractalList->append(new cFractalThreex3FaddeevaFunctionJulia());
	fractalList->append(new cFractalThreex3QuaternionJulia());
	fractalList->append(new cFractalThreex3OctonionJulia());
	fractalList->append(new cFractalThreex3SedenionJulia());
	fractalList->append(new cFractalThreex3TrigintaduonionJulia());
	fractalList->append(new cFractalThreex3ComplexifiedQuaternionJulia());
	fractalList->append(new cFractalThreex3BiquaternionJulia());
	fractalList->append(new cFractalThreex3DualQuaternionJulia());
	fractalList->append(new cFractalThreex3CliffordAlgebraJulia());
	fractalList->append(new cFractalThreex3GrassmannAlgebraJulia());
	fractalList->append(new cFractalThreex3GeometricAlgebraJulia());
	fractalList->append(new cFractalThreex3CayleyDicksonJulia());
	fractalList->append(new cFractalThreex3TwistorJulia());
	fractalList->append(new cFractalThreex3SpinorJulia());
	fractalList->append(new cFractalThreex3TensorJulia());
	fractalList->append(new cFractalThreex3MatrixJulia());
	fractalList->append(new cFractalThreex3OperatorJulia());
	fractalList->append(new cFractalThreex3FunctionalJulia());
	fractalList->append(new cFractalThreex3BanachSpaceJulia());
	fractalList->append(new cFractalThreex3HilbertSpaceJulia());
	fractalList->append(new cFractalThreex3FockSpaceJulia());
	fractalList->append(new cFractalThreex3LieAlgebraJulia());
	fractalList->append(new cFractalThreex3LieGroupJulia());
	fractalList->append(new cFractalThreex3SymmetricSpaceJulia());
	fractalList->append(new cFractalThreex3FlagVarietyJulia());
	fractalList->append(new cFractalThreex3GrassmannianJulia());
	fractalList->append(new cFractalThreex3StiefelManifoldJulia());
	fractalList->append(new cFractalThreex3SiegelUpperHalfSpaceJulia());
	fractalList->append(new cFractalThreex3TeichmllerSpaceJulia());
	fractalList->append(new cFractalThreex3ModuliSpaceJulia());
	fractalList->append(new cFractalThreex3DeligneMumfordJulia());
	fractalList->append(new cFractalThreex3StackJulia());
	fractalList->append(new cFractalThreex3DerivedJulia());
	fractalList->append(new cFractalThreex3InfinityCategoryJulia());
	fractalList->append(new cFractalThreex3SpectralJulia());
	fractalList->append(new cFractalThreex3MotivicJuliaV135());
	fractalList->append(new cFractalThreex3MixedMotiveJuliaV136());
	fractalList->append(new cFractalThreex3VoevodskyMotiveJulia());
	fractalList->append(new cFractalThreex3NoriMotiveJulia());
	fractalList->append(new cFractalThreex3PeriodDomainJulia());
	fractalList->append(new cFractalThreex3ShimuraVarietyJuliaV140());
	fractalList->append(new cFractalThreex3ArithmeticVarietyJulia());
	fractalList->append(new cFractalThreex3ArakelovVarietyJulia());
	fractalList->append(new cFractalThreex3BerkovichSpaceJulia());
	fractalList->append(new cFractalThreex3HuberSpaceJulia());
	fractalList->append(new cFractalThreex3PerfectoidSpaceJulia());
	fractalList->append(new cFractalThreex3DiamondJulia());
	fractalList->append(new cFractalThreex3CondensedJulia());
	fractalList->append(new cFractalThreex3PyknoticJulia());
	fractalList->append(new cFractalThreex3SolidJulia());
	fractalList->append(new cFractalThreex3LiquidJulia());
	fractalList->append(new cFractalThreex3KnotComplementJulia());
	fractalList->append(new cFractalThreex3LinkComplementJulia());
	fractalList->append(new cFractalThreex33ManifoldJulia());
	fractalList->append(new cFractalThreex3Hyperbolic3ManifoldJulia());
	fractalList->append(new cFractalThreex3SeifertFiberedJulia());
	fractalList->append(new cFractalThreex3GraphManifoldJulia());
	fractalList->append(new cFractalThreex3HakenManifoldJulia());
	fractalList->append(new cFractalThreex3AtoroidalJulia());
	fractalList->append(new cFractalThreex3AcylindricalJulia());
	fractalList->append(new cFractalThreex3ParedManifoldJulia());
	fractalList->append(new cFractalThreex3DehnFilledJulia());
	fractalList->append(new cFractalThreex3SurgeryJulia());
	fractalList->append(new cFractalThreex3SuturedManifoldJulia());
	fractalList->append(new cFractalThreex3TautFoliationJulia());
	fractalList->append(new cFractalThreex3ContactStructureJulia());
	fractalList->append(new cFractalThreex3TightContactJulia());
	fractalList->append(new cFractalThreex3OvertwistedContactJulia());
	fractalList->append(new cFractalThreex3SteinManifoldJulia());
	fractalList->append(new cFractalThreex3WeinsteinManifoldJulia());
	fractalList->append(new cFractalThreex3LiouvilleDomainJulia());
	fractalList->append(new cFractalThreex3ExactSymplecticJulia());
	fractalList->append(new cFractalThreex3HamiltonianJulia());
	fractalList->append(new cFractalThreex3ReebDynamicsJulia());
	fractalList->append(new cFractalThreex3MorseBottJulia());
	fractalList->append(new cFractalThreex3CerfTheoryJulia());
	fractalList->append(new cFractalThreex3HandlebodyJulia());
	fractalList->append(new cFractalThreex3CompressionBodyJulia());
	fractalList->append(new cFractalThreex3HeegaardSplittingJulia());
	fractalList->append(new cFractalThreex3HeegaardDiagramJulia());
	fractalList->append(new cFractalThreex3KirbyDiagramJulia());
	fractalList->append(new cFractalThreex3TrisectionJulia());
	fractalList->append(new cFractalThreex3BridgeSplittingJulia());
	fractalList->append(new cFractalThreex3ThinPositionJulia());
	fractalList->append(new cFractalThreex3WidthComplexJulia());
	fractalList->append(new cFractalThreex3GabaiDiskJulia());
	fractalList->append(new cFractalThreex3ScharlemannCycleJulia());
	fractalList->append(new cFractalThreex3WaveSurfaceJulia());
	fractalList->append(new cFractalThreex3HierarchyJulia());
	fractalList->append(new cFractalThreex3NormalSurfaceJulia());
	fractalList->append(new cFractalThreex3AlmostNormalJulia());
	fractalList->append(new cFractalThreex3SpunNormalJulia());
	fractalList->append(new cFractalThreex3QNormalJulia());
	fractalList->append(new cFractalThreex3AngleStructureJulia());
	fractalList->append(new cFractalThreex3GeometricStructureJulia());
	fractalList->append(new cFractalThreex3DevelopingMapJulia());
	fractalList->append(new cFractalThreex3HolonomyJulia());
	fractalList->append(new cFractalThreex3CharacterVarietyJulia());
	fractalList->append(new cFractalThreex3APolynomialJulia());
	fractalList->append(new cFractalThreex3VolumeConjectureJulia());
	fractalList->append(new cFractalThreex3ChernSimonsJulia());
	fractalList->append(new cFractalThreex3HenonMap());
	fractalList->append(new cFractalThreex3LoziMap());
	fractalList->append(new cFractalThreex3IkedaMap());
	fractalList->append(new cFractalThreex3Gingerbreadman());
	fractalList->append(new cFractalThreex3TinkerbellMap());
	fractalList->append(new cFractalThreex3BogdanovMap());
	fractalList->append(new cFractalThreex3HolmesCubic());
	fractalList->append(new cFractalThreex3UshikiMap());
	fractalList->append(new cFractalThreex3KaplanYorkeMap());
	fractalList->append(new cFractalThreex3ZaslavskiiMap());
	fractalList->append(new cFractalThreex3SinaiMap());
	fractalList->append(new cFractalThreex3ChirikovTaylorMap());
	fractalList->append(new cFractalThreex3FroeschleMap());
	fractalList->append(new cFractalThreex3FermiUlamModel());
	fractalList->append(new cFractalThreex3KeplerMap());
	fractalList->append(new cFractalThreex3StandardNontwistMap());
	fractalList->append(new cFractalThreex3WignerMap());
	fractalList->append(new cFractalThreex3HusimiMap());
	fractalList->append(new cFractalThreex3PoincareMap());
	fractalList->append(new cFractalThreex3SuspensionFlow());
	fractalList->append(new cFractalThreex3LorenzSystem());
	fractalList->append(new cFractalThreex3RosslerSystem());
	fractalList->append(new cFractalThreex3ChuaCircuit());
	fractalList->append(new cFractalThreex3DuffingOscillator());
	fractalList->append(new cFractalThreex3VanDerPolOscillator());
	fractalList->append(new cFractalThreex3FitzhughNagumo());
	fractalList->append(new cFractalThreex3HindmarshRose());
	fractalList->append(new cFractalThreex3MorrisLecar());
	fractalList->append(new cFractalThreex3HodgkinHuxley());
	fractalList->append(new cFractalThreex3KuramotoModel());
	fractalList->append(new cFractalThreex3KuramotoSivashinsky());
	fractalList->append(new cFractalThreex3SwiftHohenberg());
	fractalList->append(new cFractalThreex3ComplexGinzburgLandau());
	fractalList->append(new cFractalThreex3NonlinearSchrodinger());
	fractalList->append(new cFractalThreex3SineGordonEquation());
	fractalList->append(new cFractalThreex3KortewegDeVries());
	fractalList->append(new cFractalThreex3BoussinesqEquation());
	fractalList->append(new cFractalThreex3CamassaHolm());
	fractalList->append(new cFractalThreex3DegasperisProcesi());
	fractalList->append(new cFractalThreex3HunterSaxton());
	fractalList->append(new cFractalThreex3NavierStokes2d());
	fractalList->append(new cFractalThreex3Euler2d());
	fractalList->append(new cFractalThreex3PointVortex());
	fractalList->append(new cFractalThreex3VortexPatch());
	fractalList->append(new cFractalThreex3VortexSheet());
	fractalList->append(new cFractalThreex3BirkhoffRott());
	fractalList->append(new cFractalThreex3MooreSaffmanTanveer());
	fractalList->append(new cFractalThreex3KrasnyFilter());
	fractalList->append(new cFractalThreex3PullinMoore());
	fractalList->append(new cFractalThreex3CalogeroMoserSystem());
	fractalList->append(new cFractalThreex3RandomWalkFractal());
	fractalList->append(new cFractalThreex3SelfAvoidingWalk());
	fractalList->append(new cFractalThreex3LevyFlight());
	fractalList->append(new cFractalThreex3FractionalBrownianMotion());
	fractalList->append(new cFractalThreex3MultifractionalBrownianMotionV255());
	fractalList->append(new cFractalThreex3Subordinator());
	fractalList->append(new cFractalThreex3InverseSubordinator());
	fractalList->append(new cFractalThreex3ContinuousTimeRandomWalk());
	fractalList->append(new cFractalThreex3FractionalDiffusion());
	fractalList->append(new cFractalThreex3AnomalousDiffusion());
	fractalList->append(new cFractalThreex3PercolationCluster());
	fractalList->append(new cFractalThreex3DiffusionLimitedAggregation());
	fractalList->append(new cFractalThreex3LaplacianGrowth());
	fractalList->append(new cFractalThreex3DielectricBreakdown());
	fractalList->append(new cFractalThreex3EdenGrowth());
	fractalList->append(new cFractalThreex3RichardsonGrowth());
	fractalList->append(new cFractalThreex3WilliamsBjerknes());
	fractalList->append(new cFractalThreex3ContactProcess());
	fractalList->append(new cFractalThreex3VoterModel());
	fractalList->append(new cFractalThreex3IsingModel());
	fractalList->append(new cFractalThreex3PottsModel());
	fractalList->append(new cFractalThreex3XyModel());
	fractalList->append(new cFractalThreex3HeisenbergModel());
	fractalList->append(new cFractalThreex3ClockModel());
	fractalList->append(new cFractalThreex3AshkinTellerModel());
	fractalList->append(new cFractalThreex3BaxterModel());
	fractalList->append(new cFractalThreex3HardHexagon());
	fractalList->append(new cFractalThreex3HardSquare());
	fractalList->append(new cFractalThreex3Dimers());
	fractalList->append(new cFractalThreex3LoopModel());
	fractalList->append(new cFractalThreex3FullyPackedLoops());
	fractalList->append(new cFractalThreex3SixVertexModel());
	fractalList->append(new cFractalThreex3EightVertexModel());
	fractalList->append(new cFractalThreex3RsosModel());
	fractalList->append(new cFractalThreex3SosModel());
	fractalList->append(new cFractalThreex3BallisticDeposition());
	fractalList->append(new cFractalThreex3RandomDeposition());
	fractalList->append(new cFractalThreex3RestrictedSolidOnSolid());
	fractalList->append(new cFractalThreex3MolecularBeamEpitaxy());
	fractalList->append(new cFractalThreex3KardarParisiZhang());
	fractalList->append(new cFractalThreex3EdwardsWilkinson());
	fractalList->append(new cFractalThreex3MullinsEquation());
	fractalList->append(new cFractalThreex3WolfVillain());
	fractalList->append(new cFractalThreex3DasSarmaTamborenea());
	fractalList->append(new cFractalThreex3FamilyModel());
	fractalList->append(new cFractalThreex3TakayasuAggregation());
	fractalList->append(new cFractalThreex3InvasionPercolation());
	fractalList->append(new cFractalThreex3DirectedPercolation());
	fractalList->append(new cFractalThreex3BootstrapPercolation());
	fractalList->append(new cFractalThreex3KineticIsing());
	fractalList->append(new cFractalThreex3CollatzFractal());
	fractalList->append(new cFractalThreex33n1Generalized());
	fractalList->append(new cFractalThreex3SyracuseFunction());
	fractalList->append(new cFractalThreex3TotientFractal());
	fractalList->append(new cFractalThreex3CarmichaelFunctionFractal());
	fractalList->append(new cFractalThreex3MbiusFunctionFractal());
	fractalList->append(new cFractalThreex3LiouvilleFunctionFractal());
	fractalList->append(new cFractalThreex3DivisorFunctionFractal());
	fractalList->append(new cFractalThreex3RamanujanTauFractal());
	fractalList->append(new cFractalThreex3PartitionFunctionFractal());
	fractalList->append(new cFractalThreex3PrimeCountingFractal());
	fractalList->append(new cFractalThreex3ChebyshevFunctionFractal());
	fractalList->append(new cFractalThreex3MangoldtFunctionFractal());
	fractalList->append(new cFractalThreex3VonMangoldtFractal());
	fractalList->append(new cFractalThreex3DirichletCharacterFractal());
	fractalList->append(new cFractalThreex3LegendreSymbolFractal());
	fractalList->append(new cFractalThreex3JacobiSymbolFractal());
	fractalList->append(new cFractalThreex3KroneckerSymbolFractal());
	fractalList->append(new cFractalThreex3BernoulliNumberFractal());
	fractalList->append(new cFractalThreex3StirlingNumberFractal());
	fractalList->append(new cFractalThreex3BellNumberFractal());
	fractalList->append(new cFractalThreex3CatalanNumberFractal());
	fractalList->append(new cFractalThreex3FibonacciFractal());
	fractalList->append(new cFractalThreex3LucasFractal());
	fractalList->append(new cFractalThreex3PellFractal());
	fractalList->append(new cFractalThreex3PadovanFractal());
	fractalList->append(new cFractalThreex3PerrinFractal());
	fractalList->append(new cFractalThreex3TribonacciFractal());
	fractalList->append(new cFractalThreex3TetranacciFractal());
	fractalList->append(new cFractalThreex3NStepFibonacciFractal());
	fractalList->append(new cFractalThreex3PerfectNumberFractal());
	fractalList->append(new cFractalThreex3AmicablePairFractal());
	fractalList->append(new cFractalThreex3SociableChainFractal());
	fractalList->append(new cFractalThreex3AliquotSequenceFractal());
	fractalList->append(new cFractalThreex3AliquotTreeFractal());
	fractalList->append(new cFractalThreex3MersennePrimeFractal());
	fractalList->append(new cFractalThreex3FermatPrimeFractal());
	fractalList->append(new cFractalThreex3WieferichPrimeFractal());
	fractalList->append(new cFractalThreex3WilsonPrimeFractal());
	fractalList->append(new cFractalThreex3WolstenholmePrimeFractal());
	fractalList->append(new cFractalThreex3HarmonicNumberFractal());
	fractalList->append(new cFractalThreex3GregoryCoefficientFractal());
	fractalList->append(new cFractalThreex3BernoulliPolynomialFractal());
	fractalList->append(new cFractalThreex3EulerPolynomialFractal());
	fractalList->append(new cFractalThreex3GenocchiNumberFractal());
	fractalList->append(new cFractalThreex3EulerianNumberFractal());
	fractalList->append(new cFractalThreex3NarayanaNumberFractal());
	fractalList->append(new cFractalThreex3SchrderNumberFractal());
	fractalList->append(new cFractalThreex3DelannoyNumberFractal());
	fractalList->append(new cFractalThreex3MotzkinNumberFractal());
	fractalList->append(new cFractalThreex3CayleyGraphFractal());
	fractalList->append(new cFractalThreex3SchreierGraphFractal());
	fractalList->append(new cFractalThreex3GromovBoundaryFractal());
	fractalList->append(new cFractalThreex3PoissonBoundaryFractal());
	fractalList->append(new cFractalThreex3MartinBoundaryFractal());
	fractalList->append(new cFractalThreex3FurstenbergBoundaryFractal());
	fractalList->append(new cFractalThreex3SierpinskiGraphFractal());
	fractalList->append(new cFractalThreex3VicsekGraphFractal());
	fractalList->append(new cFractalThreex3TGraphFractal());
	fractalList->append(new cFractalThreex3HGraphFractal());
	fractalList->append(new cFractalThreex3HanoiGraphFractal());
	fractalList->append(new cFractalThreex3PascalGraphFractal());
	fractalList->append(new cFractalThreex3CellularAutomatonFractal());
	fractalList->append(new cFractalThreex3Rule90Fractal());
	fractalList->append(new cFractalThreex3Rule30Fractal());
	fractalList->append(new cFractalThreex3Rule110Fractal());
	fractalList->append(new cFractalThreex3ConwayGameOfLifeFractal());
	fractalList->append(new cFractalThreex3LangtonAntFractal());
	fractalList->append(new cFractalThreex3TurmiteFractal());
	fractalList->append(new cFractalThreex3PatersonWormsFractal());
	fractalList->append(new cFractalThreex3TurtleFractal());
	fractalList->append(new cFractalThreex3DragonCurveFractal());
	fractalList->append(new cFractalThreex3GosperCurveFractal());
	fractalList->append(new cFractalThreex3HilbertCurveFractal());
	fractalList->append(new cFractalThreex3PeanoCurveFractal());
	fractalList->append(new cFractalThreex3MooreCurveFractal());
	fractalList->append(new cFractalThreex3LebesgueCurveFractal());
	fractalList->append(new cFractalThreex3SierpinskiArrowheadFractal());
	fractalList->append(new cFractalThreex3LevyCCurveFractal());
	fractalList->append(new cFractalThreex3MinkowskiSausageFractal());
	fractalList->append(new cFractalThreex3CantorFunctionFractal());
	fractalList->append(new cFractalThreex3MinkowskiQuestionMarkFractal());
	fractalList->append(new cFractalThreex3ConwayBase13FunctionFractal());
	fractalList->append(new cFractalThreex3DirichletFunctionFractal());
	fractalList->append(new cFractalThreex3ThomaeFunctionFractal());
	fractalList->append(new cFractalThreex3WeierstrassFunctionFractal());
	fractalList->append(new cFractalThreex3TakagiFunctionFractal());
	fractalList->append(new cFractalThreex3BlancmangeCurveFractal());
	fractalList->append(new cFractalThreex3KiesswetterCurveFractal());
	fractalList->append(new cFractalThreex3RieszProductFractal());
	fractalList->append(new cFractalThreex3RademacherFunctionFractal());
	fractalList->append(new cFractalThreex3WalshFunctionFractal());
	fractalList->append(new cFractalThreex3HaarFunctionFractal());
	fractalList->append(new cFractalThreex3FaberSchauderFractal());
	fractalList->append(new cFractalThreex3BrownianBridgeFractal());
	fractalList->append(new cFractalThreex3OrnsteinUhlenbeckFractal());
	fractalList->append(new cFractalThreex3FractionalBrownianBridge());
	fractalList->append(new cFractalThreex3MultifractionalBrownianMotionV398());
	fractalList->append(new cFractalThreex3SubFractionalBrownianMotion());
	fractalList->append(new cFractalThreex3BiFractionalBrownianMotion());
	fractalList->append(new cFractalThreex3IsingModelFractal());
	fractalList->append(new cFractalThreex3PottsModelFractal());
	fractalList->append(new cFractalThreex3XyModelFractal());
	fractalList->append(new cFractalThreex3HeisenbergModelFractal());
	fractalList->append(new cFractalThreex3HubbardModelFractal());
	fractalList->append(new cFractalThreex3TJModelFractal());
	fractalList->append(new cFractalThreex3AndersonModelFractal());
	fractalList->append(new cFractalThreex3RandomMatrixFractal());
	fractalList->append(new cFractalThreex3QuantumHallFractal());
	fractalList->append(new cFractalThreex3HofstadterButterflyFractal());
	fractalList->append(new cFractalThreex3AubryAndreModelFractal());
	fractalList->append(new cFractalThreex3HarperModelFractal());
	fractalList->append(new cFractalThreex3FibonacciQuasicrystalFractal());
	fractalList->append(new cFractalThreex3PenroseTilingFractal());
	fractalList->append(new cFractalThreex3AmmannBeenkerTilingFractal());
	fractalList->append(new cFractalThreex3SocolarTilingFractal());
	fractalList->append(new cFractalThreex3DanzerTilingFractal());
	fractalList->append(new cFractalThreex3CutAndProjectFractal());
	fractalList->append(new cFractalThreex3ModelSetFractal());
	fractalList->append(new cFractalThreex3DeformedModelSetFractal());
	fractalList->append(new cFractalThreex3FourierQuasicrystalFractal());
	fractalList->append(new cFractalThreex3MeyerSetFractal());
	fractalList->append(new cFractalThreex3PisotVijayaraghavanFractal());
	fractalList->append(new cFractalThreex3SalemNumberFractal());
	fractalList->append(new cFractalThreex3PvNumberFractal());
	fractalList->append(new cFractalThreex3DiophantineApproximationFractal());
	fractalList->append(new cFractalThreex3MarkovSpectrumFractal());
	fractalList->append(new cFractalThreex3LagrangeSpectrumFractal());
	fractalList->append(new cFractalThreex3FreimanConstantFractal());
	fractalList->append(new cFractalThreex3HallRayFractal());
	fractalList->append(new cFractalThreex3BadlyApproximableFractal());
	fractalList->append(new cFractalThreex3WellApproximableFractal());
	fractalList->append(new cFractalThreex3KhinchinConstantFractal());
	fractalList->append(new cFractalThreex3LevyConstantFractal());
	fractalList->append(new cFractalThreex3LochsConstantFractal());
	fractalList->append(new cFractalThreex3PorterConstantFractal());
	fractalList->append(new cFractalThreex3GaussKuzminDistributionFractal());
	fractalList->append(new cFractalThreex3ArtinConstantFractal());
	fractalList->append(new cFractalThreex3TwinPrimeConstantFractal());
	fractalList->append(new cFractalThreex3BrunConstantFractal());
	fractalList->append(new cFractalThreex3MeisselMertensConstantFractal());
	fractalList->append(new cFractalThreex3LandauRamanujanConstantFractal());
	fractalList->append(new cFractalThreex3SierpinskiConstantFractal());
	fractalList->append(new cFractalThreex3SmarandacheFunctionFractal());
	fractalList->append(new cFractalThreex3KempnerSeriesFractal());
	fractalList->append(new cFractalThreex3ErdosBorweinConstantFractal());
	fractalList->append(new cFractalThreex3CopelandErdosConstantFractal());
	fractalList->append(new cFractalThreex3ChampernowneConstantFractal());
	fractalList->append(new cFractalThreex3LiouvilleConstantFractal());
	fractalList->append(new cFractalThreex3MahlerNumberFractal());
	fractalList->append(new cFractalThreex3LSystemTreeFractal());
	fractalList->append(new cFractalThreex3DlaTreeFractal());
	fractalList->append(new cFractalThreex3VascularNetworkFractal());
	fractalList->append(new cFractalThreex3BronchialTreeFractal());
	fractalList->append(new cFractalThreex3NeuralNetworkFractal());
	fractalList->append(new cFractalThreex3CorticalSurfaceFractal());
	fractalList->append(new cFractalThreex3RetinalVesselFractal());
	fractalList->append(new cFractalThreex3RootSystemFractal());
	fractalList->append(new cFractalThreex3LeafVenationFractal());
	fractalList->append(new cFractalThreex3CoralGrowthFractal());
	fractalList->append(new cFractalThreex3ShellPatternFractal());
	fractalList->append(new cFractalThreex3ButterflyWingFractal());
	fractalList->append(new cFractalThreex3PeacockFeatherFractal());
	fractalList->append(new cFractalThreex3FernFractal());
	fractalList->append(new cFractalThreex3RomanescoBroccoliFractal());
	fractalList->append(new cFractalThreex3LightningFractal());
	fractalList->append(new cFractalThreex3RiverNetworkFractal());
	fractalList->append(new cFractalThreex3CoastlineFractal());
	fractalList->append(new cFractalThreex3MountainRidgeFractal());
	fractalList->append(new cFractalThreex3CloudBoundaryFractal());
	fractalList->append(new cFractalThreex3GalaxyDistributionFractal());
	fractalList->append(new cFractalThreex3CosmicWebFractal());
	fractalList->append(new cFractalThreex3AccretionDiskFractal());
	fractalList->append(new cFractalThreex3SolarCoronaFractal());
	fractalList->append(new cFractalThreex3TurbulenceCascadeFractal());
	fractalList->append(new cFractalThreex3IntermittencyFractal());
	fractalList->append(new cFractalThreex3RainDropFractal());
	fractalList->append(new cFractalThreex3SnowCrystalFractal());
	fractalList->append(new cFractalThreex3FrostPatternFractal());
	fractalList->append(new cFractalThreex3CracksAndFracturesFractal());
	fractalList->append(new cFractalThreex3EarthquakeFaultFractal());
	fractalList->append(new cFractalThreex3PercolationInPorousMediaFractal());
	fractalList->append(new cFractalThreex3PolymerChainFractal());
	fractalList->append(new cFractalThreex3ProteinFoldingFractal());
	fractalList->append(new cFractalThreex3DnaStructureFractal());
	fractalList->append(new cFractalThreex3RnaFoldingFractal());
	fractalList->append(new cFractalThreex3MembraneStructureFractal());
	fractalList->append(new cFractalThreex3MitochondrialNetworkFractal());
	fractalList->append(new cFractalThreex3CellColonyFractal());
	fractalList->append(new cFractalThreex3TumorGrowthFractal());
	fractalList->append(new cFractalThreex3EpidemicSpreadFractal());
	fractalList->append(new cFractalThreex3ForestFireFractal());
	fractalList->append(new cFractalThreex3AntColonyFractal());
	fractalList->append(new cFractalThreex3SlimeMoldFractal());
	fractalList->append(new cFractalThreex3FungalMyceliumFractal());
	fractalList->append(new cFractalThreex3SpiderWebFractal());
	fractalList->append(new cFractalThreex3BirdFlockFractal());
	fractalList->append(new cFractalThreex3FishSchoolFractal());
	fractalList->append(new cFractalThreex3CrystalGrowthFractal());
	fractalList->append(new cFractalThreex3MineralDepositFractal());


	// ---- Mandalay Fold V1-V50 formulas ----
	fractalList->append(new cFractalMandalayFoldRicciFlow());
	fractalList->append(new cFractalMandalayFoldMeanCurvatureFlow());
	fractalList->append(new cFractalMandalayFoldInverseMcf());
	fractalList->append(new cFractalMandalayFoldWillmoreFlow());
	fractalList->append(new cFractalMandalayFoldGaussCurvatureFlow());
	fractalList->append(new cFractalMandalayFoldAffineSphere());
	fractalList->append(new cFractalMandalayFoldMongeAmpre());
	fractalList->append(new cFractalMandalayFoldComplexMongeAmpre());
	fractalList->append(new cFractalMandalayFoldHessianEquation());
	fractalList->append(new cFractalMandalayFoldCurvatureMeasure());
	fractalList->append(new cFractalMandalayFoldIntegralGeometry());
	fractalList->append(new cFractalMandalayFoldValuationTheory());
	fractalList->append(new cFractalMandalayFoldConvexIntegration());
	fractalList->append(new cFractalMandalayFoldHPrinciple());
	fractalList->append(new cFractalMandalayFoldMicroflexibility());
	fractalList->append(new cFractalMandalayFoldHolonomicApproximation());
	fractalList->append(new cFractalMandalayFoldWrinkle());
	fractalList->append(new cFractalMandalayFoldFoldSingularity());
	fractalList->append(new cFractalMandalayFoldCuspSingularity());
	fractalList->append(new cFractalMandalayFoldSwallowtail());
	fractalList->append(new cFractalMandalayFoldButterfly());
	fractalList->append(new cFractalMandalayFoldUmbilic());
	fractalList->append(new cFractalMandalayFoldRidge());
	fractalList->append(new cFractalMandalayFoldSymmetrySet());
	fractalList->append(new cFractalMandalayFoldMedialAxis());
	fractalList->append(new cFractalMandalayFoldLaguerreGeometry());
	fractalList->append(new cFractalMandalayFoldLieSphere());
	fractalList->append(new cFractalMandalayFoldDupinCyclide());
	fractalList->append(new cFractalMandalayFoldChannelSurface());
	fractalList->append(new cFractalMandalayFoldPipeSurface());
	fractalList->append(new cFractalMandalayFoldOffsetSurface());
	fractalList->append(new cFractalMandalayFoldMinkowskiSum());
	fractalList->append(new cFractalMandalayFoldMorphologicalDilation());
	fractalList->append(new cFractalMandalayFoldMorphologicalErosion());
	fractalList->append(new cFractalMandalayFoldDistanceTransform());
	fractalList->append(new cFractalMandalayFoldVoronoiDiagram());
	fractalList->append(new cFractalMandalayFoldDelaunayTriangulation());
	fractalList->append(new cFractalMandalayFoldPowerDiagram());
	fractalList->append(new cFractalMandalayFoldApolloniusDiagram());
	fractalList->append(new cFractalMandalayFoldAlphaShape());
	fractalList->append(new cFractalMandalayFoldPersistentHomology());
	fractalList->append(new cFractalMandalayFoldBettiNumber());
	fractalList->append(new cFractalMandalayFoldEulerCharacteristic());
	fractalList->append(new cFractalMandalayFoldGaussBonnet());
	fractalList->append(new cFractalMandalayFoldChernGaussBonnet());
	fractalList->append(new cFractalMandalayFoldAtiyahSingerIndex());
	fractalList->append(new cFractalMandalayFoldDiracOperator());
	fractalList->append(new cFractalMandalayFoldSpinGeometry());
	fractalList->append(new cFractalMandalayFoldTwistorTheory());
	fractalList->append(new cFractalMandalayFoldSelfDualYangMills());

	//====================== FRACTAL LIST - END ==================

	for (cAbstractFractal *fractal : newFractalList)
	{
		fractal->CheckForErrors();
	}
}
