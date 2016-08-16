// LineQuad.h
// Christopher Ball 2016
// child of MeshObject, holds data for blocks
// that make up the enemy

#ifndef _QUAD_H_
#define _QUAD_H_

// forward declarations
class Graphics;

#include "Mesh.h"

// inherit from Mesh Object
class QuadMesh : public Mesh
{
public:
	QuadMesh();
	~QuadMesh();
	void Init(Graphics* graphics); // initialise quad mesh
};

#endif _QUAD_MESH_H_