#include "TilemapHandler.h"

TilemapHandler::TilemapHandler()
{
}

TilemapHandler::~TilemapHandler()
{
}

void TilemapHandler::LoadTilemap(const std::string& filename)
{
	std::ifstream file(filename);
	m_tilemapData = json::parse(file);
}
