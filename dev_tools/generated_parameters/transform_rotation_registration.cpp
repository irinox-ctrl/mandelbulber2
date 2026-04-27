// Advanced Rotation Transform - AUTO-GENERATED
// Advanced rotation with multiple axes

	par->addParam("enabled", false, morphLinear, paramStandard);
	par->addParam("rotation", CVector3(0.0, 0.0, 0.0), -360.0, 360.0, morphAkimaAngle, paramStandard);
	par->addParam("center", CVector3(0.0, 0.0, 0.0), -10.0, 10.0, morphAkima, paramStandard);
	par->addParam("start_iteration", 0, 0, 250, morphLinear, paramStandard);
	par->addParam("stop_iteration", 250, 0, 250, morphLinear, paramStandard);