#include "Camera.h"
#include "Graphics.h"
#include "LevelRenderer.h"
#include "Sprite.h"
#include "Texture.h"
#include "TilemapHandler.h"
#include "TilemapData.h"

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

	m_tileWidth = m_tilemapHandler->GetTilemapData().tilewidth;
	m_tileHeight = m_tilemapHandler->GetTilemapData().tileheight;
	m_tileSetSpriteWidth = m_tileSetSprite->GetWidth();
	m_tileSetSpriteHeight = m_tileSetSprite->GetHeight();
	m_tileSetWidth = m_tileSetSpriteWidth / m_tileWidth;
}

void LevelRenderer::Update(float deltaTime)
{
}

void LevelRenderer::Render(Graphics* graphics)
{
	auto numLayers = m_tilemapHandler->GetTilemapData().layers.size();
	auto layers = m_tilemapHandler->GetTilemapData().layers;

	for(auto i = layers.begin(); i != layers.end(); ++i)
	{
		RenderLayer(graphics, *i);
	}
}

void LevelRenderer::RenderLayer(Graphics* graphics, const TilemapLayer& layer)
{
	auto layerData = layer;
	auto tileMapWidth = m_tilemapHandler->GetTilemapData().width;
	auto tileMapHeight = m_tilemapHandler->GetTilemapData().height;

	for(size_t x = 0; x < tileMapWidth; x++)
	{
		for(size_t y = 0; y < tileMapHeight; y++)
		{
			auto tileId = layer.data[y * tileMapWidth + x] - 1;
			RenderTile(graphics, tileId, x, y);
		}
	}
}

void LevelRenderer::RenderTile(Graphics* graphics, unsigned int tileId, unsigned int posX, unsigned int posY)
{
	RECT rect;

	rect.left = (tileId % m_tileSetWidth) * m_tileWidth;
	rect.right = rect.left + m_tileWidth;
	rect.top = (tileId / m_tileSetWidth) * m_tileHeight;
	rect.bottom = rect.top + m_tileHeight;

	m_tileSetSprite->SetSourceRect(rect);
	m_tileSetSprite->Render(graphics, Vector2(posX * m_tileWidth, posY * m_tileHeight));
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
