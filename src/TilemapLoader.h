#pragma once

#include "TilemapData.h"

#include <string>

class TilemapLoader
{
public:
	TilemapLoader();
	~TilemapLoader() = default;

	static void Init();
	static void Shutdown();

	static void LoadTilemap(std::string path);
	static TilemapData GetCurrentMap() { return s_instance->m_tilemapData; }

private:
	static TilemapLoader* s_instance;

	TilemapData m_tilemapData;
};
