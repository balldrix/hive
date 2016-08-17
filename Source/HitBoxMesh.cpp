#include "pch.h"
#include "HitBoxMesh.h"
#include "Graphics.h"
#include "AABB.h"

HitBoxMesh::HitBoxMesh() :
	m_rhw(0.0f),
	m_colour(Colors::White)
{
}

HitBoxMesh::~HitBoxMesh()
{
}

void
HitBoxMesh::Init()
{
	m_rhw = 1.0f; // set to right hand winding
	m_colour = Colors::LimeGreen; // set hitbox to lime green colour
	m_primitiveType = D3DPT_LINESTRIP; // set primitive type
}

void 
HitBoxMesh::Update(Graphics* graphics, AABB hitbox)
{
	// setup hitbox vertices buffers for the hitbox mesh

	D3D11_BUFFER_DESC bd = { 0 };
	D3D11_SUBRESOURCE_DATA subData = { 0 };

	PCVertex quadVerts[] =
	{
		{ hitbox.GetMin().x, hitbox.GetMin().y, 0.0f, m_rhw, m_colour.BGRA() },
		{ hitbox.GetMax().x, hitbox.GetMin().y, 0.0f, m_rhw, m_colour.BGRA() },
		{ hitbox.GetMax().x, hitbox.GetMax().y, 0.0f, m_rhw, m_colour.BGRA() },
		{ hitbox.GetMin().x, hitbox.GetMax().y, 0.0f, m_rhw, m_colour.BGRA() },
	};

	HRESULT result; // result code for error handling

	result = graphics->GetD3DDevice()->CreateVertexBuffer(sizeof(quadVerts), D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, CUSTOMFVF, D3DPOOL_DEFAULT, &m_vertexBuffer, NULL);

	if(result != S_OK)
	{
		// TODO error handling
	}

	void *ptr;
	// lock buffer
	m_vertexBuffer->Lock(0, sizeof(quadVerts), (void**)&ptr, 0);
	memcpy(ptr, quadVerts, sizeof(quadVerts));
	m_vertexBuffer->Unlock();

	// create index buffer

	WORD quadIndices[] =
	{
		0,1,2,3,0
	};

	m_vertexCount = 4;
	m_indexCount = ARRAYSIZE(quadIndices);

	result = graphics->GetD3DDevice()->CreateIndexBuffer(m_indexCount *sizeof(DWORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL);

	if(result != S_OK)
	{
		// TODO error handling
	}
}
