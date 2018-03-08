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
	json animation = data["animation"];

	// iterate through data and save in animation list
	for(json::iterator it = animation.begin(); it != animation.end(); ++it)
	{
		// json of current it in array
		json j = it.value();

		// data struct
		Animation animationType;
		animationType.name = j["name"];
		animationType.spriteSheetIndex = j["index"];
		animationType.frameCount = j["frameCount"];
		animationType.framesPerSecond = j["framesPerSecond"];
		animationType.loop = j["loop"];

		m_animationList.push_back(animationType);
	}
}