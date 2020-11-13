// Background.h
// Christopher Ball 2019-2020
// background object

#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

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

	Sprite* GetSprite() const { return m_sprite; }

private:
	Sprite*		m_sprite;
	void		Reset();
};

#endif // !_BACKGROUND_H_