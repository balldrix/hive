#include "Camera.h"
#include "Graphics.h"
#include "LevelRenderer.h"
#include "Sprite.h"
#include "Texture.h"
#include "TilemapHandler.h"

LevelRenderer::LevelRenderer() :
	m_camera(nullptr),
	m_tilemapHandler(nullptr),
	m_tileSetTexture(nullptr),
	m_tileSetSprite(nullptr)
{
}

LevelRenderer::~LevelRenderer()
{
	DeleteAll();
}

void LevelRenderer::Init(Graphics* graphics, Camera* camera)
{
	m_camera = camera;
	
	m_tilemapHandler = new TilemapHandler();
	m_tileSetTexture = new Texture();
	m_tileSetSprite = new Sprite();

	m_tilemapHandler->LoadTilemap("GameData\\Tilemaps\\tm_bunker.json");
	m_tileSetTexture->LoadTexture(graphics, "GameData\\Tilesets\\ts_bunker.png");
	m_tileSetSprite->Init(m_tileSetTexture);
	m_tileSetSprite->SetOrigin(Vector2(0, 0));
}

void LevelRenderer::Update(float deltaTime)
{
}

void LevelRenderer::Render(Graphics* graphics)
{
	auto mapWidth = m_tilemapHandler->GetTilemapData().width;
	auto mapHeight = m_tilemapHandler->GetTilemapData().height;

	for(size_t x = 0; x < mapWidth; x++)
	{
		for(size_t y = 0; y < mapHeight; y++)
		{
			RenderTile(graphics, x, y);
		}
	}
}

void LevelRenderer::RenderTile(Graphics* graphics, unsigned int posX, unsigned int posY)
{
	auto layerData = m_tilemapHandler->GetTilemapData().layers[0].data;
	auto tileMapWidth = m_tilemapHandler->GetTilemapData().width;
	auto tileWidth = m_tilemapHandler->GetTilemapData().tilewidth;
	auto tileHeight = m_tilemapHandler->GetTilemapData().tileheight;
	auto tileValue = layerData[posY * tileMapWidth + posX] - 1;
	auto spriteWidth = m_tileSetSprite->GetWidth();
	auto spriteHeight = m_tileSetSprite->GetHeight();
	
	auto tileSetWidth = spriteWidth / tileWidth;

	RECT rect;

	rect.left = (tileValue % tileSetWidth) * tileWidth;
	rect.right = rect.left + tileWidth;
	rect.top = (tileValue / tileSetWidth) * tileHeight;
	rect.bottom = rect.top + tileHeight;

	m_tileSetSprite->SetSourceRect(rect);
	m_tileSetSprite->Render(graphics, Vector2(posX * tileWidth, posY * tileHeight));
}

void LevelRenderer::DeleteAll()
{
	delete m_tileSetSprite;
	delete m_tileSetTexture;
	delete m_tilemapHandler;

	m_tileSetSprite = nullptr;
	m_tileSetTexture = nullptr;
	m_tilemapHandler = nullptr;
}
