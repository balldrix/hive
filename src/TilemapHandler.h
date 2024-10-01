#pragma once

#include "pch.h"
#include "TilemapData.h"

class TilemapHandler
{
public:
	TilemapHandler();
	~TilemapHandler();

	void LoadTilemap(const std::string& filename);
	TilemapData GetTilemapData() const { return m_tilemapData; }

private:
	TilemapData	m_tilemapData;
};