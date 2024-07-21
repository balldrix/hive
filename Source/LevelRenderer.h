#pragma once

#include "TilemapHandler.h"

class Camera;
class Graphics;
class Texture;
class Material;
class QuadMesh;
class Shader;
class Tile;

class LevelRenderer
{
public:
	LevelRenderer();
	~LevelRenderer();

	void Init(Graphics* graphics, Camera* camera, Shader* shader);
	void Render(Graphics* graphics);

	void DeleteAll();

	unsigned int GetLevelPixelWidth() const { return m_tilemapHandler->GetTilemapData().width * m_tileWidth; }

private:

	void RenderLayer(Graphics* graphics, const TilemapLayer& layer);
	void RenderTile(Graphics* graphics, unsigned int tileId, unsigned int x, unsigned int y);

	Camera* m_camera;
	Shader* m_shader;
	TilemapHandler* m_tilemapHandler;
	Texture* m_texture;
	Material* m_material;
	QuadMesh* m_quadMesh;
	Tile* m_tile;

	unsigned int m_tileWidth;
	unsigned int m_tileHeight;
	unsigned int m_tileSetSpriteWidth;
	unsigned int m_tileSetSpriteHeight;
	unsigned int m_tileSetWidth;
};