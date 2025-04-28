#pragma once

#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX;
using namespace SimpleMath;

class Spritesheet;
class Animator;
class Graphics;

class SpriteFx
{
public:
	SpriteFx();
	~SpriteFx();

	void Init(std::string textureId, std::string spriteId, const Vector2& origin);
	void Render(Graphics* graphics);
	void Update(float deltaTime);

	void DisplayFx(const Vector2& position);
	Vector2 Position() const { return m_position; }
	bool IsActive() const { return m_isActive; }

private:
	Spritesheet* m_spritesheet;
	Animator* m_animator;
	Vector2 m_position;

	bool m_isActive;
};