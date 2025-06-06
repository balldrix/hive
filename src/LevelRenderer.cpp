#define NOMINMAX

#include "LevelRenderer.h"

#include "AssetLoader.h"
#include "Camera.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "Logger.h"
#include "Sprite.h"
#include "TilemapData.h"

#include "TilemapLoader.h"
#include <cmath>
#include <cstdlib>
#include <directxtk/SimpleMath.h>
#include <utility>
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

	m_tilemapData = TilemapLoader::GetCurrentMap();
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
		if(i->data.size() == 0) continue;

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

void LevelRenderer::RenderLayer(Graphics* graphics, const TilemapLayer& layer)
{
	auto tileMapWidth = m_tilemapData.width;
	auto tileMapHeight = m_tilemapData.height;
	auto parallaxMod = layer.parallaxMod;
	auto scrollOffset = layer.scrollOffset;

	Vector2 cameraPos = m_camera->GetPosition() * parallaxMod;

	int startX = std::max(0, (int)(cameraPos.x / m_tileWidth) - 1);
	int endX = std::min(tileMapWidth, startX + (GameWidth / m_tileWidth) + 2);

	int startY = std::max(0, (int)(cameraPos.y / m_tileHeight) - 1);
	int endY = std::min(tileMapHeight, startY + (GameHeight / m_tileHeight) + 2);

	for(int x = startX; x < endX; x++)
	{
		int wrappedX = (x + (int)(scrollOffset.x / m_tileWidth)) % tileMapWidth;
		if(wrappedX < 0) wrappedX += tileMapWidth;

		float tileXPos = x * m_tileWidth - (float)fmod(scrollOffset.x, m_tileWidth);

		for(int y = startY; y < endY; y++)
		{
			int wrappedY = (y + (int)(scrollOffset.y / m_tileHeight)) % tileMapHeight;
			if(wrappedY < 0) wrappedY += tileMapHeight;

			float tileYPos = y * m_tileHeight - (float)fmod(scrollOffset.y, m_tileHeight);

			auto tileId = layer.data[wrappedY * tileMapWidth + wrappedX] - 1;
			RenderTile(graphics, tileId, tileXPos, tileYPos, parallaxMod, layer.depth, layer.opacity);
		}
	}
}

void LevelRenderer::RenderTile(Graphics* graphics, unsigned int tileId, float posX, float posY, float parallaxMod, float depth, float alpha)
{
	RECT rect {};
	rect.left = (tileId % m_tileSetWidth) * m_tileWidth;
	rect.right = rect.left + m_tileWidth;
	rect.top = (tileId / m_tileSetWidth) * m_tileHeight;
	rect.bottom = rect.top + m_tileHeight;

	Vector2 spritePosition = { posX - m_camera->GetPosition().x * parallaxMod, posY - m_camera->GetPosition().y };

	m_tileSetSprite->SetSourceRect(rect);
	m_tileSetSprite->SetPosition(spritePosition);
	m_tileSetSprite->SetDepth(depth);
	m_tileSetSprite->SetAlpha(alpha);
	m_tileSetSprite->Render(graphics);
}

void LevelRenderer::DeleteAll()
{
	delete m_tileSetSprite;

	m_tileSetSprite = nullptr;
}
