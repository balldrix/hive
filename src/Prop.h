#pragma once

#include "GameObject.h"

#include <string>

class Camera;
class Graphics;

class Prop : public GameObject
{
public:
	Prop();
	~Prop();

	void Init(const std::string& id, Camera* camera, bool isAnimated);
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
};