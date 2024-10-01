#pragma once

#include "pch.h"

class Graphics;

class PixelTexture
{
public:
	PixelTexture();
	~PixelTexture();

	void Init(Graphics* graphics);
	ID3D11ShaderResourceView* GetTexture() { return m_texture.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};