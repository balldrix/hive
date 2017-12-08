#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "pch.h"
#include "GameObject.h"

// forward declarations
class Sprite;

// player constants
const unsigned int		PLAYER_ANIM_NUM_FRAMES		= 1;
const float				PLAYER_ANIM_FRAME_DELAY		= 0.3f;
const unsigned int		PLAYER_ANIM_FRAME_WIDTH		= 32;
const unsigned int		PLAYER_ANIM_FRAME_HEIGHT	= 32;
const float				START_X						= 300;
const float				START_Y						= 300;
const unsigned int		PLAYER_WALK_SPEED			= 128;
const unsigned int		PLAYER_RUN_SPEED			= 256;
const unsigned int		MAX_BULLETS_ON_SCREEN		= 64;
const float				SHOOTING_DELAY				= 0.2f;
const float				MELEE_DELAY					= 0.6f;
const float				PLAYER_KICKBACK				= 2.5f;

class Player : public GameObject
{
public:

	// player states
	enum PlayerState
	{
		IDLE = 0,
		WALKING,
		RUNNING,
		SHOOTING,
		MELEE,
		HIT_STUN,
		BLOCK_STUN,
		MAX_PLAYER_STATES
	};

	Player();
	virtual ~Player();

	void				Init(Sprite* sprite, Vector2 position);
	void				Update(float deltaTime);
	void				Render(Graphics* graphics);
	void				Reset();
						
	void				SetPlayerState(PlayerState state);
	PlayerState			GetState()				const { return m_playerState; }

private:
	Sprite*				m_sprite;						// player sprite sheet
	PlayerState			m_playerState;						// player states for state machine
};

#endif _PLAYER_H_