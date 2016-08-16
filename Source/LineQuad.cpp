#include "Quad.h"
#include "Graphics.h"
#include "ConstantBuffers.h"

QuadMesh::QuadMesh()
{
}

QuadMesh::~QuadMesh()
{
}

void 
QuadMesh::Init(Graphics * graphics)
{
	// setup enemy mesh vertices, indices
	//  and buffers for the enemy mesh

	D3D11_BUFFER_DESC bd = { 0 };
	D3D11_SUBRESOURCE_DATA subData = { 0 };

	Vertex quadVerts[] =
	{
		{ Vector3(-1.0f, -1.0f, 0.0f), Vector2(1.0f, 1.0f) },
		{ Vector3( 1.0f, -1.0f, 0.0f), Vector2(0.0f, 1.0f) },
		{ Vector3( 1.0f,  1.0f, 0.0f), Vector2(0.0f, 0.0f) },
		{ Vector3(-1.0f,  1.0f, 0.0f), Vector2(1.0f, 0.0f) },
	};

	// create index buffer

	WORD quadIndices[] =
	{
		2,0,1,
		3,0,2,
	};

	m_vertexCount = 8;
	m_indexCount = ARRAYSIZE(quadIndices);

	// create vertex buffer for a cube
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * ARRAYSIZE(quadVerts);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	subData = { quadVerts, 0, 0 };
	graphics->GetDevice()->CreateBuffer(&bd, &subData, &m_vertexBuffer);

	// create index buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(short) * m_indexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	subData = { quadIndices, 0 };
	graphics->GetDevice()->CreateBuffer(&bd, &subData, &m_indexBuffer);
}
