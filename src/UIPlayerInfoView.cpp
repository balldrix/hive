#include "UIPlayerInfoView.h"

#include "AssetLoader.h"
#include "Logger.h"
#include "UIBarView.h"
#include "UIPortraitView.h"
#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <string>

UIPlayerInfoView::UIPlayerInfoView() :
	m_portraitView(nullptr),
	m_healthBar(nullptr)
{
}

UIPlayerInfoView::~UIPlayerInfoView()
{
	Shutdown();
}

void UIPlayerInfoView::Init(std::string name)
{
	m_name = name;

	m_portraitView = new UIPortraitView();
	m_portraitView->Init("Player Portrait");
	m_portraitView->SetPosition(Vector2(2.0f, 116.0f));

	m_healthBar = new UIBarView();
	m_healthBar->Init("Player Health Bar");
	m_healthBar->SetBackgroundTexture(AssetLoader::GetTexture("t_pixel"));
	m_healthBar->SetFillTexture(AssetLoader::GetTexture("t_bar_fill_red"));

}

void UIPlayerInfoView::Update(float deltaTime)
{
}

void UIPlayerInfoView::Render(Graphics* graphics)
{
	m_portraitView->Render(graphics);
}

void UIPlayerInfoView::TransitionIn(bool isAnimating)
{
}

void UIPlayerInfoView::TransitionOut(bool isAnimating)
{
}

void UIPlayerInfoView::Shutdown()
{
	Logger::LogInfo("Shutting down UI PlayerInfoView");

	delete m_healthBar;
	m_healthBar = nullptr;

	delete m_portraitView;
	m_portraitView = nullptr;
}

void UIPlayerInfoView::DoTransition(float deltaTime)
{
}
