#include "QuadMesh.h"

#include "Graphics.h"

QuadMesh::QuadMesh() :
	m_vertexBuffer(nullptr),
	m_indexBuffer(nullptr),
	m_vertexCount(0),
	m_indexCount(0),
	m_stride(0),
	m_quadVerts()
{
}

QuadMesh::~QuadMesh() {}

void QuadMesh::Init(Graphics* graphics) 
{
	D3D11_SUBRESOURCE_DATA subData = { 0 };
	D3D11_BUFFER_DESC bd = { 0 };

	m_quadVerts[0] = { Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)};
	m_quadVerts[1] = { Vector3(0.0f, 1.0f, 0.0f), Vector2(0.0f, 0.0f)};
	m_quadVerts[2] = { Vector3(1.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)};
	m_quadVerts[3] = { Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)};

	WORD quadIndices[] =
	{
		0, 1, 2,
		3, 0, 2
	};

	m_vertexCount = 6;
	m_indexCount = ARRAYSIZE(quadIndices);

	SetVertexBuffer(graphics);

	bd.ByteWidth = sizeof(short) * m_indexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	subData = { quadIndices, 0 };
	graphics->GetDevice()->CreateBuffer(&bd, &subData, &m_indexBuffer);

	m_stride = sizeof(VertexPositionTexture);
}

void QuadMesh::SetVertexBuffer(Graphics* graphics)
{
	D3D11_SUBRESOURCE_DATA subData = { 0 };
	D3D11_BUFFER_DESC bd = { 0 };

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexPositionTexture) * m_vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	subData = { m_quadVerts, 0, 0 };
	graphics->GetDevice()->CreateBuffer(&bd, &subData, &m_vertexBuffer);
}

void QuadMesh::Render(Graphics* graphics)
{
	UINT offset = 0;

	graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &m_stride, &offset);
	graphics->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	graphics->GetDeviceContext()->DrawIndexed(m_indexCount, 0, 0);
}

void QuadMesh::Render(Graphics* graphics, const TextureCoords& textureCoords)
{
	m_quadVerts[0].textureCoordinate = Vector2((float)textureCoords.left,  (float)textureCoords.bottom);
	m_quadVerts[1].textureCoordinate = Vector2((float)textureCoords.left,  (float)textureCoords.top);
	m_quadVerts[2].textureCoordinate = Vector2((float)textureCoords.right, (float)textureCoords.top);
	m_quadVerts[3].textureCoordinate = Vector2((float)textureCoords.right, (float)textureCoords.bottom);

	SetVertexBuffer(graphics);
	Render(graphics);
}

void QuadMesh::Release()
{
	m_vertexBuffer->Release();
	m_indexBuffer->Release();
}
