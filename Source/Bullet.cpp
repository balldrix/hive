#include "Bullet.h"
#include "Resources.h"
#include "Constants.h"

Bullet::Bullet() :
AnimatedSprite(),
Transform(),
AABB(),
m_pBulletTexture(NULL),
m_bulletState(STATIC)
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

	AnimatedSprite::Init(graphics, texture, "Bullet", BULLET, NUM_BULLET_ANIM_FRAMES, BULLET_ANIM_FRAME_DELAY);

	m_currentMovementSpeed = BULLET_SPEED;
}

void
Bullet::Update(float deltaTime)
{
	//FlipSprite(m_pBulletSprite, m_facingDirection);
		
	// set hit box position
	//m_collisionBox.SetAABB(m_position, m_position + Vector2D(TILE_SIZE, TILE_SIZE));
	

	//if (m_position.x > GAME_WIDTH ||
	//	m_position.x < 0)
	//{
	//	m_active = false;
	//	m_pBulletSprite->SetAnimDone(false);
	//	m_pBulletSprite->SetCurrentFrame(0);
	//}
}

void
Bullet::Render()
{
	//if (m_active)
	//{
	//	m_pBulletSprite->Render(D3DXVECTOR2(m_position.x, m_position.y));

	//	// animated version not used yet
	//	//m_pBulletSprite->Render(D3DXVECTOR3(m_position.x, m_position.y, 0.0f), m_pBulletSprite->GetRect());
	//
	//	if(m_showHitBox)
	//	{
	//		DrawHitBox(m_pBulletSprite, m_collisionBox);
	//	}
	//}
}


void
Bullet::Reset()
{
	SetBulletState(STATIC);
	//SetPosition(0.0f, 0.0f);
}

void 
Bullet::SetBulletState(BULLET_STATE state)
{
	m_bulletState = state;
}