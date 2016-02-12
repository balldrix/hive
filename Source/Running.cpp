#include "Running.h"
#include "UnitVectors.h"
#include "Constants.h"
#include "Resources.h"

Running::Running(GameStateManager* gm) :
	m_pGM(gm),
	m_pGraphics(NULL),
	m_pInput(NULL),
	m_initialised(false),
	m_isPaused(false),
	m_canSpawnEnemy(false),
	m_showHitBoxes(false),
	m_enemySpawnDelay(0.0f),
	m_keyDownDelay(0.0f),
	m_enemySpawnPosition(0.0f, 0.0f),
	m_score(0),
	m_level(0),
	GameState("RUNNING")
{
	m_pGraphics = m_pGM->GetGraphics();
	m_pInput = m_pGM->GetInput();
}

Running::~Running()
{
}

void
Running::OnEntry()
{
	LoadAssets();
	m_initialised = true;
}

void
Running::OnExit()
{
	DeleteAssets();
}

void
Running::LoadAssets()
{

	m_playerTexture.Init(m_pGraphics, PLAYER);
	//m_bulletTexture.Init(m_pGraphics, "Bullet");
	//m_enemyTexture.Init(m_pGraphics, "ENEMY");
	
	m_player.Init(m_pGraphics, &m_playerTexture);

	//for(int index = 0; index < MAX_ENEMY; index++)
	//{
	//	m_pEnemy[index].Init(m_pEnemySprite);
	//}

	NewGame();
}

void
Running::DeleteAssets()
{
}

void
Running::CheckInput()
{

	///////////////////////////////////////////
	// check if key is released
	///////////////////////////////////////////

	if(!m_pInput->IsKeyDown(PLAYER_UP_KEY))
	{
		// move player up
		m_player.SetTargetVelocityY(0.0f);
		m_keyPressed = false;
	}
	else if(!m_pInput->IsKeyDown(PLAYER_DOWN_KEY))
	{
		// move player down
		m_player.SetTargetVelocityY(0.0f);
		m_keyPressed = false;
	}

	if(!m_pInput->IsKeyDown(PLAYER_RIGHT_KEY))
	{
		// move player right
		m_player.SetTargetVelocityX(0.0f);

		m_keyPressed = false;
	}
	else if(!m_pInput->IsKeyDown(PLAYER_LEFT_KEY))
	{
		// move player left
		m_player.SetTargetVelocityX(0.0f);
		m_keyPressed = false;
	}

	if(!m_keyPressed)
	{
		// if player is active, allow movement with input

		///////////////////////////////////////////
		// check if key is pressed down
		///////////////////////////////////////////

		// button A to shoot (binding set to X key)
		if(m_pInput->IsKeyDown(PLAYER_A_KEY))
		{
			m_player.Shoot();
			m_player.SetIsStrafe(true);
			m_keyPressed = true;
		}
		else
		{
			m_player.SetIsStrafe(false);
		}

		if(m_pInput->IsKeyDown(PLAYER_UP_KEY))
		{
			if(m_pInput->IsKeyDown(PLAYER_RIGHT_KEY))
			{
				// move player up right
				m_player.SetTargetVelocity(directionNS::UPRIGHT);
				
				// if strafing don't change facing direction
				if(!m_player.GetIsStrafe())
				{
					m_player.SetFacingDirection(FACING_DIRECTION::RIGHT);
				}
			}
			else if(m_pInput->IsKeyDown(PLAYER_LEFT_KEY))
			{
				// move player up left
				m_player.SetTargetVelocity(directionNS::UPLEFT);

				// if strafing don't change facing direction
				if(!m_player.GetIsStrafe())
				{
					m_player.SetFacingDirection(FACING_DIRECTION::LEFT);
				}
			}
			else
			{
				// move player up
				m_player.SetTargetVelocity(directionNS::UP);
			}
			m_keyPressed = true;
		}
		else if(m_pInput->IsKeyDown(PLAYER_DOWN_KEY))
		{
			if(m_pInput->IsKeyDown(PLAYER_RIGHT_KEY))
			{
				// move player down right
				m_player.SetTargetVelocity(directionNS::DOWNRIGHT);

				// if strafing don't change facing direction
				if(!m_player.GetIsStrafe())
				{
					m_player.SetFacingDirection(FACING_DIRECTION::RIGHT);
				}
			}
			else if(m_pInput->IsKeyDown(PLAYER_LEFT_KEY))
			{
				// move player down left
				m_player.SetTargetVelocity(directionNS::DOWNLEFT);

				// if strafing don't change facing direction
				if(!m_player.GetIsStrafe())
				{
					m_player.SetFacingDirection(FACING_DIRECTION::LEFT);
				}
			}
			else
			{
				// move player down
				m_player.SetTargetVelocity(directionNS::DOWN);
			}
			m_keyPressed = true;
		}
		else if(m_pInput->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			if(m_pInput->IsKeyDown(PLAYER_UP_KEY))
			{
				// move player up right
				m_player.SetTargetVelocity(directionNS::UPRIGHT);
			}
			else if(m_pInput->IsKeyDown(PLAYER_DOWN_KEY))
			{
				// move player down right
				m_player.SetTargetVelocity(directionNS::DOWNRIGHT);
			}
			else
			{
				// move player right
				m_player.SetTargetVelocity(directionNS::RIGHT);
			}

			// if strafing don't change facing direction
			if(!m_player.GetIsStrafe())
			{
				m_player.SetFacingDirection(FACING_DIRECTION::RIGHT);
			}

			m_keyPressed = true;
		}
		else if(m_pInput->IsKeyDown(PLAYER_LEFT_KEY))
		{
			if(m_pInput->IsKeyDown(PLAYER_UP_KEY))
			{
				// move player up left
				m_player.SetTargetVelocity(directionNS::UPLEFT);
			}
			else if(m_pInput->IsKeyDown(PLAYER_DOWN_KEY))
			{
				// move player down left
				m_player.SetTargetVelocity(directionNS::DOWNLEFT);
			}
			else
			{
				// move player left
				m_player.SetTargetVelocity(directionNS::LEFT);
			}

			// if strafing don't change facing direction
			if(!m_player.GetIsStrafe())
			{
				m_player.SetFacingDirection(FACING_DIRECTION::LEFT);
			}

			m_keyPressed = true;
		}

		// use shift to run
		if(m_pInput->IsKeyDown(SHIFT_PRESSED))
		{
			m_player.SetTargetMovementSpeed(PLAYER_RUN_SPEED);
			m_keyPressed = true;
		}
		else
		{
			m_player.SetTargetMovementSpeed(PLAYER_WALK_SPEED);
		}

		// button B to melee attack (binding set to Z key)
		if(m_pInput->IsKeyDown(PLAYER_B_KEY))
		{
			// melee attack
			m_player.Melee();
			m_keyPressed = true;
		}

		//set key to debug hit boxes
		if(m_pInput->WasKeyPressed(F4_KEY))
		{
			// switch visible hitboxes on or off
			SetRenderHitBoxes();

			m_keyPressed = true;
		}

		if(m_pInput->WasKeyPressed('R'))
		{
			// reset game
			NewGame();
			m_keyPressed = true;
		}
	}

	if(!(m_pInput->IsKeyDown(PLAYER_UP_KEY) ||
	   m_pInput->IsKeyDown(PLAYER_DOWN_KEY) ||
	   m_pInput->IsKeyDown(PLAYER_LEFT_KEY) ||
	   m_pInput->IsKeyDown(PLAYER_RIGHT_KEY) ||
	   m_pInput->IsKeyDown(PLAYER_A_KEY) ||
	   m_pInput->IsKeyDown(PLAYER_B_KEY) ||
	   m_pInput->IsKeyDown(ENTER_KEY) ||
	   m_pInput->IsKeyDown(F4_KEY)
	   ))
	{
		m_keyPressed = false;
	}
}

void
Running::Update(float deltaTime)
{
	if(!m_initialised)
	{
		return;
	}

	CheckInput();

	if(!m_isPaused)
	{
		m_player.Update(deltaTime);

		//for(int index = 0; index < MAX_ENEMY; index++)
		//{
		//	if(m_pEnemy[index].IsActive())
		//	{
		//		m_pEnemy[index].Update(deltaTime);
		//	}
		//}

		CheckCollisions();
	}

	if(m_keyDownDelay < 0)
	{
		m_keyDownDelay = KEY_DELAY;
		m_keyPressed = false;
	}

	m_keyDownDelay -= deltaTime;
}

void
Running::Render()
{
	m_pGraphics->SpriteBegin();
	//for(int index = 0; index < MAX_ENEMY; index++)
	//{
	//	if(m_pEnemy[index].IsActive())
	//	{
	//		m_pEnemy[index].Render();
	//	}
	//}
	m_player.Render();
	m_pGraphics->SpriteEnd();
}

void
Running::NewGame()
{
	m_score = 0;
	m_level = 0;
	//m_enemySpawnDelay = ENEMY_SPAWN_DELAY;
	ResetAll();
	SpawnEnemy();
}

void
Running::ResetAll()
{
	srand((int)time(NULL));

	m_player.Reset();

	//for(int index = 0; index < MAX_ENEMY; index++)
	//{
	//	m_pEnemy[index].Reset();
	//}
}

void
Running::SpawnEnemy()
{
/*
	// loop through enemy array
	for(int index = 0; index < MAX_ENEMY - 1; index++)
	{
		// loop through remaining array
		for(int j = index; j < MAX_ENEMY; j++)
		{
			// no point checking against itself
			if(index != j)
			{	// loop while there is a collision
				while(m_pEnemy[index].GetAABB().Collision(m_pEnemy[j].GetAABB()))
				{
					m_enemySpawnPosition = SetSpawnLocation();
					m_pEnemy[j].SetPosition(m_enemySpawnPosition);
					m_pEnemy[j].SetCollisionBox(m_enemySpawnPosition, Vector2D(m_enemySpawnPosition.x + TILE_SIZE, m_enemySpawnPosition.y + TILE_SIZE));

				}
			}
		}
		// set spawned enemy to active
		m_pEnemy[index].SetActive(true);
	}
*/
}

Vector2D
Running::SetSpawnLocation()
{
	// create x and y position vars
	unsigned int xPos = 0;
	unsigned int yPos = 0;

	do
	{
		xPos = Randomiser::GetRandNum(ENEMY_SPAWN__AREA1_MIN_X, ENEMY_SPAWN__AREA2_MAX_X);
	} while((xPos > ENEMY_SPAWN__AREA1_MAX_X) &&
			(xPos < ENEMY_SPAWN__AREA2_MIN_X));

	do
	{
		yPos = Randomiser::GetRandNum(ENEMY_SPAWN__AREA1_MIN_Y, ENEMY_SPAWN__AREA2_MAX_Y);
	} while((yPos > ENEMY_SPAWN__AREA1_MAX_Y) &&
			(yPos < ENEMY_SPAWN__AREA2_MIN_Y));

	return Vector2D(xPos, yPos);
}

void
Running::CheckCollisions()
{
	////////////////////////////////////
	// check collisions with enemy
	////////////////////////////////////
	/*
	for(int i = 0; i < MAX_ENEMY; i++)
	{
		if(m_pEnemy[i].IsActive())
		{
			////////////////////////////////////
			// check collision with bullets
			////////////////////////////////////
			for(int j = 0; j < MAX_BULLETS_ON_SCREEN; j++)
			{

				if(m_player.m_bullets[j].IsActive())
				{
					if(m_pEnemy[i].GetAABB().Collision(m_player.m_bullets[j].GetAABB()))
					{
						//// Kill enemy
						//// enemy death anim

						m_pEnemy[i].SetEnemyState(Enemy::ENEMY_STATE::ENEMY_STATE_DEATH);  // must add death anim/sprites later

						//// remove bullet
						m_player.m_bullets[j].SetActive(false);
						m_player.m_bullets[j].SetCurrentAnimFrame(0);
						m_player.m_bullets[j].SetAnimDone(false);

						//// add score
						AddScore(15);
						break;
					}
				}
			}

			////////////////////////////////////
			// check collision with player melee attack
			////////////////////////////////////
			if(m_player.GetIsMelee())
			{
				if(m_pEnemy[i].GetAABB().Collision(m_player.GetMeleeAABB()))
				{
					// Kill enemy
					// enemy death anim

					m_pEnemy[i].SetEnemyState(Enemy::ENEMY_STATE::ENEMY_STATE_DEATH);  // must add death anim/sprites later

					m_player.SetIsMelee(false);
					// add score
					AddScore(15);
				}
			}
		}
	}
	*/

	////////////////////////////////////
	////////////////////////////////////
}

void
Running::AddScore(unsigned int score)
{
	m_score += score;
}

void Running::SetRenderHitBoxes()
{
	//toggle show/hide player hit boxes
	if(m_player.GetShowHitBox())
	{
		m_player.SetShowHitBox(false);
	}
	else
	{
		m_player.SetShowHitBox(true);
	}

	//toggle show/hide enemy hit boxes
	/*
	for(int index = 0; index < MAX_ENEMY; index++)
	{
		if(m_pEnemy[index].GetShowHitBox())
		{
			m_pEnemy[index].SetShowHitBox(false);
		}
		else
		{
			m_pEnemy[index].SetShowHitBox(true);
		}
	}

	//toggle show/hide bullet hit boxes
	for(int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
	{
		if(m_player.m_bullets[index].GetShowHitBox())
		{
			m_player.m_bullets[index].SetShowHitBox(false);
		}
		else
		{
			m_player.m_bullets[index].SetShowHitBox(true);
		}
	}
	*/
}
