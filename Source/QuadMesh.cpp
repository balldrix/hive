#include "QuadMesh.h"

#include "Graphics.h"
#include "ConstantBuffers.h"
#include "InstanceData.h"

using namespace GlobalConstants;

QuadMesh::QuadMesh() :
	m_vertexBuffer(nullptr),
	m_indexBuffer(nullptr),
	m_instanceBuffer(nullptr),
	m_vertexCount(0),
	m_indexCount(0),
	m_stride(0)
{
}

QuadMesh::~QuadMesh() {}

void QuadMesh::Init(Graphics* graphics)
{
	D3D11_SUBRESOURCE_DATA subData = { 0 };
	D3D11_BUFFER_DESC bd = { 0 };

	VertexPositionTexture quadVerts[] =
	{
		{ Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f) },
		{ Vector3(0.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f) },
		{ Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 0.0)  },
		{ Vector3(1.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f) }
	};

	m_vertexCount = 4;

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexPositionTexture) * m_vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	subData = { quadVerts, 0, 0 };
	graphics->GetDevice()->CreateBuffer(&bd, &subData, &m_vertexBuffer);

	WORD quadIndices[] =
	{
		0, 1, 2,
		3, 0, 2
	};

	m_indexCount = ARRAYSIZE(quadIndices);

	bd.ByteWidth = sizeof(short) * m_indexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	subData = { quadIndices, 0 };
	graphics->GetDevice()->CreateBuffer(&bd, &subData, &m_indexBuffer);

	m_stride = sizeof(VertexPositionTexture);
}

void QuadMesh::CreateInstanceBuffer(Graphics* graphics, const unsigned int& numInstances)
{
	D3D11_BUFFER_DESC* bd = new D3D11_BUFFER_DESC;

	bd->Usage = D3D11_USAGE_DYNAMIC;
	bd->ByteWidth = sizeof(InstanceType) * numInstances;
	bd->BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd->CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd->MiscFlags = 0;

	DX::ThrowIfFailed(graphics->GetDevice()->CreateBuffer(bd, nullptr, &m_instanceBuffer));

	delete bd;
	bd = nullptr;
}

void QuadMesh::Render(Graphics* graphics)
{
	UINT offset = 0;

	graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &m_stride, &offset);
	graphics->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	graphics->GetDeviceContext()->DrawIndexed(m_indexCount, 0, 0);
}

void QuadMesh::RenderInstanced(Graphics* graphics, unsigned int* stride, const unsigned int& instanceCount)
{
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = m_vertexBuffer;
	bufferPointers[1] = m_instanceBuffer;

	graphics->GetDeviceContext()->IASetVertexBuffers(0, 2, bufferPointers, stride, offsets);
	graphics->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	
	graphics->GetDeviceContext()->DrawIndexedInstanced(m_indexCount, NumTilesPerScreen, 0, 0, 0);
}

void QuadMesh::Release()
{
	m_vertexBuffer->Release();
	m_indexBuffer->Release();
}
