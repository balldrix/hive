#include "HitBoxManager.h"
#include "Graphics.h"
#include "GameObject.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "Animation.h"
#include "Camera.h"
#include "GameplayConstants.h"

using namespace GameplayConstants;

HitBoxManager::HitBoxManager() :
	m_owner(nullptr),
	m_spriteSheet(nullptr),
	m_hitBoxDataList(0),
	m_isVisible(false)
{
}


HitBoxManager::~HitBoxManager()
{
	m_hitBoxDataList.clear();
	m_pushBox.Delete();
	m_hitBox.Delete();
	m_hurtBox.Delete();
}

void HitBoxManager::Init(Sprite* sprite, const std::string &fileName)
{
	Init(sprite, nullptr, fileName);
}

void HitBoxManager::Init(Sprite* sprite, GameObject* owner, const std::string &fileName)
{
	m_spriteSheet = sprite;
	m_owner = owner;

	LoadData(fileName);

	// initialise hitboxes
	m_pushBox.Init(sprite, Colors::Blue.v);
	m_hurtBox.Init(sprite, Colors::Green.v);
	m_hitBox.Init(sprite, Colors::Red.v);
}

// set box positions
void HitBoxManager::Update()
{
	Vector2 ownerPosition = m_owner->GetPosition();
	m_pushBox.Update(ownerPosition);
	m_hurtBox.Update(ownerPosition);
	m_hitBox.Update(ownerPosition);
}

void HitBoxManager::Update(const unsigned int& frameNumber)
{
	UpdateCollider(frameNumber, m_pushBoxTagData, m_pushBox);
	UpdateCollider(frameNumber, m_hitBoxTagData, m_hitBox);
	UpdateCollider(frameNumber, m_hurtBoxTagData, m_hurtBox);

	Update();
}

void HitBoxManager::UpdateCollider(const unsigned int& frameNumber, TagData& tagData, Collider& collider)
{
	auto frame = FrameData::GetFrameData(frameNumber, tagData.frameData);
	Vector2 origin = m_owner->GetSprite()->GetOrigin();

	AABB aabb;
	aabb.SetMin(Vector2(frame.bounds.x - origin.x, frame.bounds.y - origin.y));
	aabb.SetMax(Vector2(aabb.GetMin().x + frame.bounds.width, aabb.GetMin().y + frame.bounds.height));

	collider.SetAABB(aabb);
}

// render boxes
void HitBoxManager::Render(Graphics* graphics, Camera* camera)
{
	if(!m_isVisible)
		return;

	Vector2 screenPosition = m_owner->GetPosition();

	if (camera != nullptr)
		screenPosition.x -= camera->GetPosition().x;

	m_pushBox.Render(graphics, screenPosition);
	m_hurtBox.Render(graphics, screenPosition);

	// only render hitbox if it is active
	if(IsHitBoxActive())
	{
		m_hitBox.Render(graphics, screenPosition);
	}
}

void HitBoxManager::SetOwner(GameObject* owner)
{
	m_owner = owner;
}

void HitBoxManager::SetCollidersUsingTag(const std::string &name)
{
	HitBoxData pushBox;
	HitBoxData hitBox;
	HitBoxData hurtBox;

	pushBox = HitBoxData::GetHitBoxData(PushBoxName, m_hitBoxDataList);
	hitBox = HitBoxData::GetHitBoxData(HitBoxName, m_hitBoxDataList);
	hurtBox = HitBoxData::GetHitBoxData(HurtBoxName, m_hitBoxDataList);

	m_pushBoxTagData = TagData::GetTagData(name, pushBox.tagData);
	m_hitBoxTagData = TagData::GetTagData(name, hitBox.tagData);
	m_hurtBoxTagData = TagData::GetTagData(name, hurtBox.tagData);

	Update(0);
}

void HitBoxManager::SetFlipped(bool flip)
{
	m_pushBox.SetFlipped(flip);
	m_hitBox.SetFlipped(flip);
	m_hurtBox.SetFlipped(flip);
}

bool HitBoxManager::IsHitBoxActive()
{
	return m_hitBox.GetAABB().GetMin().x != m_hitBox.GetAABB().GetMax().x &&
		m_hitBox.GetAABB().GetMin().y != m_hitBox.GetAABB().GetMax().y;
}

void HitBoxManager::LoadData(const std::string &fileName)
{
	// read file
	std::ifstream file(fileName);

	// parse data from file
	json data = json::parse(file);
	
	m_hitBoxDataList = data.get<std::vector<HitBoxData>>();
}