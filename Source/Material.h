#pragma once

#include "pch.h"

class Graphics;
class Texture;
class Shader;

const int MAX_TEXTURES = 2;

class Material
{
public:
	Material();
	~Material();
	
	void Init(Shader* shader);
	void Init(Texture* texture, Shader* shader);
	void RenderSetup(Graphics* graphics);

private:
	ID3D11ShaderResourceView* m_texture[MAX_TEXTURES];
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_inputLayout;
};
