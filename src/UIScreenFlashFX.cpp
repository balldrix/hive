#include "UIScreenFlashFX.h"

#include "AssetLoader.h"
#include "GlobalConstants.h"
#include "UIImageView.h"
#include "UIManager.h"
#include "UIView.h"

#include <cmath>
#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <string>

using namespace GlobalConstants;

UIScreenFlashFX::UIScreenFlashFX() :
	m_fullscreenImage(nullptr),
	m_timer(0.0f)
{
}

UIScreenFlashFX::~UIScreenFlashFX()
{
	Shutdown();
}

void UIScreenFlashFX::Init(std::string name)
{
	m_name = name;

	m_fullscreenImage = new UIImageView();
	m_fullscreenImage->Init("Image");
	m_fullscreenImage->GetSprite()->Init(AssetLoader::GetTexture("t_pixel"));
	
	RECT rect {};
	rect.left = 0;
	rect.right = GameWidth;
	rect.top = 0;
	rect.bottom = GameHeight;

	m_fullscreenImage->GetSprite()->SetSourceRect(rect);
	m_fullscreenImage->SetOrigin(Vector2::Zero);
	m_fullscreenImage->SetColour(Colors::White.v);
	m_fullscreenImage->SetDepth(1.0f);
	m_fullscreenImage->SetActive(true);

	UIManager::RegisterUIView(this);
}

void UIScreenFlashFX::Update(float deltaTime)
{
	if(!m_isActive) return;

	float t = m_timer / FlashDuration;
	float alpha = std::lerp(0.0f, 1.0f, t);
	m_fullscreenImage->SetAlpha(alpha);
	m_timer -= deltaTime;

	if(t <= 0.0f)
	{
		m_isActive = false;
		m_currentViewState = UIView::ViewStates::NotVisible;
	}
}

void UIScreenFlashFX::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	m_fullscreenImage->Render(graphics);
}

void UIScreenFlashFX::Shutdown()
{
	UIManager::UnregisterUIView(this);

	delete m_fullscreenImage;
	m_fullscreenImage = nullptr;
}

void UIScreenFlashFX::TransitionIn(bool isAnimating)
{
	m_currentViewState = UIView::ViewStates::Visible;
	m_isActive = true;
	m_fullscreenImage->SetAlpha(1.0);
	m_timer = FlashDuration;
}
