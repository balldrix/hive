#pragma once

#include "TilemapHandler.h"
#include "Tile.h"
#include "InstanceData.h"

#include "pch.h"

class Camera;
class Graphics;
class Texture;
class QuadMesh;
class Material;
class Shader;

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

	void UpdateInstanceData(Graphics* graphics, const TilemapLayer& layer);
	InstanceType* GetInstanceData(Graphics* graphics, unsigned int tileId, const unsigned int& posX, const unsigned int& posY, const unsigned int& posZ);

	Camera* m_camera;
	Shader* m_shader;
	TilemapHandler* m_tilemapHandler;
	Texture* m_texture;
	Material* m_material;
	QuadMesh* m_quadMesh;
	Tile* m_tile;
	std::vector<InstanceType> m_tileInstances;

	unsigned int m_tileWidth;
	unsigned int m_tileHeight;
	unsigned int m_tileSetSpriteWidth;
	unsigned int m_tileSetSpriteHeight;
	unsigned int m_tileSetWidth;
	unsigned int m_numTiles;
};