#include "UIFadeOverlayView.h"

#include "AssetLoader.h"
#include "GlobalConstants.h"
#include "Logger.h"
#include "Sprite.h"

using namespace GlobalConstants;

UIFadeOverlayView::UIFadeOverlayView() :
	m_startingAlpha(0),
	m_targetAlpha(0)
{
}

UIFadeOverlayView::~UIFadeOverlayView()
{
	Shutdown();
}

void UIFadeOverlayView::Init(std::string name)
{
	m_name = name;

	Logger::LogInfo("Initialising UI Fade Overlay.");

	m_sprite = new Sprite();
	m_sprite->Init(AssetLoader::GetTexture("t_pixel"));
	m_sprite->SetColour(OpaqueColour);

	RECT rect;
	rect.left = 0;
	rect.right = GameWidth;
	rect.top = 0;
	rect.bottom = GameHeight;

	m_sprite->SetSourceRect(rect);
	m_sprite->SetOrigin(Vector2::Zero);
	m_sprite->SetDepth(1.0f);
}

void UIFadeOverlayView::Update(float deltaTime)
{
	if(!m_isActive) return;
		
	if(m_transitionTimer > 0.0f)
	{
		m_isAnimating = true;
		m_transitionTimer -= deltaTime;
	}

	if(m_transitionTimer < 0.0f)
	{
		m_isAnimating = false;
		m_transitionTimer = 0.0f;
	}

	float t = m_transitionTimer / FadeDuration;
	float a = m_startingAlpha;
	float b = m_targetAlpha;
	float lerp = std::lerp(a, b, 1 - t);

	m_sprite->SetAlpha(lerp);

	if(m_sprite->GetAlpha() == 0.0f && !m_isAnimating)
		m_isActive = false;
}

void UIFadeOverlayView::Render(Graphics* graphics)
{
	if(m_isActive)
		m_sprite->Render(graphics);
}

void UIFadeOverlayView::TransitionIn(bool isAnimating)
{
	Logger::LogInfo(fmt::format("Transition In: UI Fade Overlay {} animation.", isAnimating ? "with" : "without"));

	m_isActive = true;
	m_startingAlpha = 0.0f;
	m_targetAlpha = 1.0f;

	if(!isAnimating)
	{
		m_sprite->SetAlpha(m_targetAlpha);
		return;
	}

	m_sprite->SetAlpha(m_startingAlpha);
	m_transitionTimer = FadeDuration;
}

void UIFadeOverlayView::TransitionOut(bool isAnimating)
{
	Logger::LogInfo(fmt::format("Transition Out: UI Fade Overlay {} animation.", isAnimating ? "with" : "without"));
	
	m_isActive = true;
	m_startingAlpha = 1.0f;
	m_targetAlpha = 0.0f;

	if(!isAnimating)
	{
		m_sprite->SetAlpha(m_targetAlpha);
		m_isActive = false;
		return;
	}

	m_sprite->SetAlpha(m_startingAlpha);
	m_transitionTimer = FadeDuration;
}

void UIFadeOverlayView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Fade Overlay.");
}
