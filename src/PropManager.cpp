#include "PropManager.h"

#include "AABB.h"
#include "Collider.h"
#include "LevelCollision.h"
#include "Prop.h"
#include "Sprite.h"
#include "TilemapLoader.h"
#include "Utils.h"

#include <directxtk/SimpleMath.h>
#include "AssetLoader.h"
#include <DirectXColors.h>

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

				position = Vector2(j->x, j->y);

				if(j->customProperties.contains("collider"))
				{
					aabb = ParseAABB(j->customProperties.at("collider"));
					aabb.OffSetAABB(position);
					collider.Init(m_debugSprite, Colors::Orange.v);
					collider.SetAABB(aabb);
					LevelCollision::AddCollider(j->name, collider);
				}

				isAnimated = j->customProperties.contains("isAnimated") && j->customProperties.at("isAnimated") == "true";
				prop = new Prop();
				prop->Init(j->name, camera, Vector2(j->x, j->y), collider, isAnimated);
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
