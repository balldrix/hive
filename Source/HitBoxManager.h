// HitBoxManager.h
// Christopher Ball 2019
// manages hitbox data

#ifndef _HITBOXMANAGER_H_
#define _HITBOXMANAGER_H_

#include "pch.h"
#include "HitBox.h"

class Graphics;
class GameObject;
class Sprite;

namespace
{
	struct HitBoxData
	{
		std::string	name; // name of hitbox data should be same as animation state name
		AABB movementBox; // hit box to block movement in scene
		AABB hitBox; // hit box (red) is what will do damage to other character
		AABB hurtBox; // hit box that set character's vulnerable area
		int startupFrames;
		int activeFrames;
	};

	void from_json(const json& j, HitBoxData& a)
	{
		a.name = j.at("name").get<std::string>();
		a.startupFrames = j.at("startup").get<int>();
		a.activeFrames = j.at("active").get<int>();

		// movement box data
		json movement = j["movementBox"];
		a.movementBox.SetMin(Vector2(movement["minX"], movement["minY"]));
		a.movementBox.SetMax(Vector2(movement["maxX"], movement["maxY"]));

		// hitbox data
		json hits = j["hitBox"];
		a.hitBox.SetMin(Vector2(hits["minX"], hits["minY"]));
		a.hitBox.SetMax(Vector2(hits["maxX"], hits["maxY"]));

		// hurt box data
		json hurts = j["hurtBox"];
		a.hurtBox.SetMin(Vector2(hurts["minX"], hurts["minY"]));
		a.hurtBox.SetMax(Vector2(hurts["maxX"], hurts["maxY"]));
	}
}

class HitBoxManager
{
public:
	HitBoxManager();
	~HitBoxManager();

	void Init(Sprite* sprite, GameObject* owner, std::string fileName);
	void Update();
	void Render(Graphics* graphics);

	void SetFlipped(bool flip); // flip the hitbox data
	void SetCurrentHitBox(std::string name);
	void SetCurrentHitBox(int index);

	HitBox GetMovementBox() const { return m_movementBox; }
	HitBox GetHurtBox() const { return m_hurtBox; }
	HitBox GetHitBox() const { return m_hitBox; }

	void Kill();

	bool IsHitBoxActive();

private:
	GameObject* m_owner; // owner of the hitbox manager
	Sprite* m_sprite; // debug sprite
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

#endif _HITBOXMANAGER_