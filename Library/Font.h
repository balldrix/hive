#ifndef _FONT_H_
#define _FONT_H_

#include "Sprite.h"

class Font
{
public:
	Font();
	~Font();
	void	Init(Sprite* sprite);
	void	Render(int score);

private:
	Sprite*				m_pSprite;

	const char*			m_filename;

};

#endif _FONT_H_