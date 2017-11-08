// GameObject.h
// Christopher Ball 2017
// A base class for objects used in game

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "pch.h"
#include "AABB.h"

// forward definitions
class Sprite;
class Graphics;

class GameObject
{
public:
	GameObject();
	~GameObject();
	
	void			Init(Sprite* sprite, Vector2 position = Vector2(0.0f, 0.0f)); // initialise object

	virtual void	Update(float deltaTime) = 0;	// update object
	virtual void 	Render(Graphics* graphics) = 0;					// render object

	void			SetID(const wchar_t* string);		// set object ID
	void			SetPosition(Vector2 position);	// set position
	void			SetActive(bool active);			// set active or not

	const wchar_t*	GetID() const		{ return m_ID; }		// return object ID
	Sprite*			GetSprite() 		{ return m_sprite; }	// return sprite pointer
	Vector2			GetPosition() const { return m_position; }	// return cursor position
	AABB&			GetHitBox()			{ return m_hitbox; }	// return hitbox
	bool			IsActive() const	{ return m_active;}		// return if active

protected:
	const wchar_t*	m_ID;		// object ID
	Sprite*			m_sprite;	// game object sprite
	Vector2			m_position;	// object position
	AABB			m_hitbox;	// axis aligned bounding box
	bool			m_active;	// object active or not
};

#endif _GAMEOBJECT_H_