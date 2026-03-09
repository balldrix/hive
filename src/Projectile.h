#pragma once

#include "Collider.h"

#include <directxtk/SimpleMath.h>

class GameObject;

using namespace DirectX::SimpleMath;

struct Projectile
{
	Vector2 position = Vector2::Zero;
	Vector2 previousPosition = Vector2::Zero;
	Vector2 direction = Vector2::UnitX;
	float speed = 0.0f;
	float lifetimeRemaining = 0.0f;
	int damage = 0;
	bool active = false;
	Collider collider = {};
	GameObject* owner = nullptr;
};
