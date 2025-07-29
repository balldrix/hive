#include "UIPanelContainer.h"

#include "AssetLoader.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "UIImageView.h"
#include "UIView.h"

#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <string>
#include <Windows.h>

using namespace GlobalConstants;

UIPanelContainer::UIPanelContainer() :
	m_overlayImage(nullptr),
	m_panelImage(nullptr)
{
}

UIPanelContainer::~UIPanelContainer()
{
	Shutdown();
}

void UIPanelContainer::Init(const std::string& name, const RECT& rect)
{
	UIView::Init(name);

	m_overlayImage = new UIImageView();
	m_overlayImage->Init("Pause Overlay Image", AssetLoader::GetTexture("t_pixel"));
	m_overlayImage->GetSprite()->SetSourceRect(RECT{ 0, 0, GameWidth, GameHeight });
	m_overlayImage->SetAlpha(0.4f);
	m_overlayImage->SetOrigin(Vector2::Zero);
	m_overlayImage->SetColour(Colors::Black.v);
	m_overlayImage->SetDepth(0.3f);

	m_panelImage = new UIImageView();
	m_panelImage->Init("Panel Image", AssetLoader::GetTexture("t_pixel"));
	m_panelImage->GetSprite()->SetSourceRect(rect);
	m_panelImage->SetOrigin(Vector2::Zero);
	m_panelImage->SetPosition(Vector2(10.0f, 30.0f));
	m_panelImage->SetColour(Color(0.17f, 0.18f, 0.2f, 0.9f));
	m_panelImage->SetDepth(0.4f);
}

void UIPanelContainer::Render(Graphics* graphics)
{
	m_panelImage->Render(graphics);
	m_overlayImage->Render(graphics);
}

void UIPanelContainer::Shutdown()
{
	delete m_panelImage;
	delete m_overlayImage;

	m_panelImage = nullptr;
	m_overlayImage = nullptr;
}

void UIPanelContainer::SetActive(bool isActive)
{
	m_overlayImage->SetActive(isActive);
	m_panelImage->SetActive(isActive);
}

void UIPanelContainer::SetOverlayAlpha(float alpha)
{
	m_overlayImage->SetAlpha(alpha * 0.4f);
}

void UIPanelContainer::SetPanelAlpha(float alpha)
{
	m_panelImage->SetAlpha(alpha);
}
