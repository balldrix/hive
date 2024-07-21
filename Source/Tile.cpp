#include "Tile.h"

#include "Graphics.h"
#include "Material.h"
#include "QuadMesh.h"

Tile::Tile() :
	m_mesh(nullptr),
	m_material(nullptr),
	m_modelMatrix(XMMatrixIdentity()),
	m_scaleMatrix(XMMatrixIdentity()),
	m_translationalMatrix(XMMatrixIdentity()),
	m_rotationalMatrix(XMMatrixIdentity()),
	m_texCoords(),
	m_position(0.0f, 0.0f)
{
}

Tile::~Tile()
{
	m_mesh->Release();
}

void Tile::Init(QuadMesh* mesh, Material* material)
{
	m_mesh = mesh;
	m_material = material;
}

void Tile::Update()
{
	m_translationalMatrix = XMMatrixTranslationFromVector(m_position);
	m_modelMatrix = m_rotationalMatrix * m_scaleMatrix * m_translationalMatrix;
}

void Tile::Render(Graphics* graphics)
{
	graphics->SetWorldMatrix(m_modelMatrix);
	m_material->RenderSetup(graphics);
	m_mesh->Render(graphics, m_texCoords);
}

void Tile::SetSize(const Vector2& size)
{
	m_scaleMatrix *= XMMatrixScaling(size.x, size.y, 1.0f);
}

void Tile::SetTexCoords(const TextureCoords& texCoords)
{
	m_texCoords = texCoords;
}

void Tile::SetPosition(const Vector2& position)
{
	m_position = position;
}
