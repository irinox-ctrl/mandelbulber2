#ifndef MANDELBULBER2_SRC_PARAMETER_RENDER_FINGERPRINT_HPP_
#define MANDELBULBER2_SRC_PARAMETER_RENDER_FINGERPRINT_HPP_

#include <QByteArray>

class cParameterContainer;
class cFractalContainer;

/** Lightweight render-state fingerprint (avoids full settings text serialization). */
QByteArray ComputeRenderParameterFingerprint(const cParameterContainer *params,
	const cFractalContainer *fractalParams);

#endif /* MANDELBULBER2_SRC_PARAMETER_RENDER_FINGERPRINT_HPP_ */
