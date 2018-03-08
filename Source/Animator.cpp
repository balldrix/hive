#include "Animator.h"

Animator::Animator() :
	m_currentAnimation(nullptr),
	m_paused(false),
	m_currentFrame(0),
	m_animDone(false),
	m_loop(false),
	m_animationTimer(0.0f)
{
	m_animationList.clear();
}

Animator::~Animator()
{
	m_animationList.clear();
}

void Animator::Init(std::string fileName)
{
	// read file
	std::ifstream file(fileName);

	// parse data from file
	json data = json::parse(file);

	// iterate through data and save in animation list
	for(json::iterator it = data.begin(); it != data.end(); ++it)
	{
		// current iterator
		json anim = it.value();

		// data struct
		Animation animation;
		animation.spriteSheetIndex = anim["index"];
	}
}