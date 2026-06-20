#include "parameter_render_fingerprint.hpp"

#include <QCryptographicHash>

#include "algebra.hpp"
#include "fractal_container.hpp"
#include "fractal_enums.h"
#include "parameters.hpp"

namespace
{
void AddDouble(QCryptographicHash &hash, const cParameterContainer *params, const char *key)
{
	hash.addData(QByteArray::number(params->Get<double>(key)));
}

void AddInt(QCryptographicHash &hash, const cParameterContainer *params, const char *key)
{
	hash.addData(QByteArray::number(params->Get<int>(key)));
}

void AddBool(QCryptographicHash &hash, const cParameterContainer *params, const char *key)
{
	hash.addData(QByteArray::number(params->Get<bool>(key) ? 1 : 0));
}

void AddVector3(QCryptographicHash &hash, const cParameterContainer *params, const char *key)
{
	const CVector3 v = params->Get<CVector3>(key);
	hash.addData(QByteArray(reinterpret_cast<const char *>(&v), int(sizeof(CVector3))));
}

void AddString(QCryptographicHash &hash, const cParameterContainer *params, const char *key)
{
	hash.addData(params->Get<QString>(key).toUtf8());
}
} // namespace

QByteArray ComputeRenderParameterFingerprint(const cParameterContainer *params,
	const cFractalContainer *fractalParams)
{
	if (!params || !fractalParams) return QByteArray();

	QCryptographicHash hash(QCryptographicHash::Md5);

	AddVector3(hash, params, "camera");
	AddVector3(hash, params, "target");
	AddVector3(hash, params, "top_vector");
	AddDouble(hash, params, "camera_distance_to_target");
	AddDouble(hash, params, "fov");
	AddDouble(hash, params, "rotation");
	AddDouble(hash, params, "detail_level");
	AddInt(hash, params, "N");
	AddInt(hash, params, "image_width");
	AddInt(hash, params, "image_height");
	AddDouble(hash, params, "image_preview_scale");
	AddInt(hash, params, "main_material_id");
	AddBool(hash, params, "julia_mode");
	AddVector3(hash, params, "julia_c");
	AddBool(hash, params, "opencl_enabled");
	AddInt(hash, params, "opencl_mode");
	AddBool(hash, params, "nebula_mode");
	AddInt(hash, params, "ambient_occlusion_mode");
	AddBool(hash, params, "ambient_occlusion_enabled");
	AddBool(hash, params, "DOF_monte_carlo");
	AddBool(hash, params, "antialiasing_enabled");
	AddBool(hash, params, "raytraced_reflections");
	AddBool(hash, params, "volumetric_fog_enabled");
	AddInt(hash, params, "volumetric_fog_mode");
	AddBool(hash, params, "volumetric_blue_noise_jitter");

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		const std::shared_ptr<cParameterContainer> slot = fractalParams->at(i);
		if (!slot) continue;
		AddString(hash, slot.get(), "formula");
		AddInt(hash, slot.get(), "formula_enabled");
		AddInt(hash, slot.get(), "iterations");
		AddDouble(hash, slot.get(), "power");
	}

	return hash.result();
}
