#pragma once

#include <DirectXTK/SpriteFont.h>

using namespace DirectX;

class UIConfig
{
public:
	static SpriteFont* DespairFont8;
	static SpriteFont* DespairFont12;

	static void Init();
};