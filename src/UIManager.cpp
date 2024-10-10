#include "UIManager.h"

#include "pch.h"
#include "Logger.h"
#include "Graphics.h"
#include "Sprite.h"
#include "AssetLoader.h"
#include "GlobalConstants.h"

using namespace GlobalConstants;

UIManager* UIManager::s_instance = nullptr;

UIManager::UIManager()
{

}

UIManager::~UIManager()
{
}

void UIManager::Init()
{
	Logger::LogInfo("Initialising UI Manager.");

	s_instance = new UIManager;
}

void UIManager::CreateSystemUI()
{
	s_instance->m_uiFadeScreen = new Sprite();

	s_instance->m_uiFadeScreen->Init(AssetLoader::GetTexture("pixel"));

	RECT rect;
	rect.left = 0;
	rect.right = GameWidth;
	rect.top = 0;
	rect.bottom = GameHeight;

	s_instance->m_uiFadeScreen->SetSourceRect(rect);
	s_instance->m_uiFadeScreen->SetColour(Colors::HotPink.v);
}

void UIManager::Shutdown()
{
	delete m_uiFadeScreen;
	m_uiFadeScreen = nullptr;
}

void UIManager::Destroy()
{
	s_instance->Shutdown();

	delete s_instance;
	s_instance = nullptr;
}

void UIManager::RenderUI(Graphics* graphics)
{
	s_instance->Render(graphics);
}

void UIManager::Render(Graphics* graphics)
{
	m_uiFadeScreen->Render(graphics);
}
