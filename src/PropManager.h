#pragma once

#include <vector>

class Camera;
class Graphics;
class Prop;

class PropManager
{
public:
	PropManager();
	~PropManager();

	void Init(Camera* camera);
	void Update(float deltaTime);
	void Render(Graphics* graphics);
private:
	void Shutdown();
	std::vector<Prop*> m_propList;
};