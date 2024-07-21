#pragma once

#include "pch.h"
#include "TextureCoords.h"

class Graphics;
class QuadMesh;
class Material;

class Tile
{
public:
	Tile();
	~Tile();

	void Init(QuadMesh* mesh, Material* material);
	void Update();
	void Render(Graphics* graphics);

	void SetSize(const Vector2& size);
	void SetTexCoords(const TextureCoords& rect);
	void SetPosition(const Vector2& position);
private:
	QuadMesh*		m_mesh;
	Material*		m_material;

	Matrix			m_modelMatrix;
	Matrix			m_scaleMatrix;
	Matrix			m_translationalMatrix;
	Matrix			m_rotationalMatrix;

	TextureCoords	m_texCoords;
	Vector2			m_position;
};