#pragma once

#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX::SimpleMath;

class Camera;
class Graphics;
class Sprite;
class Texture;

class Pickup
{
public:
	virtual ~Pickup() {};

	virtual void Init(const std::string& id, const Vector2& position,
		Camera* camera,
		Texture* texture) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(Graphics* graphics) = 0;
	virtual void ApplyEffect() = 0;
	Vector2 GetPosition() const { return m_position; }

protected:
	virtual void Shutdown() = 0;

	Vector2 m_position;
	Camera* m_camera;
	Sprite* m_sprite;
};