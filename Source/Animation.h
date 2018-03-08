// Animation.h
// Christopher Ball 2018
// animation sourceRect data

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

struct Animation
{
	std::string	name;
	int spriteSheetIndex;
	int frameCount;
	int framesPerSecond;
	bool loop;
};

#endif // !_ANIMATION_H_
