#include "Bullet.h"
#include "Resources.h"
#include "Constants.h"

Bullet::Bullet() :
m_pBulletTexture(NULL),
m_bulletState(STATIC),
m_active(false)
{
}

Bullet::~Bullet()
{

}

void
Bullet::Init(Graphics* graphics, Texture* texture)
{
	m_pGraphics = graphics;
	m_pBulletTexture = texture;
}

void
Bullet::Update(float deltaTime)
{
	if(m_active)
	{

	}
}

void
Bullet::Render()
{
	if (m_active)
	{

	}
}

void
Bullet::Reset()
{
	SetActive(false);
	SetBulletState(STATIC);
	//SetPosition(0.0f, 0.0f);
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
