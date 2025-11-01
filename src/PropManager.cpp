#include "PropManager.h"

#include "AABB.h"
#include "AssetLoader.h"
#include "Collider.h"
#include "LevelCollision.h"
#include "Prop.h"
#include "Sprite.h"
#include "TilemapLoader.h"
#include "Utils.h"

#include <algorithm>
#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>

using namespace Utils;

PropManager::PropManager() :
	m_propList(),
	m_debugSprite(nullptr)
{
}

PropManager::~PropManager()
{
	Shutdown();
}

void PropManager::Init(Camera* camera)
{
	m_debugSprite = new Sprite();
	m_debugSprite->Init(AssetLoader::GetTexture("t_pixel"));

	auto currentMap = TilemapLoader::GetCurrentMap();

	for(auto i = currentMap.layers.begin(); i != currentMap.layers.end(); i++)
	{
		if(i->name == "props")
		{
			for(auto j = i->objectData.begin(); j != i->objectData.end(); j++)
			{
				Prop* prop;
				AABB aabb;
				Vector2 position;
				Collider collider;
				bool isAnimated;
				bool isBreakable;
				std::string id;

				position = Vector2(j->x, j->y);
				id = fmt::format("{0}_{1}", j->name, j->id);

				if(j->customProperties.contains("collider"))
				{
					aabb = ParseAABB(j->customProperties.at("collider"));
					aabb.OffSetAABB(position);
					collider.Init(m_debugSprite, Colors::Orange.v);
					collider.SetAABB(aabb);
					LevelCollision::AddCollider(id, collider);
				}

				isAnimated = j->customProperties.contains("isAnimated") && j->customProperties.at("isAnimated") == "true";
				isBreakable = j->customProperties.contains("isBreakable") && j->customProperties.at("isBreakable") == "true";

				prop = new Prop();
				prop->Init(id, j->name, camera, Vector2(j->x, j->y), collider, isAnimated, isBreakable, this);
				m_propList.push_back(prop);
			}
		}
	}
}

void PropManager::Update(float deltaTime)
{
	for(auto prop : m_propList)
	{
		prop->Update(deltaTime);
	}
}

void PropManager::Render(Graphics* graphics)
{
	for(auto prop : m_propList)
	{
		prop->Render(graphics);
	}
}

void PropManager::Remove(Prop* prop)
{
	m_propList.erase(find(m_propList.begin(), m_propList.end(), prop));
	delete prop;
	prop = nullptr;
}

void PropManager::Shutdown()
{
	for(auto prop : m_propList)
	{
		delete prop;
		prop = nullptr;
	}

	m_propList.clear();

	delete m_debugSprite;
	m_debugSprite = nullptr;
}
