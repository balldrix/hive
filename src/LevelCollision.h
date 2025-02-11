#pragma once

#include "Collider.h"

#include <directxtk/SimpleMath.h>
#include <map>
#include <string>

class LevelCollision
{
public:
	LevelCollision();
	~LevelCollision();

	static void Init();
	static void Shutdown();

	static void AddCollider(std::string id, Collider box);
	static void RemoveCollider(std::string id);
	static Collider* GetCollider(std::string id);
	static void ClearAll();

	static bool IsCollision(Collider box);
	static bool IsCollision(Vector2 position);

private:
	static LevelCollision* s_instance;
	typedef std::map<std::string, Collider> ColliderMap;
	ColliderMap m_colliders;
};