#include "Camera.h"
#include "Graphics.h"
#include "LevelRenderer.h"
#include "Sprite.h"
#include "Texture.h"

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
	RECT rect;

	rect.left = 0;
	rect.right = m_tilemapHandler->GetTilemapData().tilewidth;
	rect.top = 0;
	rect.bottom = m_tilemapHandler->GetTilemapData().tileheight;

	//m_tileSetSprite->SetSourceRect(rect);
	m_tileSetSprite->Render(graphics, Vector2(0, 0));
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
