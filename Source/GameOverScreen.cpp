#include "GameOverScreen.h"

#include "Texture.h"
#include "Animator.h"
#include "SpriteSheet.h"

GameOverScreen::GameOverScreen() :
	m_animator(nullptr),
	m_texture(nullptr),
	m_spriteSheet(nullptr),
	m_isActive(false)
{
}

GameOverScreen::~GameOverScreen()
{
	DeleteAll();
}

void GameOverScreen::Init(Graphics* graphics, Animator* animator, std::string texturePath)
{
	m_animator = animator;

	m_texture = new Texture();
	m_texture->LoadTexture(graphics, texturePath);

	m_spriteSheet = new Spritesheet();
	m_spriteSheet->Init(m_texture, "GameData\\SpriteSheetData\\gameOverSpritesheetData.json");
}

void GameOverScreen::Update(float deltaTime)
{
	if(m_isActive == true)
		m_animator->Update(deltaTime);
}

void GameOverScreen::Render(Graphics* graphics)
{
	if(m_isActive == true)
		m_spriteSheet->Render(graphics, m_animator->GetCurrentFrame());
}

void GameOverScreen::Release()
{
	if(m_texture != nullptr) m_texture->Release();
}

void GameOverScreen::Reset()
{
	m_isActive = false;
}

void GameOverScreen::DeleteAll()
{
	if(m_spriteSheet != nullptr)
	{
		delete m_spriteSheet;
		m_spriteSheet = nullptr;
	}

	if(m_texture != nullptr)
	{
		delete m_texture;
		m_texture = nullptr;
	}
}