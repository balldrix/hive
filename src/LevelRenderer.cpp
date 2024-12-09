#include "LevelRenderer.h"

#include "AssetLoader.h"
#include "Camera.h"
#include "Graphics.h"
#include "Logger.h"
#include "Sprite.h"
#include "TilemapData.h"

#include <fmt/core.h>
#include <fstream>
#include <string>

LevelRenderer::LevelRenderer() :
	m_camera(nullptr),
	m_tileSetSprite(nullptr),
	m_tileWidth(0),
	m_tileHeight(0),
	m_tileSetSpriteWidth(0),
	m_tileSetSpriteHeight(0),
	m_tileSetWidth(0)
{
}

LevelRenderer::~LevelRenderer()
{
	DeleteAll();
}

void LevelRenderer::Init(Graphics* graphics, Camera* camera)
{
	m_camera = camera;

	m_tilemapData = LoadTilemap("assets\\data\\tilemaps\\tm_bunker.json");
	m_tileSetSprite = new Sprite();

	m_tileSetSprite->Init(AssetLoader::GetTexture("ts_bunker"));
	m_tileSetSprite->SetOrigin(Vector2(0, 0));

	m_tileWidth = m_tilemapData.tilewidth;
	m_tileHeight = m_tilemapData.tileheight;
	m_tileSetSpriteWidth = m_tileSetSprite->GetWidth();
	m_tileSetSpriteHeight = m_tileSetSprite->GetHeight();
	m_tileSetWidth = m_tileSetSpriteWidth / m_tileWidth;
}

void LevelRenderer::Render(Graphics* graphics)
{
	auto numLayers = m_tilemapData.layers.size();
	auto layers = m_tilemapData.layers;

	for(auto i = layers.begin(); i != layers.end(); ++i)
	{
		RenderLayer(graphics, *i);
	}
}

TilemapData LevelRenderer::LoadTilemap(std::string path)
{
	Logger::LogInfo(fmt::format("Loading Tilemap Data: {}.", path));

	std::ifstream file(path);

	if(file.fail())
	{
		Logger::LogError(fmt::format("[AssetLoader] [Tilemap] Failed to load tile map at {0}.", path));
		return TilemapData();
	}

	json data = json::parse(file);
	TilemapData tilemapData = data.get<TilemapData>();
	return tilemapData;
}

void LevelRenderer::RenderLayer(Graphics* graphics, const TilemapLayer& layer)
{
	auto layerData = layer;
	auto tileMapWidth = m_tilemapData.width;
	auto tileMapHeight = m_tilemapData.height;

	for(size_t x = 0; x < tileMapWidth; x++)
	{
		for(size_t y = 0; y < tileMapHeight; y++)
		{
			auto tileId = layer.data[y * tileMapWidth + x] - 1;
			RenderTile(graphics, tileId, (unsigned int)x, (unsigned int)y);
		}
	}
}

void LevelRenderer::RenderTile(Graphics* graphics, unsigned int tileId, unsigned int posX, unsigned int posY)
{
	RECT rect {};
	rect.left = (tileId % m_tileSetWidth) * m_tileWidth;
	rect.right = rect.left + m_tileWidth;
	rect.top = (tileId / m_tileSetWidth) * m_tileHeight;
	rect.bottom = rect.top + m_tileHeight;

	Vector2 spritePosition = { (float)(posX * m_tileWidth), (float)(posY * m_tileHeight) };
	spritePosition.x -= m_camera->GetPosition().x;

	m_tileSetSprite->SetSourceRect(rect);
	m_tileSetSprite->SetPosition(spritePosition);
	m_tileSetSprite->Render(graphics);
}

void LevelRenderer::DeleteAll()
{
	delete m_tileSetSprite;

	m_tileSetSprite = nullptr;
}
