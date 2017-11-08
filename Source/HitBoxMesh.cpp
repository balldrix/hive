#include "pch.h"
#include "HitBoxMesh.h"
#include "Graphics.h"
#include "AABB.h"

HitBoxMesh::HitBoxMesh() :
	m_colour(Colors::White)
{
}

HitBoxMesh::~HitBoxMesh()
{
}

void
HitBoxMesh::Init()
{
	m_colour = Colors::LimeGreen; // set hitbox to lime green colour
}

void 
HitBoxMesh::Update(Graphics* graphics, AABB hitbox)
{
	
}
