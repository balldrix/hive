#include "NPCFactory.h"

#include "Animator.h"
#include "Enemy.h"
#include "Error.h"
#include "Sprite.h"
#include "Spritesheet.h"
#include "Texture.h"
#include "KingMook.h"
#include "KingMookEnemyGlobalState.h"
#include "MookRunningEnemyGlobalState.h"
#include "MookEnemyGlobalState.h"
#include "EnemyOwnedStates.h"
#include "InGameHudConstants.h"

using namespace InGameHudConstants;

NPCFactory::NPCFactory() :
	m_graphics(nullptr),
	m_camera(nullptr),
	m_player(nullptr),
	m_hudManager(nullptr),
	m_mookTexture(nullptr),
	m_kingMookTexture(nullptr),
	m_standardShadowTexture(nullptr),
	m_mookPortraitTexture(nullptr),
	m_kingMookPortraitTexture(nullptr),
	m_hitBoxTexture(nullptr),
	m_mookPortraitSprite(nullptr),
	m_kingMookPortraitSprite(nullptr)
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

	if (data.type == "MookRunner")
		return CreateMookRunner(data);

	if(data.type == "Boss")
		return CreateBoss(data);

	return nullptr;
}

Enemy* NPCFactory::CreateMook(EnemyData& data)
{
	auto mook = new Enemy();
	mook->Init(m_graphics, m_camera, m_player, data,
				m_mookTexture, m_standardShadowTexture,
				m_hitBoxTexture,
				m_hudManager, m_mookPortraitSprite,
				MookEnemyGlobalState::Instance(),
				EnemyIdleState::Instance());

	return mook;
}

Enemy* NPCFactory::CreateMookRunner(EnemyData& data)
{
	auto mook = new Enemy();
	mook->Init(m_graphics, m_camera, m_player, data,
				m_mookTexture, m_standardShadowTexture,
				m_hitBoxTexture,
				m_hudManager, m_mookPortraitSprite,
				MookRunningEnemyGlobalState::Instance(),
				EnemyRunningState::Instance());

	return mook;
}

Enemy* NPCFactory::CreateBoss(EnemyData& data)
{
	auto boss = new KingMook();
	boss->Init(m_graphics, m_camera, m_player, data,
				m_kingMookTexture, m_standardShadowTexture,
				m_hitBoxTexture,
				m_hudManager, m_kingMookPortraitSprite,
				KingMookEnemyGlobalState::Instance(),
				EnemyIdleState::Instance());

	return boss;
}

void NPCFactory::ReleaseAll()
{
	if(m_mookTexture != nullptr) { m_mookTexture->Release(); }
	if(m_kingMookTexture != nullptr) { m_kingMookTexture->Release(); }
	if(m_mookPortraitTexture != nullptr) { m_mookPortraitTexture->Release(); }
	if(m_kingMookPortraitTexture != nullptr) { m_kingMookPortraitTexture->Release(); }
}

void NPCFactory::DeleteAll()
{
		delete m_kingMookPortraitSprite;
		delete m_mookPortraitSprite;
		delete m_kingMookPortraitTexture;
		delete m_mookPortraitTexture;
		delete m_kingMookTexture;
		delete m_mookTexture;

		m_kingMookPortraitSprite = nullptr;
		m_mookPortraitSprite = nullptr;
		m_kingMookPortraitTexture = nullptr;
		m_mookPortraitTexture = nullptr;
		m_kingMookTexture = nullptr;
		m_mookTexture = nullptr;
}