#ifndef MANDELBULBER2_SRC_CLOUD_PRESETS_HPP_
#define MANDELBULBER2_SRC_CLOUD_PRESETS_HPP_

#include <memory>

class cParameterContainer;

namespace cloudPresets
{

enum class ePreset
{
	SoftMist = 0,
	VolumetricClouds = 1,
	HardFractalSmoke = 2,
	NebulaDust = 3
};

void ApplyPreset(const std::shared_ptr<cParameterContainer> &par, ePreset preset);
const char *PresetName(ePreset preset);

} // namespace cloudPresets

#endif
