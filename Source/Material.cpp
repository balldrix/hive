#include "Material.h"
#include "Graphics.h"
#include "Texture.h"
#include "Shader.h"

Material::Material() :
	m_vertexShader(nullptr),
	m_pixelShader(nullptr),
	m_inputLayout(nullptr)
{
	for(int i = 0; i < MAX_TEXTURES; i++)
	{
		m_texture[i] = nullptr;
	}
}

Material::~Material()
{
}

void Material::Init(Shader* shader)
{
	m_vertexShader = shader->GetVertexShader();
	m_pixelShader = shader->GetPixelShader();
	m_inputLayout = shader->GetInputLayout();
}

void Material::Init(Texture* texture, Shader* shader)
{
	m_texture[0] = texture->GetTexture();
	m_vertexShader = shader->GetVertexShader();
	m_pixelShader = shader->GetPixelShader();
	m_inputLayout = shader->GetInputLayout();
}


void Material::RenderSetup(Graphics* graphics)
{
	graphics->GetDeviceContext()->VSSetShader(m_vertexShader, nullptr, 0);
	graphics->GetDeviceContext()->PSSetShader(m_pixelShader, nullptr, 0);

	if(m_texture[1] != nullptr)
	{
		graphics->GetDeviceContext()->PSSetShaderResources(0, 1, &m_texture[0]);
		graphics->GetDeviceContext()->PSSetShaderResources(1, 1, &m_texture[1]);
	}
	else
	{
		graphics->GetDeviceContext()->PSSetShaderResources(0, 1, &m_texture[0]);
	}

	graphics->GetDeviceContext()->IASetInputLayout(m_inputLayout);
}