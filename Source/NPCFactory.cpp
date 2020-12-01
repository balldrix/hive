#include "NPCFactory.h"

#include "Animator.h"
#include "Enemy.h"
#include "Error.h"
#include "Sprite.h"
#include "Spritesheet.h"
#include "Texture.h"

using namespace InGameHudConstants;

NPCFactory::NPCFactory() :
    m_graphics(nullptr),
	m_camera(nullptr),
	m_player(nullptr),
	m_hudManager(nullptr),
	m_mookTexture(nullptr),
	m_standardShadowTexture(nullptr),
	m_mookPortraitTexture(nullptr),
	m_hitBoxTexture(nullptr),
	m_mookPortraitSprite(nullptr),
    m_mook(nullptr)
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
	m_mookTexture->LoadTexture(m_graphics, "GameData\\Sprites\\enemySpritesheet.png");

	m_mookPortraitTexture = new Texture();
	m_mookPortraitTexture->LoadTexture(m_graphics, "GameData\\Sprites\\UI\\mook_hud_portrait.png");

	m_mookPortraitSprite = new Sprite();
	m_mookPortraitSprite->Init(m_mookPortraitTexture);
	m_mookPortraitSprite->SetOrigin(Vector2::Zero);
	m_mookPortraitSprite->SetPosition(Vector2(EnemyPortraitPositionX, EnemyPortraitPositionY));

	m_hitBoxTexture = hitBoxTexture;
}

Enemy* NPCFactory::GetEnemy(EnemyData data)
{
    m_mook = new Enemy();
	m_mook->SetData(data);
	m_mook->SetPlayerTarget(m_player);
	m_mook->Init(m_graphics, data.objectData.startingPosition, 
				 m_mookTexture, m_standardShadowTexture,
				 m_hitBoxTexture,
				 m_hudManager, m_mookPortraitSprite);

	std::string type = m_mook->GetData().type;
	std::string enemyDataFile = "GameData\\EnemyData\\Damage\\" + type + "Damage.txt";

	if(!m_mook->LoadDamageData(enemyDataFile))
	{
		std::string error = "Error! Enemy damage data " + enemyDataFile + " not found.";
		Error::FileLog(error);
	}

	m_mook->SetCamera(m_camera);
	m_mook->SetActive(false);

    return m_mook;
}

void NPCFactory::ReleaseAll()
{
	if(m_mookTexture != nullptr) { m_mookTexture->Release(); }
	if(m_mookPortraitTexture != nullptr) { m_mookPortraitTexture->Release(); }
}

void NPCFactory::DeleteAll()
{
	if(m_mookPortraitSprite != nullptr)
	{
		delete m_mookPortraitSprite;
		m_mookPortraitSprite = nullptr;
	}

	if(m_mookPortraitTexture != nullptr)
	{
		delete m_mookPortraitTexture;
		m_mookPortraitTexture = nullptr;
	}

	if(m_mookTexture != nullptr)
	{
		delete m_mookTexture;
		m_mookTexture = nullptr;
	}
}