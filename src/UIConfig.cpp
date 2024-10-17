#include "UIConfig.h"

#include "Logger.h"
#include "AssetLoader.h"

SpriteFont* UIConfig::DespairFont12;

void UIConfig::Init()
{
	Logger::LogInfo("Initialising UI Config");

	DespairFont12 = AssetLoader::GetSpriteFont("f_despair_12");
}
