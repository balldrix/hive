#pragma once

#include "AABB.h"
#include "Collider.h"
#include "GameObject.h"

#include <directxtk/SimpleMath.h>
#include <string>

class Camera;
class Graphics;
class PropManager;
class SoundSource;

class Prop : public GameObject
{
public:
	Prop();
	~Prop();

	void Init(const std::string& id, const std::string& name, Camera* camera, const Vector2& position, Collider collider, bool isAnimated, bool isBreakable, PropManager* propManager);
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;

	Collider GetCollider() const;
	void Break();

	bool IsBreakable() const { return m_isBreakable; }

private:
	void Shutdown();

	PropManager* m_propManager;
	Collider m_collider;
	bool m_isAnimated;
	bool m_isBreakable;
	bool m_hasBroken;
};