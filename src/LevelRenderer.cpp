#include "LevelRenderer.h"

#include "AssetLoader.h"
#include "Camera.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "Logger.h"
#include "Sprite.h"
#include "TilemapData.h"

#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <fstream>
#include <string>

using namespace GlobalConstants;

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

	//m_tilemapData = LoadTilemap("assets\\data\\tilemaps\\tm_trailer-level-showcase.json");
	m_tilemapData = LoadTilemap("assets\\data\\tilemaps\\tm_lift.json");
	m_tileSetSprite = new Sprite();

	m_tileSetSprite->Init(AssetLoader::GetTexture("ts_master"));
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
	auto tileMapWidth = m_tilemapData.width;
	auto tileMapHeight = m_tilemapData.height;
	auto parallaxMod = layer.parallaxMod;

	for(size_t x = 0; x < tileMapWidth; x++)
	{
		auto tileX = x * m_tileWidth;
		if(tileX < m_camera->GetPosition().x * parallaxMod - m_tileWidth) continue;
		if(tileX > m_camera->GetPosition().x * parallaxMod + GameWidth) continue;

		for(size_t y = 0; y < tileMapHeight; y++)
		{
			auto tileId = layer.data[y * tileMapWidth + x] - 1;
			RenderTile(graphics, tileId, (unsigned int)x, (unsigned int)y, parallaxMod, layer.depth);
		}
	}
}

void LevelRenderer::RenderTile(Graphics* graphics, unsigned int tileId, unsigned int posX, unsigned int posY, float parallaxMod, float depth)
{
	RECT rect {};
	rect.left = (tileId % m_tileSetWidth) * m_tileWidth;
	rect.right = rect.left + m_tileWidth;
	rect.top = (tileId / m_tileSetWidth) * m_tileHeight;
	rect.bottom = rect.top + m_tileHeight;

	Vector2 spritePosition = { (float)(posX * m_tileWidth), (float)(posY * m_tileHeight) };
	spritePosition -= m_camera->GetPosition() * parallaxMod;

	m_tileSetSprite->SetSourceRect(rect);
	m_tileSetSprite->SetPosition(spritePosition);
	m_tileSetSprite->SetDepth(depth);
	m_tileSetSprite->Render(graphics);
}

void LevelRenderer::DeleteAll()
{
	delete m_tileSetSprite;

	m_tileSetSprite = nullptr;
}
