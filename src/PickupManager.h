#pragma once

#include <directxtk/SimpleMath.h>
#include <vector>

using namespace DirectX::SimpleMath;

class Camera;
class Graphics;
class Pickup;

class PickupManager
{
public:
	PickupManager();
	~PickupManager();

	void Init(Camera* camera);
	void Update(float deltaTime);
	void Render(Graphics* graphics);

	void TrySpawnPickup(const Vector2& position);
	void RemovePickup(Pickup* pickup);
	std::vector<Pickup*> GetPickupList() const { return m_pickupList; }

private:
	void Shutdown();

	enum PickupType 
	{ 
		None,
		Health,
		Special,
		FullHealth,
		FullSpecial
	};

	struct WeightedPickup
	{
		float weight;
		PickupType type;
	};

	Camera* m_camera;
	std::vector<Pickup*> m_pickupList;
	std::vector<WeightedPickup> m_weightedList;
	int m_spawnCount;
};