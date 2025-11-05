#pragma once

#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX::SimpleMath;

class Camera;
class Graphics;
class Sprite;
class Texture;
class Player;

class Pickup
{
public:
	Pickup();
	virtual ~Pickup();

	virtual void Init(const std::string& id, const Vector2& position,
		Camera* camera,
		Texture* texture, Color colour);
	virtual void Update(float deltaTime);
	virtual void Render(Graphics* graphics);
	virtual void ApplyEffect(Player* player) = 0;
	Vector2 GetPosition() const { return m_position; }

protected:
	virtual void Shutdown();

	Vector2 m_position;
	Camera* m_camera;
	Sprite* m_sprite;
};