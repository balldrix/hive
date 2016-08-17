#include "Mesh.h"
#include "Graphics.h"

Mesh::Mesh() :
	m_vertexBuffer(nullptr),
	m_indexBuffer(nullptr),
	m_vertexCount(0),
	m_indexCount(0),
	m_primitiveType(D3DPT_POINTLIST)
{}

Mesh::~Mesh()
{
}

void 
Mesh::Render(Graphics* graphics)
{
	UINT stride = sizeof(PCVertex);
	UINT offset = 0;

	// set render state
	graphics->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// set vertex buffer to stream source
	graphics->GetD3DDevice()->SetStreamSource(0, m_vertexBuffer, 0, sizeof(PCVertex));

	// set FVF
	graphics->GetD3DDevice()->SetFVF(CUSTOMFVF);

	// draw primitive indexed buffer
	graphics->GetD3DDevice()->DrawIndexedPrimitive(m_primitiveType, 0, 0, m_vertexCount, 0, m_indexCount);

	// reset render state
	graphics->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void
Mesh::Release()
{
	// release all buffers

	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}

	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}
}