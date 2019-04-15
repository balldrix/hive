#include "HitBoxManager.h"
#include "Graphics.h"
#include "GameObject.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "Animation.h"


HitBoxManager::HitBoxManager() :
	m_owner(nullptr),
	m_sprite(nullptr),
	m_currentHitBoxData(nullptr),
	m_hitBoxDataList(0)
{
}


HitBoxManager::~HitBoxManager()
{
	m_hitBoxDataList.clear();
}

void HitBoxManager::Init(Sprite* sprite, GameObject* owner, std::string fileName)
{
	m_sprite = sprite;
	m_owner = owner;

	LoadData(fileName);
	SetCurrentHitBox("Idle");

	// initialise hitboxes
	m_movementBox.Init(sprite, m_currentHitBoxData->movementBox, Colors::Blue.v);
	m_hurtBox.Init(sprite, m_currentHitBoxData->hurtBox, Colors::Green.v);
	m_hitBox.Init(sprite, m_currentHitBoxData->hitBox, Colors::Red.v);
}

// set box positions
void HitBoxManager::Update()
{
	Vector2 ownerPosition = m_owner->GetSprite()->GetPosition();
	m_movementBox.Update(ownerPosition);
	m_hurtBox.Update(ownerPosition);
	m_hitBox.Update(ownerPosition);
}

// render boxes
void HitBoxManager::Render(Graphics* graphics)
{
	m_movementBox.Render(graphics);
	m_hurtBox.Render(graphics);

	// only render hitbox if it is active
	if(IsHitBoxActive())
	{
		m_hitBox.Render(graphics);
	}
}

// flip boxes
void HitBoxManager::SetFlipped(bool flip)
{
	m_movementBox.SetFlipped(flip);
	m_hitBox.SetFlipped(flip);
	m_hurtBox.SetFlipped(flip);
}

void HitBoxManager::SetCurrentHitBox(std::string name)
{
	int index = 0;

	for(unsigned int i = 0; i < m_hitBoxDataList.size(); i++)
	{
		if(name == m_hitBoxDataList[i].name)
		{
			index = i;
		}
	}

	SetCurrentHitBox(index);
}

void HitBoxManager::SetCurrentHitBox(int index)
{
	m_currentHitBoxData = &m_hitBoxDataList[index];
	SetAllHitBoxes();
}

void HitBoxManager::KillAll()
{
	AABB empty;
	m_movementBox.SetAABB(empty);
	m_hitBox.SetAABB(empty);
	m_hurtBox.SetAABB(empty);
}

bool HitBoxManager::IsHitBoxActive()
{
	int currentFrame = m_owner->GetAnimator()->GetCurrentFrame();
	int startup = m_currentHitBoxData->startupFrames - 1;
	int active = m_currentHitBoxData->activeFrames + startup;

	if(m_owner->GetAnimator()->GetAnimation()->name == "Jab")
	{
		if(currentFrame >= startup && currentFrame <= active)
		{
			return true;
		}
	}

	return false;
}

void HitBoxManager::LoadData(std::string fileName)
{
	// read file
	std::ifstream file(fileName);

	// parse data from file
	json data = json::parse(file);
	json hitbox = data["hitbox"];

	m_hitBoxDataList = hitbox.get<std::vector<HitBoxData>>();
}

void HitBoxManager::SetAllHitBoxes()
{
	SetMovementBox();
	SetHurtBox();
	SetHitBox();
}

void HitBoxManager::SetMovementBox()
{
	m_movementBox.SetAABB(m_currentHitBoxData->movementBox);
}

void HitBoxManager::SetHurtBox()
{
	m_hurtBox.SetAABB(m_currentHitBoxData->hurtBox);
}

void HitBoxManager::SetHitBox()
{
	m_hitBox.SetAABB(m_currentHitBoxData->hitBox);
}
