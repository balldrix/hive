#pragma once

#include "Collider.h"
#include "GameObject.h"

#include <string>

class Camera;
class Graphics;

class Prop : public GameObject
{
public:
	Prop();
	~Prop();

	void Init(const std::string& id, Camera* camera, const Vector2& position, const Vector2& size, bool isAnimated);
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;

	Collider GetCollider() const { return m_collider; }
private:
	void Shutdown();
	Collider m_collider;
	bool m_isAnimated;
};