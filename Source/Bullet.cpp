#include "Bullet.h"
#include "Resources.h"
#include "Constants.h"

Bullet::Bullet() :
AnimatedSprite(),
Transform(),
AABB(),
m_pBulletTexture(NULL),
m_bulletState(STATIC),
m_active(false)
{
}

Bullet::~Bullet()
{

}

void
Bullet::Init(Graphics* graphics, TextureManager* texture)
{
	m_pGraphics = graphics;
	m_pBulletTexture = texture;

	AnimatedSprite::Init(graphics, texture, NUM_BULLET_ANIM_FRAMES, BULLET_ANIM_FRAME_DELAY);

	m_currentMovementSpeed = BULLET_SPEED;
	m_loop = false;
}

void
Bullet::Update(float deltaTime)
{
	if(m_active)
	{
		AnimatedSprite::Update(deltaTime);
		AnimatedSprite::FlipSprite();
		Transform::Update(deltaTime);

		// set hit box position
		m_collisionBox.SetAABB(m_position, m_position + Vector2D(TILE_SIZE, TILE_SIZE));
	
		if (m_position.x > GAME_WIDTH ||
			m_position.x < 0)
		{
			m_active = false;
			SetAnimDone(false);
			SetCurrentFrame(0);
		}
	}
}

void
Bullet::Render()
{
	if (m_active)
	{
		Sprite::Render(m_position);

		// animated version not used yet
	//	Sprite::Render(m_position, GetRect());
	
		//if(m_showHitBox)
		//{
		//	RenderHitBox(m_collisionBox);
		//}
	}
}

void
Bullet::Reset()
{
	Transform::Reset();
	AnimatedSprite::Reset();

	SetActive(false);
	SetBulletState(STATIC);
	SetPosition(0.0f, 0.0f);
}

void 
Bullet::SetBulletState(BULLET_STATE state)
{
	m_bulletState = state;
}

void Bullet::SetActive(bool active)
{
	m_active = active;
}
