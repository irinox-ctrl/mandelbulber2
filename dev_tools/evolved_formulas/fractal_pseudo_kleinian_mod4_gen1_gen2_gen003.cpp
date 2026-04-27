/**
 * Mandelbulber v2, a 3D fractal generator
 *
 * AUTO-EVOLVED FORMULA
 * Base: fractal_pseudo_kleinian_mod4
 * Generation: 3
 * Parent: pseudo_kleinian_mod4_gen1_gen002
 * Mutations: offset_transformCommon.offset000, offset_transformCommon.additionConstantP000
 */

#include "all_fractal_definitions.h"

class cFractalPseudoKleinianMod4Gen1Gen2Gen003 : public cAbstractFractal
{
public:
	cFractalPseudoKleinianMod4Gen1Gen2Gen003();
	void FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux) override;
};

cFractalPseudoKleinianMod4Gen1Gen2Gen003::cFractalPseudoKleinianMod4Gen1Gen2Gen003() : cAbstractFractal()
{
	nameInComboBox = "Evolved fractal_pseudo_kleinian_mod4 Gen3";
	internalName = "pseudo_kleinian_mod4_gen1_gen2_gen003";
	internalID = fractal::pseudo_kleinian_mod4_gen1_gen2_gen003;
	DEType = analyticDEType;
	DEFunctionType = pseudoKleinianDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionPseudoKleinian;
	coloringFunction = coloringFunctionDefault;
}

void cFractalPseudoKleinianMod4Gen1Gen2Gen003::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// sphere inversion
		if (fractal->transformCommon.sphereInversionEnabledFalse
				&& aux.i >= fractal->transformCommon.startIterationsX
				&& aux.i < fractal->transformCommon.stopIterations1)
		{
			z += fractal->transformCommon.offset000;
			double rr = z.Dot(z);
			z *= fractal->transformCommon.scaleG1 / rr;
			aux.DE *= (fractal->transformCommon.scaleG1 / rr);
			z += fractal->transformCommon.additionConstantP000 - fractal->transformCommon.offset000;
			z *= fractal->transformCommon.scaleA1;
			aux.DE *= fractal->transformCommon.scaleA1;
		}


	// box offset
		if (aux.i >= fractal->transformCommon.startIterationsM
				&& aux.i < fractal->transformCommon.stopIterationsM)
		{
			z.x -= fractal->transformCommon.constantMultiplier000.x * sign(z.x);
			z.y -= fractal->transformCommon.constantMultiplier000.y * sign(z.y);
			z.z -= fractal->transformCommon.constantMultiplier000.z * sign(z.z);
		}


	// Pseudo kleinian
		double k = 0.0;
		z = fabs(z + fractal->transformCommon.additionConstant0777)
				- fabs(z - fractal->transformCommon.additionConstant0777) - z;

		k = max(fractal->transformCommon.minR05 / z.Dot(z), 1.0);
		z *= k;
		aux.DE *= k + fractal->analyticDE.tweak005;
		aux.pseudoKleinianDE = fractal->analyticDE.scale1; 
	// pK DE

		z += fractal->transformCommon.additionConstant000;

		if (fractal->transformCommon.functionEnabledGFalse
				&& aux.i >= fractal->transformCommon.startIterationsG
				&& aux.i < fractal->transformCommon.stopIterationsG)
		{
			z.x += aux.pos_neg * fractal->transformCommon.additionConstantA000.x;
			z.y += aux.pos_neg * fractal->transformCommon.additionConstantA000.y;
			z.z += aux.pos_neg * fractal->transformCommon.additionConstantA000.z;
			aux.pos_neg *= fractal->transformCommon.scaleNeg1;
		}

		if (fractal->transformCommon.functionEnabledFFalse
				&& aux.i >= fractal->transformCommon.startIterationsF
				&& aux.i < fractal->transformCommon.stopIterationsF)
		{
			z = fabs(z + fractal->transformCommon.offsetA000)
					- fabs(z - fractal->transformCommon.offsetA000) - z;
		}

		if (fractal->transformCommon.functionEnabledNFalse
				&& aux.i >= fractal->transformCommon.startIterationsN
				&& aux.i < fractal->transformCommon.stopIterationsN)
		{

	// double foldX = fractal->transformCommon.offset1;

	// double foldY = fractal->transformCommon.offsetA1;

			double t;
			z.x = fabs(z.x);
			z.y = fabs(z.y);
			if (fractal->transformCommon.functionEnabledAFalse)
			{
				t = z.x;
				z.x = z.y;
				z.y = t;
			}
			t = z.x;
			z.x = z.x + z.y - fractal->transformCommon.offset0;
			z.y = t - z.y - fractal->transformCommon.offsetA0;
			if (fractal->transformCommon.functionEnabledBxFalse
					&& aux.i >= fractal->transformCommon.startIterationsO
					&& aux.i < fractal->transformCommon.stopIterationsO)
						z.x = -fabs(z.x);
			if (fractal->transformCommon.functionEnabledBx
					&& aux.i >= fractal->transformCommon.startIterationsP
					&& aux.i < fractal->transformCommon.stopIterationsP)
						z.y = -fabs(z.y);

			t = z.x;
			z.x = z.x + z.y;
			z.y = t - z.y;
			z.x *= 0.5;
			z.y *= 0.5;
			if (fractal->transformCommon.functionEnabledAx
					&& aux.i >= fractal->transformCommon.startIterationsR
					&& aux.i < fractal->transformCommon.stopIterationsR)
						z.x = fractal->transformCommon.offset1 - fabs(z.x + fractal->transformCommon.offset1);
			if (fractal->transformCommon.functionEnabledAxFalse
					&& aux.i >= fractal->transformCommon.startIterationsRV
					&& aux.i < fractal->transformCommon.stopIterationsRV)
						z.y = fractal->transformCommon.offsetA1 - fabs(z.y + fractal->transformCommon.offsetA1);
		}

		if (fractal->transformCommon.functionEnabledxFalse) z.x = -z.x;
		if (fractal->transformCommon.functionEnabledyFalse) z.y = -z.y;
		if (fractal->transformCommon.functionEnabledzFalse) z.z = -z.z;


	// color
		if (fractal->foldColor.auxColorEnabledFalse)
		{
			colorAdd += fractal->foldColor.difs0000.x * fabs(z.x);
			colorAdd += fractal->foldColor.difs0000.y * fabs(z.y);
			colorAdd += fractal->foldColor.difs0000.z * fabs(z.z);
			colorAdd += fractal->foldColor.difs0000.w * k;

			aux.color += colorAdd;
		}

}
