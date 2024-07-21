#pragma once

#include "pch.h"
#include "TextureCoords.h"

const int NUM_VERTS = 4;

class Graphics;

class QuadMesh
{
public:
	QuadMesh();
	QuadMesh(const QuadMesh&);
	~QuadMesh();

	void Init(Graphics* graphics);
	void Render(Graphics* graphics);
	void Render(Graphics* graphics, const TextureCoords& rect);
	void Release();
	
	void SetVertexBuffer(Graphics* graphics);

private:
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	int m_vertexCount;
	int m_indexCount;
	UINT m_stride;
	
	VertexPositionTexture m_quadVerts[NUM_VERTS];
};