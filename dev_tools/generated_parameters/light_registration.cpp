// Light System - AUTO-GENERATED
// Light source parameters

// Array of 4 Light System
for (int i = 0; i < 4; i++)
{
	par->addParam(enabled_" + QString::number(i) + ", false, morphNone, paramStandard);
	par->addParam(intensity_" + QString::number(i) + ", 1.0, 0.0, 100.0, morphLinear, paramStandard);
	par->addParam(position_" + QString::number(i) + ", CVector3(0.0, 3.0, -3.0), morphAkima, paramStandard);
	par->addParam(color_" + QString::number(i) + ", sRGB(255, 255, 255), morphLinear, paramStandard);
	par->addParam(type_" + QString::number(i) + ", 0, morphLinear, paramStandard, QStringList({"directional", "point", "spot"}));
}