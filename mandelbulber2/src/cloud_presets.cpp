#include "cloud_presets.hpp"

#include "parameters.hpp"

namespace cloudPresets
{

namespace
{
struct sValues
{
	double opacity;
	double density;
	double sharpness;
	double densityGamma;
	double softness;
	double ambientLight;
	bool sharpEdges;
	int noiseIterations;
};

sValues ValuesFor(ePreset preset)
{
	switch (preset)
	{
		case ePreset::SoftMist:
			return {1.2, 0.20, 8.0, 1.2, 0.60, 0.05, false, 4};
		case ePreset::VolumetricClouds:
			return {2.0, 0.30, 15.0, 1.0, 0.40, 0.0, false, 5};
		case ePreset::HardFractalSmoke:
			return {2.5, 0.45, 35.0, 0.8, 0.25, 0.0, true, 6};
		case ePreset::NebulaDust:
			return {1.5, 0.15, 6.0, 1.5, 0.70, 0.30, false, 7};
		default:
			return {2.0, 0.30, 15.0, 1.0, 0.40, 0.0, false, 5};
	}
}
} // namespace

const char *PresetName(const ePreset preset)
{
	switch (preset)
	{
		case ePreset::SoftMist: return "Soft Mist";
		case ePreset::VolumetricClouds: return "Volumetric Clouds";
		case ePreset::HardFractalSmoke: return "Hard Fractal Smoke";
		case ePreset::NebulaDust: return "Nebula Dust";
		default: return "Volumetric Clouds";
	}
}

void ApplyPreset(const std::shared_ptr<cParameterContainer> &par, const ePreset preset)
{
	if (!par) return;

	const sValues v = ValuesFor(preset);
	par->Set("clouds_opacity", v.opacity);
	par->Set("clouds_density", v.density);
	par->Set("clouds_sharpness", v.sharpness);
	par->Set("clouds_density_gamma", v.densityGamma);
	par->Set("clouds_softness", v.softness);
	par->Set("clouds_ambient_light", v.ambientLight);
	par->Set("clouds_sharp_edges", v.sharpEdges);
	par->Set("clouds_noise_iterations", v.noiseIterations);
	par->Set("clouds_adaptive_detail", true);
	par->Set("clouds_enable", true);
}

} // namespace cloudPresets
