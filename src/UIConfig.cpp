#include "UIConfig.h"

#include "AssetLoader.h"
#include "Logger.h"

#include <directxtk/SpriteFont.h>

SpriteFont* UIConfig::DespairFont8;
SpriteFont* UIConfig::DespairFont12;
SpriteFont* UIConfig::GamerFont16;
SpriteFont* UIConfig::GamerFont36;
SpriteFont* UIConfig::ThaleahFont12;

void UIConfig::Init()
{
	Logger::LogInfo("Initialising UI Config");

	DespairFont8 = AssetLoader::GetSpriteFont("f_despair_8");
	DespairFont12 = AssetLoader::GetSpriteFont("f_despair_12");
	GamerFont16 = AssetLoader::GetSpriteFont("f_gamer_16");
	GamerFont36 = AssetLoader::GetSpriteFont("f_gamer_36");
	ThaleahFont12 = AssetLoader::GetSpriteFont("f_thaleah_12");
}
