/**
 * 3x3lion — Smart Camera System
 * Founded by Iri and Devin
 */

#include "smart_camera.h"

#include "src/camera_target.hpp"
#include "src/fractal_container.hpp"
#include "src/interface.hpp"
#include "src/parameters.hpp"
#include "src/write_log.hpp"

#include <QJsonDocument>
#include <cmath>

namespace
{
constexpr int kSmoothIntervalMs = 16;  // ~60 fps
constexpr int kOrbitIntervalMs = 33;   // ~30 fps
constexpr int kSurfaceFollowMs = 33;
constexpr int kRecordIntervalMs = 100; // 10 fps recording
constexpr int kPlaybackIntervalMs = 33;
constexpr double kCollisionMarginFactor = 2.0;

CVector3 Lerp(const CVector3 &a, const CVector3 &b, double t)
{
	return a + (b - a) * t;
}

double SmoothStep(double t)
{
	t = qBound(0.0, t, 1.0);
	return t * t * (3.0 - 2.0 * t);
}
} // namespace

cSmartCamera::cSmartCamera(QObject *parent) : QObject(parent)
{
	smoothTimer = new QTimer(this);
	smoothTimer->setInterval(kSmoothIntervalMs);
	connect(smoothTimer, &QTimer::timeout, this, &cSmartCamera::slotSmoothTick);

	orbitTimer = new QTimer(this);
	orbitTimer->setInterval(kOrbitIntervalMs);
	connect(orbitTimer, &QTimer::timeout, this, &cSmartCamera::slotOrbitTick);

	surfaceFollowTimer = new QTimer(this);
	surfaceFollowTimer->setInterval(kSurfaceFollowMs);
	connect(surfaceFollowTimer, &QTimer::timeout, this, &cSmartCamera::slotSurfaceFollowTick);

	recordTimer = new QTimer(this);
	recordTimer->setInterval(kRecordIntervalMs);
	connect(recordTimer, &QTimer::timeout, this, &cSmartCamera::slotRecordTick);

	playbackTimer = new QTimer(this);
	playbackTimer->setInterval(kPlaybackIntervalMs);
	connect(playbackTimer, &QTimer::timeout, this, &cSmartCamera::slotPlaybackTick);

	fpsTimer.start();
}

cSmartCamera::~cSmartCamera() = default;

void cSmartCamera::AssignParameters(std::shared_ptr<cParameterContainer> _params,
	std::shared_ptr<cFractalContainer> _fractalParams)
{
	par = _params;
	parFractal = _fractalParams;
}

// --- Helpers ---

double cSmartCamera::GetDE(CVector3 point)
{
	if (!par || !parFractal) return 1.0;
	return cInterface::GetDistanceForPoint(point, par, parFractal);
}

CVector3 cSmartCamera::GetSurfaceNormal(CVector3 point, double de)
{
	double eps = de * 0.01;
	if (eps < 1e-15) eps = 1e-10;
	double dx = GetDE(point + CVector3(eps, 0, 0)) - GetDE(point - CVector3(eps, 0, 0));
	double dy = GetDE(point + CVector3(0, eps, 0)) - GetDE(point - CVector3(0, eps, 0));
	double dz = GetDE(point + CVector3(0, 0, eps)) - GetDE(point - CVector3(0, 0, eps));
	CVector3 n(dx, dy, dz);
	double len = n.Length();
	if (len > 1e-15) n = n / len;
	return n;
}

void cSmartCamera::WriteCameraToParams(CVector3 cam, CVector3 tgt, CVector3 top)
{
	if (!par) return;
	par->Set("camera", cam);
	par->Set("target", tgt);
	par->Set("camera_top", top);
	cCameraTarget ct(cam, tgt, top);
	par->Set("camera_rotation", ct.GetRotation() * (180.0 / M_PI));
	par->Set("camera_distance_to_target", ct.GetDistance());
}

void cSmartCamera::ReadCameraFromParams(CVector3 &cam, CVector3 &tgt, CVector3 &top)
{
	if (!par) return;
	cam = par->Get<CVector3>("camera");
	tgt = par->Get<CVector3>("target");
	top = par->Get<CVector3>("camera_top");
}

// ============================================================
// Smooth Camera Interpolation
// ============================================================

void cSmartCamera::SmoothMoveTo(CVector3 targetCamera, CVector3 targetTarget, double duration)
{
	ReadCameraFromParams(smoothStartCam, smoothStartTgt, smoothStartTop);
	smoothEndCam = targetCamera;
	smoothEndTgt = targetTarget;
	smoothDuration = qMax(0.1, duration);
	smoothProgress = 0.0;
	smoothAnimating = true;
	smoothElapsed.start();
	smoothTimer->start();
}

void cSmartCamera::StopAnimation()
{
	smoothAnimating = false;
	smoothTimer->stop();
}

void cSmartCamera::slotSmoothTick()
{
	if (!smoothAnimating || !par) { smoothTimer->stop(); return; }

	double elapsed = smoothElapsed.elapsed() / 1000.0;
	smoothProgress = qMin(1.0, elapsed / smoothDuration);
	double t = SmoothStep(smoothProgress);

	CVector3 cam = Lerp(smoothStartCam, smoothEndCam, t);
	CVector3 tgt = Lerp(smoothStartTgt, smoothEndTgt, t);

	if (collisionAvoidance)
		cam = ApplyCollisionAvoidance(smoothStartCam, cam);

	WriteCameraToParams(cam, tgt, smoothStartTop);
	emit signalCameraUpdated();

	if (smoothProgress >= 1.0)
	{
		smoothAnimating = false;
		smoothTimer->stop();
		emit signalRender();
	}
}

// ============================================================
// DE-Based Collision Avoidance
// ============================================================

CVector3 cSmartCamera::ApplyCollisionAvoidance(CVector3 currentPos, CVector3 desiredPos)
{
	if (!collisionAvoidance || !par || !parFractal) return desiredPos;

	double de = GetDE(desiredPos);
	double safeThreshold = minSafeDistance * kCollisionMarginFactor;

	if (de > safeThreshold)
		return desiredPos;

	CVector3 normal = GetSurfaceNormal(desiredPos, de);
	double pushBack = safeThreshold - de;
	CVector3 corrected = desiredPos + normal * pushBack;

	double deCheck = GetDE(corrected);
	if (deCheck < minSafeDistance)
	{
		emit signalCollisionWarning(deCheck);
		return currentPos;
	}

	emit signalCollisionWarning(de);
	return corrected;
}

// ============================================================
// Adaptive Step Size
// ============================================================

double cSmartCamera::ComputeAdaptiveStepSize(CVector3 position, double baseStep)
{
	if (!adaptiveStep || !par || !parFractal) return baseStep;

	double de = GetDE(position);
	double adaptiveFactor = qBound(0.01, de * 0.5, 10.0);
	return baseStep * adaptiveFactor;
}

// ============================================================
// Orbit Mode
// ============================================================

void cSmartCamera::StartOrbit(CVector3 center, double radius, double speed)
{
	orbitCenter = center;
	orbitRadius = qMax(0.001, radius);
	orbitSpeed = speed;
	orbitAngle = 0.0;

	CVector3 cam, tgt, top;
	ReadCameraFromParams(cam, tgt, top);
	orbitPitch = asin(qBound(-0.99, (cam.z - center.z) / orbitRadius, 0.99));

	orbitActive = true;
	orbitTimer->start();
}

void cSmartCamera::StopOrbit()
{
	orbitActive = false;
	orbitTimer->stop();
}

void cSmartCamera::slotOrbitTick()
{
	if (!orbitActive || !par) { orbitTimer->stop(); return; }

	orbitAngle += orbitSpeed * 0.03;
	if (orbitAngle > 2.0 * M_PI) orbitAngle -= 2.0 * M_PI;

	double cosPitch = cos(orbitPitch);
	CVector3 cam;
	cam.x = orbitCenter.x + orbitRadius * cos(orbitAngle) * cosPitch;
	cam.y = orbitCenter.y + orbitRadius * sin(orbitAngle) * cosPitch;
	cam.z = orbitCenter.z + orbitRadius * sin(orbitPitch);

	if (collisionAvoidance)
	{
		CVector3 current;
		CVector3 dummy1, dummy2;
		ReadCameraFromParams(current, dummy1, dummy2);
		cam = ApplyCollisionAvoidance(current, cam);
	}

	CVector3 top(0, 0, 1);
	WriteCameraToParams(cam, orbitCenter, top);
	UpdateHUD();
	emit signalCameraUpdated();
}

// ============================================================
// Surface Following
// ============================================================

void cSmartCamera::StartSurfaceFollow(double targetDistance, double speed)
{
	surfaceFollowTargetDist = qMax(1e-10, targetDistance);
	surfaceFollowSpeed = speed;
	surfaceFollowActive = true;

	CVector3 cam, tgt, top;
	ReadCameraFromParams(cam, tgt, top);
	cCameraTarget ct(cam, tgt, top);
	surfaceFollowDirection = ct.GetForwardVector();

	surfaceFollowTimer->start();
}

void cSmartCamera::StopSurfaceFollow()
{
	surfaceFollowActive = false;
	surfaceFollowTimer->stop();
}

void cSmartCamera::slotSurfaceFollowTick()
{
	if (!surfaceFollowActive || !par || !parFractal)
	{
		surfaceFollowTimer->stop();
		return;
	}

	CVector3 cam, tgt, top;
	ReadCameraFromParams(cam, tgt, top);

	double de = GetDE(cam);
	double stepSize = de * 0.3 * surfaceFollowSpeed;
	if (stepSize < 1e-15) stepSize = 1e-10;

	CVector3 newCam = cam + surfaceFollowDirection * stepSize;
	double newDE = GetDE(newCam);

	CVector3 normal = GetSurfaceNormal(newCam, newDE);
	double correction = (surfaceFollowTargetDist - newDE) * 0.5;
	newCam = newCam + normal * correction;

	CVector3 rightVec = surfaceFollowDirection.Cross(CVector3(0, 0, 1));
	double rightLen = rightVec.Length();
	if (rightLen > 1e-10) rightVec = rightVec / rightLen;
	CVector3 newUp = rightVec.Cross(surfaceFollowDirection);
	double upLen = newUp.Length();
	if (upLen > 1e-10) newUp = newUp / upLen;
	else newUp = CVector3(0, 0, 1);

	surfaceFollowDirection = (newCam + surfaceFollowDirection * de - cam);
	double dirLen = surfaceFollowDirection.Length();
	if (dirLen > 1e-15) surfaceFollowDirection = surfaceFollowDirection / dirLen;

	CVector3 newTgt = newCam + surfaceFollowDirection * (newDE * 2.0);

	WriteCameraToParams(newCam, newTgt, newUp);
	UpdateHUD();
	emit signalCameraUpdated();
}

// ============================================================
// Flight Path Recorder
// ============================================================

void cSmartCamera::StartRecording()
{
	recording = true;
	recordElapsed.start();
	recordTimer->start();
}

void cSmartCamera::StopRecording()
{
	recording = false;
	recordTimer->stop();
	emit signalFlightPathRecorded(flightPath.size());
}

void cSmartCamera::slotRecordTick()
{
	if (!recording || !par) return;

	sFlightFrame frame;
	ReadCameraFromParams(frame.camera, frame.target, frame.top);
	frame.timestamp = recordElapsed.elapsed() / 1000.0;
	flightPath.append(frame);
}

void cSmartCamera::StartPlayback(double speed)
{
	if (flightPath.isEmpty()) return;
	playbackFrame = 0;
	playbackSpeed = qMax(0.1, speed);
	playing = true;
	playbackTimer->start();
}

void cSmartCamera::StopPlayback()
{
	playing = false;
	playbackTimer->stop();
}

void cSmartCamera::slotPlaybackTick()
{
	if (!playing || !par || flightPath.isEmpty())
	{
		playing = false;
		playbackTimer->stop();
		emit signalPlaybackFinished();
		return;
	}

	int idx = qMin(playbackFrame, flightPath.size() - 1);
	const sFlightFrame &f = flightPath[idx];
	WriteCameraToParams(f.camera, f.target, f.top);
	emit signalCameraUpdated();

	playbackFrame += static_cast<int>(playbackSpeed);
	if (playbackFrame >= flightPath.size())
	{
		playing = false;
		playbackTimer->stop();
		emit signalPlaybackFinished();
		emit signalRender();
	}
}

void cSmartCamera::ClearFlightPath()
{
	flightPath.clear();
}

QJsonArray cSmartCamera::FlightPathToJson() const
{
	QJsonArray arr;
	for (const sFlightFrame &f : flightPath)
	{
		QJsonObject obj;
		obj["cx"] = f.camera.x; obj["cy"] = f.camera.y; obj["cz"] = f.camera.z;
		obj["tx"] = f.target.x; obj["ty"] = f.target.y; obj["tz"] = f.target.z;
		obj["ux"] = f.top.x;    obj["uy"] = f.top.y;    obj["uz"] = f.top.z;
		obj["t"] = f.timestamp;
		arr.append(obj);
	}
	return arr;
}

void cSmartCamera::FlightPathFromJson(const QJsonArray &arr)
{
	flightPath.clear();
	for (const QJsonValue &v : arr)
	{
		QJsonObject o = v.toObject();
		sFlightFrame f;
		f.camera = CVector3(o["cx"].toDouble(), o["cy"].toDouble(), o["cz"].toDouble());
		f.target = CVector3(o["tx"].toDouble(), o["ty"].toDouble(), o["tz"].toDouble());
		f.top = CVector3(o["ux"].toDouble(), o["uy"].toDouble(), o["uz"].toDouble());
		f.timestamp = o["t"].toDouble();
		flightPath.append(f);
	}
}

// ============================================================
// HUD Data
// ============================================================

cSmartCamera::sHUDData cSmartCamera::GetHUDData()
{
	UpdateHUD();
	return lastHUDData;
}

void cSmartCamera::UpdateHUD()
{
	if (!par || !parFractal) return;

	CVector3 cam, tgt, top;
	ReadCameraFromParams(cam, tgt, top);

	lastHUDData.camera = cam;
	lastHUDData.target = tgt;
	lastHUDData.distanceToSurface = GetDE(cam);

	cCameraTarget ct(cam, tgt, top);
	lastHUDData.rotation = ct.GetRotation() * (180.0 / M_PI);
	lastHUDData.cameraDistance = ct.GetDistance();

	lastHUDData.collisionWarning = (lastHUDData.distanceToSurface < minSafeDistance * 3.0);
	lastHUDData.isAnimating = smoothAnimating;
	lastHUDData.isRecording = recording;
	lastHUDData.isPlaying = playing;
	lastHUDData.isOrbiting = orbitActive;
	lastHUDData.isSurfaceFollowing = surfaceFollowActive;

	frameCount++;
	double elapsed = fpsTimer.elapsed() / 1000.0;
	if (elapsed > 0.5)
	{
		lastHUDData.fps = frameCount / elapsed;
		frameCount = 0;
		fpsTimer.restart();
	}

	if (orbitActive) lastHUDData.modeName = "ORBIT";
	else if (surfaceFollowActive) lastHUDData.modeName = "SURFACE FOLLOW";
	else if (playing) lastHUDData.modeName = "PLAYBACK";
	else if (smoothAnimating) lastHUDData.modeName = "SMOOTH MOVE";
	else lastHUDData.modeName = "FREE";

	emit signalHUDDataChanged(lastHUDData);
}
