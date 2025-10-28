#include "LevelCollision.h"

#include "AABB.h"
#include "AssetLoader.h"
#include "Camera.h"
#include "Collider.h"
#include "GameplayConstants.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "LevelRenderer.h"
#include "Logger.h"
#include "Sprite.h"
#include "TilemapLoader.h"

#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <string>

using namespace GameplayConstants;
using namespace GlobalConstants;

LevelCollision* LevelCollision::s_instance = nullptr;

LevelCollision::LevelCollision() :
	m_colliders(),
	m_sprite(nullptr),
	m_isVisible(false),
	m_camera(nullptr)
{
}

LevelCollision::~LevelCollision()
{
}

void LevelCollision::Init(Camera* camera)
{
	s_instance = new LevelCollision;
	s_instance->m_sprite = new Sprite();
	s_instance->m_sprite->Init(AssetLoader::GetTexture("t_pixel"));
	s_instance->m_camera = camera;
}

void LevelCollision::Shutdown()
{
	if(s_instance == nullptr) return;

	delete s_instance->m_sprite;
	s_instance->m_sprite = nullptr;

	delete s_instance;
	s_instance = nullptr;
}

void LevelCollision::Render(Graphics* graphics)
{
	if(!s_instance->m_isVisible) return;

	auto& colliders = s_instance->m_colliders;

	for(auto it = colliders.begin(); it != colliders.end(); ++it)
	{
		auto& collider = it->second;
		collider.Render(graphics, -s_instance->m_camera->GetPosition());
	}
}

void LevelCollision::CreateBounds(LevelRenderer* levelRenderer)
{
	Sprite* sprite = s_instance->m_sprite;
	const Color colliderColour = Colors::Orange.v;

	Collider upperBounds;
	upperBounds.Init(sprite, colliderColour);
	upperBounds.SetAABB(AABB(Vector2(0, 0), Vector2((float)levelRenderer->GetLevelPixelWidth(), GameplayBoundsUpperY)));
	upperBounds.Update(Vector2::Zero);
	LevelCollision::AddCollider(UpperBoundsId, upperBounds);

	Collider lowerBounds;
	lowerBounds.Init(sprite, Colors::Orange.v);
	lowerBounds.SetAABB(AABB(Vector2(0, GameplayBoundsLowerY), Vector2((float)levelRenderer->GetLevelPixelWidth(), GameHeight)));
	lowerBounds.Update(Vector2::Zero);
	LevelCollision::AddCollider(LowerBoundsId, lowerBounds);

	Collider leftBounds;
	leftBounds.Init(sprite, Colors::Orange.v);
	leftBounds.SetAABB(AABB(Vector2(-10, 0), Vector2(0, GameHeight)));
	leftBounds.Update(Vector2::Zero);
	LevelCollision::AddCollider(LeftBoundsId, leftBounds);

	Collider rightBounds;
	rightBounds.Init(sprite, Colors::Orange.v);
	rightBounds.SetAABB(AABB(Vector2((float)levelRenderer->GetLevelPixelWidth()), Vector2((float)levelRenderer->GetLevelPixelWidth() + 10)));
	rightBounds.Update(Vector2::Zero);
	LevelCollision::AddCollider(RightBoundsId, rightBounds);

	auto currentMap = TilemapLoader::GetCurrentMap();

	for(auto i = currentMap.layers.begin(); i != currentMap.layers.end(); i++)
	{
		if(i->name == "bounds" || i->name == "props")
		{
			for(auto j = i->objectData.begin(); j != i->objectData.end(); j++)
			{
				Collider collider;
				Vector2 position = Vector2(j->x, j->y);
				collider.Init(sprite, colliderColour);
				collider.SetAABB(AABB(position, Vector2(position.x + j->width, position.y + j->height)));
				LevelCollision::AddCollider(fmt::to_string(j->id), collider);
			}
		}
	}
}

void LevelCollision::AddCollider(std::string id, Collider box)
{
	if(s_instance->m_colliders.contains(id))
	{
		Logger::LogWarning(fmt::format("[Level Collision] Collision map already contains Collider with id {}", id));
		return;
	}
		
	s_instance->m_colliders[id] = box;
}

void LevelCollision::RemoveCollider(std::string id)
{
	s_instance->m_colliders.erase(id);
}

Collider* LevelCollision::GetCollider(std::string id)
{
	if(!s_instance->m_colliders.contains(id))
	{
		Logger::LogWarning(fmt::format("[Level Collision] Collider with id {} does not exist", id));
		return nullptr;
	}

	return &s_instance->m_colliders[id];
}

void LevelCollision::ClearAll()
{
	s_instance->m_colliders.clear();
}

bool LevelCollision::IsCollision(Collider box)
{
	for(auto it = s_instance->m_colliders.begin(); it != s_instance->m_colliders.end(); it++)
	{ 
		if(!(*it).second.OnCollision(box)) continue;

		return true;
	}

	return false;
}

bool LevelCollision::IsCollision(Vector2 position)
{
	for(auto it = s_instance->m_colliders.begin(); it != s_instance->m_colliders.end(); it++)
	{
		if(!(*it).second.OnCollision(position)) continue;

		return true;
	}

	return false;
}

void LevelCollision::SetVisible(bool isVisible)
{
	s_instance->m_isVisible = isVisible;
}
