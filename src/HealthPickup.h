#pragma once

#include "Pickup.h"

#include <directxtk/SimpleMath.h>
#include <string>

class Camera;
class Graphics;
class Texture;

class HealthPickup : public Pickup
{
public:
	HealthPickup() {};
	~HealthPickup() {};

	void Init(const std::string& id,
		const Vector2& position,
		Camera* camera,
		Texture* texture) override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
	void ApplyEffect() override;
	void Shutdown() override;
};