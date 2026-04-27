// Light System - AUTO-GENERATED LOADING CODE

// Load 4 Light System
for (int i = 0; i < 4; i++)
{
	lights.enabled[i] = container->Get<bool>(enabled_" + QString::number(i) + ", fractalNumber);
	lights.intensity[i] = container->Get<double>(intensity_" + QString::number(i) + ", fractalNumber);
	lights.position[i] = container->Get<CVector3>(position_" + QString::number(i) + ", fractalNumber);
	lights.color[i] = container->Get<sRGB>(color_" + QString::number(i) + ", fractalNumber);
	lights.type[i] = container->Get<int>(type_" + QString::number(i) + ", fractalNumber);
}