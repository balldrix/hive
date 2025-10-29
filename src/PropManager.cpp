#include "PropManager.h"

#include "LevelCollision.h"
#include "Prop.h"
#include "TilemapLoader.h"

#include <directxtk/SimpleMath.h>

PropManager::PropManager() :
	m_propList()
{
}

PropManager::~PropManager()
{
	Shutdown();
}

void PropManager::Init(Camera* camera)
{
	auto currentMap = TilemapLoader::GetCurrentMap();

	for(auto i = currentMap.layers.begin(); i != currentMap.layers.end(); i++)
	{
		if(i->name == "props")
		{
			for(auto j = i->objectData.begin(); j != i->objectData.end(); j++)
			{
				Prop* prop = new Prop();

				bool isAnimated = j->customProperties.contains("isAnimated") && j->customProperties.at("isAnimated") == "true";
				prop->Init(j->name, camera, Vector2(j->x, j->y), Vector2(j->width, j->height), isAnimated);
				m_propList.push_back(prop);

				LevelCollision::AddCollider(j->name, prop->GetCollider());
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
}
