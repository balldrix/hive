#pragma once

#include "Collider.h"
#include "HitBoxData.h"

#include <string>
#include <vector>

class Graphics;
class Camera;
class GameObject;
class Texture;
class Sprite;

class HitBoxManager
{
public:
	HitBoxManager();
	~HitBoxManager();

	void Init(GameObject* owner, std::vector<HitBoxData> hitBoxData);
	void Update();
	void Update(const unsigned int& frameNumber);
	void UpdateCollider(const unsigned int& frameNumber, TagData& tagData, Collider& collider);
	void Render(Graphics* graphics, Camera* camera);

	void SetOwner(GameObject* owner);
	void SetCollidersUsingTag(const std::string& tagName);

	void SetFlipped(bool flip);
	void SetVisible(bool isVisible) { m_isVisible = isVisible; }

	Collider GetPushBox() const { return m_pushBox; }
	Collider GetHurtBox() const { return m_hurtBox; }
	Collider GetHitBox() const { return m_hitBox; }

	bool IsHitBoxActive();

private:
	GameObject* m_owner;
	Sprite* m_sprite;
	std::vector<HitBoxData> m_hitBoxDataList;

	Collider m_pushBox;
	Collider m_hurtBox;
	Collider m_hitBox;

	TagData m_pushBoxTagData;
	TagData m_hitBoxTagData;
	TagData m_hurtBoxTagData;

	bool m_isVisible;
};