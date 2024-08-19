#pragma once

#include "pch.h"
#include "TextureCoords.h"

const int NUM_VERTS = 4;

class Graphics;

class QuadMesh
{
public:
	QuadMesh();
	QuadMesh(const QuadMesh&) = default;
	~QuadMesh();

	void Init(Graphics* graphics);
	void CreateInstanceBuffer(Graphics* graphics, const unsigned int& numInstances);
	
	void Render(Graphics* graphics);
	void RenderInstanced(Graphics* graphics, unsigned int* stride, const unsigned int& instanceCount);
	void Release();

	ID3D11Buffer* GetInstanceBuffer() const { return m_instanceBuffer; }

private:

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	ID3D11Buffer* m_instanceBuffer;

	int m_vertexCount;
	int m_indexCount;
	UINT m_stride;
};