#include "LevelRenderer.h"

#include "AnimationData.h"
#include "AssetLoader.h"
#include "Camera.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "Logger.h"
#include "Sprite.h"
#include "TilemapData.h"

#include <cmath>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <fstream>
#include <iosfwd>
#include <string>
#include <Windows.h>

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

	Logger::LogInfo("Initialised LevelRenderer");
}

void LevelRenderer::Render(Graphics* graphics)
{
	auto numLayers = m_tilemapData.layers.size();
	auto &layers = m_tilemapData.layers;

	for(auto i = layers.begin(); i != layers.end(); ++i)
	{
		RenderLayer(graphics, *i);
	}
}

void LevelRenderer::Update(float deltaTime)
{
	for(auto it = m_tilemapData.layers.begin(); it != m_tilemapData.layers.end(); ++it)
	{
		if(std::abs(it->scrollSpeedX) > 0)
		{
			it->scrollOffset.x += it->scrollSpeedX * deltaTime;

			if(it->scrollOffset.x > m_tileWidth * it->width)
			{
				it->scrollOffset.x -= m_tileWidth * it->width;
			}
			else if(it->scrollOffset.x < 0)
			{
				it->scrollOffset.x += m_tileWidth * it->width;
			}
		}
		
		if(std::abs(it->scrollSpeedY) > 0)
		{
			it->scrollOffset.y += it->scrollSpeedY * deltaTime;

			if(it->scrollOffset.y > m_tileWidth * it->height)
			{
				it->scrollOffset.y -= m_tileWidth * it->height;
			}
			else if(it->scrollOffset.y < 0)
			{
				it->scrollOffset.y += m_tileWidth * it->height;
			}
		}
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
	auto scrollOffset = layer.scrollOffset;

	for(size_t x = 0; x < GameWidth / m_tileWidth + 2; x++)
	{
		int wrappedX = (x - (int)(scrollOffset.x / m_tileWidth)) % tileMapWidth;
		
		if(wrappedX < 0) wrappedX += tileMapWidth;
		if(wrappedX >= tileMapWidth) wrappedX -= tileMapWidth;
		
		float tileXPos = x * m_tileWidth - scrollOffset.x;

		for(size_t y = 0; y < GameHeight / m_tileHeight + 2; y++)
		{
			int wrappedY = (y - (int)(scrollOffset.y / m_tileHeight)) % tileMapHeight;
			if(wrappedY < 0) wrappedY += tileMapHeight;
			if(wrappedY >= tileMapHeight) wrappedY -= tileMapHeight;

			float tileYPos = y * m_tileHeight - scrollOffset.y;

			auto tileId = layer.data[wrappedY * tileMapWidth + wrappedX] - 1;
			RenderTile(graphics, tileId, tileXPos, tileYPos, parallaxMod, layer.depth);
		}
	}
}

void LevelRenderer::RenderTile(Graphics* graphics, unsigned int tileId, float posX, float posY, float parallaxMod, float depth)
{
	RECT rect {};
	rect.left = (tileId % m_tileSetWidth) * m_tileWidth;
	rect.right = rect.left + m_tileWidth;
	rect.top = (tileId / m_tileSetWidth) * m_tileHeight;
	rect.bottom = rect.top + m_tileHeight;

	Vector2 spritePosition = { posX, posY };
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
