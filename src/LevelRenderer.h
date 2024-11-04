#pragma once

#include "TilemapData.h"

class Camera;
class Graphics;
class Sprite;

class LevelRenderer
{
public:
	LevelRenderer();
	~LevelRenderer();

	void Init(Graphics* graphics, Camera* camera);
	void Render(Graphics* graphics);

	void DeleteAll();

	unsigned int GetLevelPixelWidth() const { return m_tilemapData.width * m_tileWidth; }

private:
	TilemapData LoadTilemap(std::string path);
	void RenderLayer(Graphics* graphics, const TilemapLayer& layer);
	void RenderTile(Graphics* graphics, unsigned int tileId, unsigned int x, unsigned int y);

	Camera* m_camera;
	TilemapData m_tilemapData;
	Sprite* m_tileSetSprite;
	unsigned int m_tileWidth;
	unsigned int m_tileHeight;
	unsigned int m_tileSetSpriteWidth;
	unsigned int m_tileSetSpriteHeight;
	unsigned int m_tileSetWidth;
};