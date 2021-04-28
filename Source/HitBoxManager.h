#pragma once

#include "pch.h"
#include "HitBox.h"
#include "HitBoxData.h"

class Graphics;
class GameObject;
class Sprite;

class HitBoxManager
{
public:
	HitBoxManager();
	~HitBoxManager();

	void Init(Sprite* sprite, std::string fileName);
	void Init(Sprite* sprite, GameObject* owner, std::string fileName);
	void Update();
	void Render(Graphics* graphics);

	void SetOwner(GameObject* owner);
	void SetFlipped(bool flip); // flip the hitbox data
	void SetCurrentHitBox(std::string name);
	void SetCurrentHitBox(const int& index);

	HitBox GetMovementBox() const { return m_movementBox; }
	HitBox GetHurtBox() const { return m_hurtBox; }
	HitBox GetHitBox() const { return m_hitBox; }

	void KillAll();

	bool IsHitBoxActive();

private:
	GameObject* m_owner;	// owner of the hitbox manager
	Sprite* m_spriteSheet; // debug sprite
	HitBoxData* m_currentHitBoxData; // current hit box in use
	std::vector<HitBoxData> m_hitBoxDataList; // list of all hitboxes in this manager
	HitBox m_movementBox;	// hit box to block movement in scene
	HitBox m_hurtBox;		// hurt box that set character's vulnerable area
	HitBox m_hitBox;		// hit box (red) is what will do damage to other character

	// load json data
	void LoadData(std::string fileName);

	// set hitboxes
	void SetAllHitBoxes();
	void SetMovementBox();
	void SetHurtBox();
	void SetHitBox();
};