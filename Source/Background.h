#pragma once

#include "GameObject.h"

class Sprite;
class Graphics;

class Background : public GameObject
{
public:
	Background();
	~Background();

	void Update(float deltaTime);
	void Init(Sprite* sprite);
	void Render(Graphics* graphics);

	Sprite* GetSprite() const { return m_spriteSheet; }

private:
	Sprite*		m_spriteSheet;
	void		Reset();
};