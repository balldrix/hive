#pragma once

#include <DirectXTK/SpriteFont.h>

using namespace DirectX;

class UIConfig
{
public:
	static SpriteFont* DespairFont8;
	static SpriteFont* DespairFont12;
	static SpriteFont* GamerFont16;
	static SpriteFont* GameBoy28;
	static SpriteFont* GamerFont34;
	static SpriteFont* ThaleahFont12;

	static void Init();
};