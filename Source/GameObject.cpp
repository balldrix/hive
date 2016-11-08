#include "GameObject.h"
#include "Sprite.h"

GameObject::GameObject() :
	m_ID(L"GameObject"),
	m_sprite(nullptr),
	m_position(0.0f, 0.0f),
	m_hitbox(AABB(Vector2(0.0f,0.0f), Vector2(0.0f, 0.0f))),
	m_active(false)
{
}

GameObject::~GameObject()
{
}

void
GameObject::Init(Sprite* sprite, 
				 Vector2 position)
{
	// set member variables with passed params
	m_sprite = sprite;
	m_position = position;
	m_hitbox.SetAABB(Vector2(0.0f, 0.0f), Vector2(m_sprite->GetWidth(), m_sprite->GetHeight()));
}

void
GameObject::SetID(const wchar_t* string)
{
	m_ID = string;
}

void
GameObject::SetPosition(Vector2 position)
{
	m_position = position;
}

void 
GameObject::SetActive(bool active)
{
	m_active = active;
}
