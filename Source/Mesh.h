// Mesh.h
// Christopher Ball 2016
// The mesh class is a base class to hold the vertex and index buffers
// a child class will specify the vertices and indices specific to 
// that mesh. Modified code from SumoDX by Mickey Macdonald @scruffyfurn

#ifndef _MESH_H_
#define _MESH_H_

#include "pch.h"

// forward declarations
class Graphics;

class Mesh
{
public:
	Mesh();
	~Mesh();
	virtual void Init(Graphics* graphics) = 0; // pure virtual method to initialise mesh object
	virtual void Render(Graphics* graphics); // render mesh object
	void Release();

protected:
	IDirect3DVertexBuffer9*	m_vertexBuffer; // vertex buffer
	IDirect3DIndexBuffer9*	m_indexBuffer; // index buffer
	int						m_vertexCount; // number of vertices
	int						m_indexCount; // number of indices
	D3DPRIMITIVETYPE		m_primitiveType; // primitive type enum
};

#endif _MESH_H_