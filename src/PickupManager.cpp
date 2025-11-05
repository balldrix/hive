#include "PickupManager.h"

#include "AssetLoader.h"
#include "FullHealthPickup.h"
#include "FullSpecialPickup.h"
#include "HealthPickup.h"
#include "Pickup.h"
#include "Randomiser.h"
#include "SpecialPickup.h"
#include "Texture.h"

#include <algorithm>
#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>

PickupManager::PickupManager() :
	m_pickupList(),
	m_spawnCount(0),
	m_weightedList(),
	m_camera(nullptr)
{
}

PickupManager::~PickupManager()
{
	Shutdown();
}

void PickupManager::Init(Camera* camera)
{
	m_camera = camera;

	m_weightedList = 
	{
		{ 0.25f, PickupType::None },
		{ 0.4f, PickupType::Health },
		{ 0.25f, PickupType::Special },
		{ 0.05f, PickupType::FullHealth },
		{ 0.05f, PickupType::FullSpecial }
	};
}

void PickupManager::Update(float deltaTime)
{
	for(const auto& pickup : m_pickupList)
	{
		pickup->Update(deltaTime);
	}
}

void PickupManager::Render(Graphics* graphics)
{
	for(const auto& pickup : m_pickupList)
	{
		pickup->Render(graphics);
	}
}

void PickupManager::TrySpawnPickup(const Vector2& position)
{
	float totalWeight = 0.0f;
	for(const auto& wp : m_weightedList)
		totalWeight += wp.weight;

	if(totalWeight <= 0.0f)
		return;

	float roll = Randomiser::GetRandNumUniform(0.0f, totalWeight);

	float cumulative = 0.0f;
	for(const auto& wp : m_weightedList)
	{
		cumulative += wp.weight;
		if(roll <= cumulative)
		{
			Texture* texture = AssetLoader::GetTexture("t_pickup");

			switch(wp.type)
			{
				case PickupType::None:
					// No pickup spawned
					return;
				case PickupType::Health:
				{
					HealthPickup* healthPickup = new HealthPickup();
					healthPickup->Init(fmt::format("health_pickup_{0}", m_spawnCount), position, m_camera, texture, Colors::LightBlue.v);
					m_pickupList.push_back(healthPickup);
					break;
				}
				case PickupType::Special:
				{
					SpecialPickup* specialPickup = new SpecialPickup();
					specialPickup->Init(fmt::format("special_pickup_{0}", m_spawnCount), position, m_camera, texture, Colors::Yellow.v);
					m_pickupList.push_back(specialPickup);
					break;
				}
				case PickupType::FullHealth:
				{
					FullHealthPickup* fullHealthPickup = new FullHealthPickup();
					fullHealthPickup->Init(fmt::format("fullhealth_pickup_{0}", m_spawnCount), position, m_camera, texture, Colors::DarkBlue.v);
					m_pickupList.push_back(fullHealthPickup);
					break;
				}
				case PickupType::FullSpecial:
				{
					FullSpecialPickup* fullSpecialPickup = new FullSpecialPickup();
					fullSpecialPickup->Init(fmt::format("fullspecial_pickup{0}", m_spawnCount), position, m_camera, texture, Colors::Orange.v);
					m_pickupList.push_back(fullSpecialPickup);
					break;
				}
			}
			break;
		}
	}

	m_spawnCount++;
}

void PickupManager::RemovePickup(Pickup* pickup)
{
	m_pickupList.erase(find(m_pickupList.begin(), m_pickupList.end(), pickup));
	delete pickup;
	pickup = nullptr;
}

void PickupManager::Shutdown()
{
	for(auto pickup : m_pickupList)
	{
		delete pickup;
		pickup = nullptr;
	}

	m_pickupList.clear();
	m_spawnCount = 0;
}