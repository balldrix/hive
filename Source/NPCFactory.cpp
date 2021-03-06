#include "NPCFactory.h"

#include "Animator.h"
#include "Enemy.h"
#include "Error.h"
#include "Sprite.h"
#include "Spritesheet.h"
#include "Texture.h"
#include "KingMook.h"
#include "KingMookEnemyGlobalState.h"
#include "MookEnemyGlobalState.h"
#include "EnemyOwnedStates.h"

using namespace InGameHudConstants;

NPCFactory::NPCFactory() :
    m_graphics(nullptr),
	m_camera(nullptr),
	m_player(nullptr),
	m_hudManager(nullptr),
	m_mookTexture(nullptr),
	m_kingMookTexture(nullptr),
	m_standardShadowTexture(nullptr),
	m_largeShadowTexture(nullptr),
	m_mookPortraitTexture(nullptr),
	m_kingMookPortraitTexture(nullptr),
	m_hitBoxTexture(nullptr),
	m_mookPortraitSprite(nullptr),
	m_kingMookPortraitSprite(nullptr),
    m_mook(nullptr),
	m_boss(nullptr)
{
}

NPCFactory::~NPCFactory()
{
    ReleaseAll();
    DeleteAll();
}

void NPCFactory::Init(Graphics* graphics, 
					  Camera* camera, 
					  Player* player, 
					  InGameHudManager* hudManager,
					  Texture* standardShadowTexture,
					  Texture* hitBoxTexture)
{
    m_graphics = graphics;
	m_camera = camera;
	m_player = player;
	m_hudManager = hudManager;
	m_standardShadowTexture = standardShadowTexture;

	m_mookTexture = new Texture();
	m_mookTexture->LoadTexture(m_graphics, "GameData\\Sprites\\mookSpritesheet.png");

	m_kingMookTexture = new Texture();
	m_kingMookTexture->LoadTexture(m_graphics, "GameData\\Sprites\\kingMookSpritesheet.png");

	m_largeShadowTexture = new Texture();
	m_largeShadowTexture->LoadTexture(m_graphics, "GameData\\Sprites\\shadow_large.png");

	m_mookPortraitTexture = new Texture();
	m_mookPortraitTexture->LoadTexture(m_graphics, "GameData\\Sprites\\UI\\mook_hud_portrait.png");

	m_kingMookPortraitTexture = new Texture();
	m_kingMookPortraitTexture->LoadTexture(m_graphics, "GameData\\Sprites\\UI\\kingMook_hud_portrait.png");

	m_mookPortraitSprite = new Sprite();
	m_mookPortraitSprite->Init(m_mookPortraitTexture);
	m_mookPortraitSprite->SetOrigin(Vector2::Zero);
	m_mookPortraitSprite->SetPosition(Vector2(EnemyPortraitPositionX, EnemyPortraitPositionY));

	m_kingMookPortraitSprite = new Sprite();
	m_kingMookPortraitSprite->Init(m_kingMookPortraitTexture);
	m_kingMookPortraitSprite->SetOrigin(Vector2::Zero);
	m_kingMookPortraitSprite->SetPosition(Vector2(EnemyPortraitPositionX, EnemyPortraitPositionY));

	m_hitBoxTexture = hitBoxTexture;
}

Enemy* NPCFactory::GetEnemy(EnemyData data)
{
	if(data.type == "Mook")
		return CreateMook(data);

	if(data.type == "Boss")
		return CreateBoss(data);

	return nullptr;
}

Enemy* NPCFactory::CreateMook(EnemyData& data)
{
	m_mook = new Enemy();
	m_mook->Init(m_graphics, m_camera, m_player, data,
				 m_mookTexture, m_standardShadowTexture,
				 m_hitBoxTexture,
				 m_hudManager, m_mookPortraitSprite,
				 MookEnemyGlobalState::Instance());

	return m_mook;
}

Enemy* NPCFactory::CreateBoss(EnemyData& data)
{
	m_boss = new KingMook();
	m_boss->Init(m_graphics, m_camera, m_player, data,
				 m_kingMookTexture, m_largeShadowTexture,
				 m_hitBoxTexture,
				 m_hudManager, m_kingMookPortraitSprite,
				 KingMookEnemyGlobalState::Instance());

	return m_boss;
}

void NPCFactory::ReleaseAll()
{
	if(m_mookTexture != nullptr) { m_mookTexture->Release(); }
	if(m_kingMookTexture != nullptr) { m_kingMookTexture->Release(); }
	if(m_largeShadowTexture != nullptr) { m_largeShadowTexture->Release(); }
	if(m_mookPortraitTexture != nullptr) { m_mookPortraitTexture->Release(); }
	if(m_kingMookPortraitTexture != nullptr) { m_kingMookPortraitTexture->Release(); }
}

void NPCFactory::DeleteAll()
{
	if(m_kingMookPortraitSprite != nullptr)
	{
		delete m_kingMookPortraitSprite;
		m_kingMookPortraitSprite = nullptr;
	}

	if(m_mookPortraitSprite != nullptr)
	{
		delete m_mookPortraitSprite;
		m_mookPortraitSprite = nullptr;
	}

	if(m_kingMookPortraitTexture != nullptr)
	{
		delete m_kingMookPortraitTexture;
		m_kingMookPortraitTexture = nullptr;
	}

	if(m_mookPortraitTexture != nullptr)
	{
		delete m_mookPortraitTexture;
		m_mookPortraitTexture = nullptr;
	}

	if(m_largeShadowTexture != nullptr)
	{
		delete m_largeShadowTexture;
		m_largeShadowTexture = nullptr;
	}

	if(m_kingMookTexture != nullptr)
	{
		delete m_kingMookTexture;
		m_kingMookTexture = nullptr;
	}

	if(m_mookTexture != nullptr)
	{
		delete m_mookTexture;
		m_mookTexture = nullptr;
	}
}