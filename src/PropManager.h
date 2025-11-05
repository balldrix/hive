#pragma once

#include <vector>

class Camera;
class Graphics;
class Prop;
class Sprite;
class Player;

class PropManager
{
public:
	PropManager();
	~PropManager();

	void Init(Camera* camera, Player* player);
	void Update(float deltaTime);
	void Render(Graphics* graphics);
	void Remove(Prop* prop);
	std::vector<Prop*> GetPropList() const { return m_propList; }

private:
	void Shutdown();
	std::vector<Prop*> m_propList;
	Sprite* m_debugSprite;
};