// HitBoxMesh.h
// Christopher Ball 2016
// child of Mesh class, holds data for quad
// that make up the visable hitbox

#ifndef _HITBOXMESH_H_
#define _HITBOXMESH_H_

#include "Mesh.h"

// forward declarations
class Graphics;
class AABB;

// inherit from Mesh Object
class HitBoxMesh : public Mesh
{
public:
	HitBoxMesh();
	~HitBoxMesh();
	void Init();
	void Update(Graphics* graphics, AABB hitbox); // update hitbox mesh position
private:
	float m_rhw; // right hand winding value
	Color m_colour; // vertex colour
};

#endif _HITBOXMESH_H_