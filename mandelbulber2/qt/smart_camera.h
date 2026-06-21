/**
 * 3x3lion — Smart Camera System
 * Founded by Iri and Devin
 *
 * Advanced camera features: smooth interpolation, DE collision avoidance,
 * adaptive step, orbit mode, surface following, flight path recording.
 * Designed as infrastructure for autonomous drone navigation.
 */

#ifndef MANDELBULBER2_QT_SMART_CAMERA_H_
#define MANDELBULBER2_QT_SMART_CAMERA_H_

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

#include "src/algebra.hpp"

class cParameterContainer;
class cFractalContainer;

class cSmartCamera : public QObject
{
	Q_OBJECT

public:
	explicit cSmartCamera(QObject *parent = nullptr);
	~cSmartCamera() override;

	void AssignParameters(std::shared_ptr<cParameterContainer> _params,
		std::shared_ptr<cFractalContainer> _fractalParams);

	// --- Smooth Interpolation ---
	void SmoothMoveTo(CVector3 targetCamera, CVector3 targetTarget, double duration = 1.0);
	void SetSmoothness(double s) { smoothness = qBound(0.01, s, 0.99); }
	double GetSmoothness() const { return smoothness; }
	bool IsAnimating() const { return smoothAnimating; }
	void StopAnimation();

	// --- DE Collision Avoidance ---
	void SetCollisionAvoidance(bool enable) { collisionAvoidance = enable; }
	bool GetCollisionAvoidance() const { return collisionAvoidance; }
	void SetMinSafeDistance(double d) { minSafeDistance = qMax(1e-15, d); }
	double GetMinSafeDistance() const { return minSafeDistance; }
	CVector3 ApplyCollisionAvoidance(CVector3 currentPos, CVector3 desiredPos);

	// --- Adaptive Step ---
	void SetAdaptiveStep(bool enable) { adaptiveStep = enable; }
	bool GetAdaptiveStep() const { return adaptiveStep; }
	double ComputeAdaptiveStepSize(CVector3 position, double baseStep);

	// --- Orbit Mode ---
	void StartOrbit(CVector3 center, double radius, double speed = 1.0);
	void StopOrbit();
	bool IsOrbiting() const { return orbitActive; }

	// --- Surface Following ---
	void StartSurfaceFollow(double targetDistance = 0.1, double speed = 1.0);
	void StopSurfaceFollow();
	bool IsSurfaceFollowing() const { return surfaceFollowActive; }
	void SetSurfaceFollowDistance(double d) { surfaceFollowTargetDist = d; }

	// --- Flight Path Recorder ---
	void StartRecording();
	void StopRecording();
	bool IsRecording() const { return recording; }
	void StartPlayback(double speed = 1.0);
	void StopPlayback();
	bool IsPlaying() const { return playing; }
	void ClearFlightPath();
	int GetFlightPathLength() const { return flightPath.size(); }
	QJsonArray FlightPathToJson() const;
	void FlightPathFromJson(const QJsonArray &arr);

	// --- HUD Data ---
	struct sHUDData
	{
		double distanceToSurface = 0.0;
		CVector3 camera;
		CVector3 target;
		CVector3 rotation;
		double cameraDistance = 0.0;
		double currentSpeed = 0.0;
		double fps = 0.0;
		bool collisionWarning = false;
		bool isAnimating = false;
		bool isRecording = false;
		bool isPlaying = false;
		bool isOrbiting = false;
		bool isSurfaceFollowing = false;
		QString modeName;
	};

	sHUDData GetHUDData();
	void UpdateHUD();

private slots:
	void slotSmoothTick();
	void slotOrbitTick();
	void slotSurfaceFollowTick();
	void slotPlaybackTick();
	void slotRecordTick();

signals:
	void signalCameraUpdated();
	void signalHUDDataChanged(const cSmartCamera::sHUDData &data);
	void signalCollisionWarning(double distance);
	void signalFlightPathRecorded(int frameCount);
	void signalPlaybackFinished();
	void signalRender();

private:
	double GetDE(CVector3 point);
	CVector3 GetSurfaceNormal(CVector3 point, double de);
	void WriteCameraToParams(CVector3 cam, CVector3 tgt, CVector3 top);
	void ReadCameraFromParams(CVector3 &cam, CVector3 &tgt, CVector3 &top);

	std::shared_ptr<cParameterContainer> par;
	std::shared_ptr<cFractalContainer> parFractal;

	// Smooth interpolation
	QTimer *smoothTimer = nullptr;
	bool smoothAnimating = false;
	CVector3 smoothStartCam, smoothStartTgt, smoothStartTop;
	CVector3 smoothEndCam, smoothEndTgt;
	double smoothDuration = 1.0;
	double smoothProgress = 0.0;
	double smoothness = 0.15;
	QElapsedTimer smoothElapsed;

	// Collision avoidance
	bool collisionAvoidance = true;
	double minSafeDistance = 0.001;

	// Adaptive step
	bool adaptiveStep = true;

	// Orbit
	QTimer *orbitTimer = nullptr;
	bool orbitActive = false;
	CVector3 orbitCenter;
	double orbitRadius = 1.0;
	double orbitSpeed = 1.0;
	double orbitAngle = 0.0;
	double orbitPitch = 0.3;

	// Surface following
	QTimer *surfaceFollowTimer = nullptr;
	bool surfaceFollowActive = false;
	double surfaceFollowTargetDist = 0.1;
	double surfaceFollowSpeed = 1.0;
	CVector3 surfaceFollowDirection;

	// Flight path
	struct sFlightFrame
	{
		CVector3 camera;
		CVector3 target;
		CVector3 top;
		double timestamp;
	};
	QVector<sFlightFrame> flightPath;
	QTimer *recordTimer = nullptr;
	QTimer *playbackTimer = nullptr;
	bool recording = false;
	bool playing = false;
	int playbackFrame = 0;
	double playbackSpeed = 1.0;
	QElapsedTimer recordElapsed;

	// HUD
	sHUDData lastHUDData;
	QElapsedTimer fpsTimer;
	int frameCount = 0;
};

#endif /* MANDELBULBER2_QT_SMART_CAMERA_H_ */
