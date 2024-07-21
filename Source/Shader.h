#pragma once

#include "pch.h"

class Graphics;

class Shader
{
public:
	Shader();
	Shader(const Shader&);
	~Shader();
	void LoadVertexShader(Graphics* graphics, std::wstring filename, std::string entryPoint, D3D11_INPUT_ELEMENT_DESC* inputElement, int numElements);
	void LoadPixelShader(Graphics* graphics, std::wstring filename, std::string entryPoint);
	void Release(); 
	ID3D11VertexShader* GetVertexShader() const { return m_vertexShader; }
	ID3D11PixelShader* GetPixelShader() const { return m_pixelShader; }
	ID3D11InputLayout* GetInputLayout() const { return m_vertexLayout; }

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_vertexLayout;
};