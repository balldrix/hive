#include "Animator.h"
#include "Error.h"

Animator::Animator() :
	m_currentAnimation(nullptr),
	m_paused(false),
	m_currentFrame(0),
	m_animDone(false),
	m_animationTimer(0.0f)
{
	m_animationList.clear();
}

Animator::~Animator()
{
	m_animationList.clear();
}

void Animator::Init(const std::string &fileName)
{
	// read file
	std::ifstream file(fileName);

	// parse data from file
	json data = json::parse(file);
	json animation = data["animation"];

	m_animationList = animation.get<std::vector<Animation>>();
	SetAnimation(0);
}

void Animator::Update(float deltaTime)
{
	if(m_paused)
		return;

	m_animationTimer += deltaTime;

	float frameRate;
	frameRate = 1 / (float)m_currentAnimation->framesPerSecond;

	if(m_animationTimer > frameRate)
	{
		m_animationTimer -= frameRate;

		if(!m_animDone)
		{
			if(m_currentFrame < ((unsigned int)m_currentAnimation->frameCount - 1))
			{
				m_currentFrame++;
			}
			else
			{
				if(m_currentAnimation->loop)
				{
					m_currentFrame = 0;
				}
				else
				{
					m_currentFrame = m_currentAnimation->frameCount - 1;
					m_animDone = true;
				}
			}
		}
	}
}

// set current animation from list using index
void Animator::SetAnimation(unsigned int index)
{
	m_currentAnimation = &m_animationList[index];
	m_animDone = false;
}

void Animator::SetAnimation(const std::string &name)
{
	Animation newAnimation;

	// loop through animation list
	for(unsigned int i = 0; i < m_animationList.size(); i++)
	{
		if(m_animationList[i].name == name)
		{
			SetAnimation(i);
			return;
		}
	}
	
	// unable to find animation with string so call error function
	std::string error = " Error! No animation with name " + name + " found. Check animation data.";
	Error::FileLog(error);
}

void Animator::Reset()
{
	m_animationTimer = 0.0f;
	m_animDone = false;
	m_currentFrame = 0;
}