#pragma once

#include "TilemapHandler.h"

class Camera;
class Graphics;
class Texture;
class Sprite;

class LevelRenderer
{
public:
	LevelRenderer();
	~LevelRenderer();

	void Init(Graphics* graphics, Camera* camera);
	void Update(float deltaTime);
	void Render(Graphics* graphics);

	void DeleteAll();

	unsigned int GetWidth() const { return m_tilemapHandler->GetTilemapData().width; }

private:
	Camera* m_camera;
	TilemapHandler* m_tilemapHandler;
	Texture* m_tileSetTexture;
	Sprite* m_tileSetSprite;
};