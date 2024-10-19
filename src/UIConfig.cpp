#include "UIConfig.h"

#include "Logger.h"
#include "AssetLoader.h"

SpriteFont* UIConfig::DespairFont8;
SpriteFont* UIConfig::DespairFont12;

void UIConfig::Init()
{
	Logger::LogInfo("Initialising UI Config");

	DespairFont8 = AssetLoader::GetSpriteFont("f_despair_8");
	DespairFont12 = AssetLoader::GetSpriteFont("f_despair_12");
}
