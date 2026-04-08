#pragma once

#include "ScreenShake.h"
#include <directxtk/SimpleMath.h>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

using namespace DirectX::SimpleMath;

class EventManager;
class GameObject;

struct CameraControl {
	bool active = false;

	// for smooth release
	bool releasing = false;
	float releaseT = 0;

	// for smooth lock-in
	bool locking = false;
	float lockT = 0;
};

struct CameraCutsceneFocus : CameraControl {
	Vector2 position = Vector2::Zero;
	float fromX = 0;
	float toX = 0;
	float focusDuration = 2.0f;
};

struct CameraLock : CameraControl {
	float minX = 0;
	float maxX = 0;

	float fromMinX = 0, fromMaxX = 0;
	float toMinX = 0, toMaxX = 0;

	float releaseDuration = 0.35f;
	float lockDuration = 0.2f;
};

class Camera
{
public:
	Camera();
	~Camera();

	void			Init(EventManager* eventManager, float width);

	void			Update(float deltaTime);

	float			GetWidth() const { return m_width; }
	Vector2			GetPosition() const { return m_position + m_screenShake.GetPositionOffset(); }
	RECT			GetWorldRect() const;

	void			SetTarget(GameObject* target);
	void			SetPosition(const Vector2& position);
	void			SetWidth(float width);
	void			SetBoundary(float x);

	void			StartShake(float intensity, float duration);
	void			LockBounds(float min, float max);
	void			ReleaseBoundsSmooth(float duration, float min, float max);
	void			Reset();

	void			BeginCutsceneFocus(float focusX);
	void			ReleaseCutsceneFocus();
	bool			IsCutsceneFocusLocked() const { return m_cutsceneFocus.locking; }
	bool			IsCutsceneFocusReleasing() const { return m_cutsceneFocus.releasing; }

private:
	void			TrackTarget(float deltaTime);
	void			ClampCameraToBoundary();
	bool			TargetIsRightOfLeftThreshold(float targetX) const;
	bool			TargetIsLeftOfRightThreshold(float targetX) const;
	void			UpdatePosition(float deltaTime, float desiredX);

	GameObject*		m_trackingTarget;
	Vector2			m_position;
	float			m_width;
	float			m_boundary;
	float			m_threshold;
	ScreenShake		m_screenShake;
	EventManager*	m_eventManager;
	CameraLock		m_lock;
	CameraCutsceneFocus m_cutsceneFocus;
};
