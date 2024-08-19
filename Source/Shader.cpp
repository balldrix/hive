#include "Shader.h"

#include "Graphics.h"
#include "Error.h"

Shader::Shader() :
	m_vertexShader(nullptr),
	m_pixelShader(nullptr),
	m_vertexLayout(nullptr)
{
}

Shader::~Shader() {}

void Shader::LoadVertexShader(Graphics* graphics, std::wstring filename, std::string entryPoint, D3D11_INPUT_ELEMENT_DESC* inputElement, int numElements)
{
	HRESULT result;
	ID3DBlob* errorMessage = nullptr;
	ID3DBlob* vertexShaderBuffer = nullptr;
	
	// compile vertex shader
	result = D3DCompileFromFile(filename.c_str(), NULL, NULL, entryPoint.c_str(), "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
	
	if(FAILED(result))
	{
		std::string error = " Error creating vertex shader in Shader.cpp;\n";
		Error::FileLog(error);
		MessageBox(graphics->GetHwnd(), L"Shader Error. See Logs/Error.txt", L"Error!", MB_OK);
		PostQuitMessage(0);
	}

	// create vertex shader
	result = graphics->GetDevice()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	
	if(FAILED(result))
	{
		std::string error = " Error creating vertex shader in Shader.cpp;\n";
		Error::FileLog(error);
		MessageBox(graphics->GetHwnd(), L"Shader Error. See Logs/Error.txt", L"Error!", MB_OK);
		PostQuitMessage(0);
	}

	result = graphics->GetDevice()->CreateInputLayout(inputElement, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_vertexLayout);

	if(FAILED(result))
	{
		std::string error = " Error creating input layout in Shader.cpp;\n";
		Error::FileLog(error);
		MessageBox(graphics->GetHwnd(), L"Shader Error. See Logs/Error.txt", L"Error!", MB_OK);
		PostQuitMessage(0);
	}
}

void Shader::LoadPixelShader(Graphics* graphics, std::wstring filename, std::string entryPoint)
{
	HRESULT result;
	ID3DBlob* errorMessage = nullptr;
	ID3DBlob* pixelShaderBuffer = nullptr;

	// compile pixel shader
	result = D3DCompileFromFile(filename.c_str(), NULL, NULL, entryPoint.c_str(), "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);

	if(FAILED(result))
	{
		std::string error = " Error creating pixel shader in Shader.cpp;\n";
		Error::FileLog(error);
		MessageBox(graphics->GetHwnd(), L"Shader Error. See Logs/Error.txt", L"Error!", MB_OK);
		PostQuitMessage(0);
	}

	result = graphics->GetDevice()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if(FAILED(result))
	{
		std::string error = " Error creating pixel shader in Shader.cpp;\n";
		Error::FileLog(error);
		MessageBox(graphics->GetHwnd(), L"Shader Error. See Logs/Error.txt", L"Error!", MB_OK);
		PostQuitMessage(0);
	}
}

void Shader::Release()
{
	// release all shader related pointers
	if(m_vertexLayout) { m_vertexLayout->Release(); }
	if(m_pixelShader) { m_pixelShader->Release(); }
	if(m_vertexShader) { m_vertexShader->Release(); }
}
