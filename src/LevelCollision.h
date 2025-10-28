#pragma once

#include "Collider.h"
#include "LevelRenderer.h"
#include "Sprite.h"

#include <directxtk/SimpleMath.h>
#include <map>
#include <string>

class Camera;
class Graphics;

class LevelCollision
{
public:
	LevelCollision();
	~LevelCollision();

	static void Init(Camera* camera);
	static void Shutdown();

	static void Render(Graphics* graphics);

	static void CreateBounds(LevelRenderer* levelrenderer);
	static void AddCollider(std::string id, Collider box);
	static void RemoveCollider(std::string id);
	static Collider* GetCollider(std::string id);
	static void ClearAll();

	static bool IsCollision(Collider box);
	static bool IsCollision(Vector2 position);

	static void SetVisible(bool isVisible);

private:
	static LevelCollision* s_instance;
	typedef std::map<std::string, Collider> ColliderMap;
	ColliderMap m_colliders;
	Sprite* m_sprite;
	bool m_isVisible;
	Camera* m_camera;
};