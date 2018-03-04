// Animation.h
// Christopher Ball 2018
// animation frame data

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

struct Animation
{
	const wchar_t* m_name;
	unsigned int m_spriteSheetIndex;
	unsigned int m_frameCount;
	unsigned int m_framesPerSecond;
	bool m_loop;
};

#endif // !_ANIMATION_H_
