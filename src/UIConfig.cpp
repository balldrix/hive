#include "UIConfig.h"

#include "AssetLoader.h"
#include "Logger.h"

#include <directxtk/SpriteFont.h>

SpriteFont* UIConfig::DespairFont8;
SpriteFont* UIConfig::DespairFont12;
SpriteFont* UIConfig::GameBoy28;
SpriteFont* UIConfig::GamerFont16;
SpriteFont* UIConfig::GamerFont34;
SpriteFont* UIConfig::ThaleahFont12;

void UIConfig::Init()
{
	Logger::LogInfo("Initialising UI Config");

	DespairFont8 = AssetLoader::GetSpriteFont("f_despair_8");
	DespairFont12 = AssetLoader::GetSpriteFont("f_despair_12");
	GameBoy28 = AssetLoader::GetSpriteFont("f_gameboy_28");
	GamerFont16 = AssetLoader::GetSpriteFont("f_gamer_16");
	GamerFont34 = AssetLoader::GetSpriteFont("f_gamer_34");
	ThaleahFont12 = AssetLoader::GetSpriteFont("f_thaleah_12");
}
