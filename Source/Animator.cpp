#include "Animator.h"

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

void Animator::Init(std::string fileName)
{
	// read file
	std::ifstream file(fileName);

	// parse data from file
	json data = json::parse(file);
	json animation = data["animation"];

	m_animationList = animation.get<std::vector<Animation>>();
}

void Animator::Update(float deltaTime)
{
	// if paused
	if(m_paused)
	{
		return;
	}

	// update timer
	m_animationTimer += deltaTime;

	// calculate frame rate
	float frameRate;
	frameRate = 1 / (float)m_currentAnimation->framesPerSecond;

	// if timer has gone over rate
	if(m_animationTimer > frameRate)
	{
		// reset timer
		m_animationTimer -= frameRate;

		// if animation is not over
		if(!m_animDone)
		{
			// if frame count is below max num of frames in animation
			if(m_currentFrame < ((unsigned int)m_currentAnimation->frameCount - 1))
			{
				// increase frame count
				m_currentFrame++;
			}
			else
			{
				// if animation should loop
				if(m_currentAnimation->loop)
				{
					// reset frame count
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

void Animator::SetAnimation(unsigned int index)
{
	m_currentAnimation = &m_animationList[index];
}

void Animator::Reset()
{
	m_animationTimer = 0.0f;
	m_animDone = false;
	m_currentFrame = 0;
}