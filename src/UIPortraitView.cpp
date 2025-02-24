#include "UIPortraitView.h"

#include "AssetLoader.h"
#include "Sprite.h"
#include "UIImageView.h"
#include "UIView.h"

#include "Texture.h"
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>

UIPortraitView::UIPortraitView() :
	m_frame(nullptr),
	m_characterImage(nullptr)
{
}

UIPortraitView::~UIPortraitView()
{
	Shutdown();
}

void UIPortraitView::Init(std::string name)
{
	m_name = name;

	m_frame = new UIImageView();
	m_frame->Init(fmt::format("{} Frame", name));
	m_frame->GetSprite()->Init(AssetLoader::GetTexture("t_portrait_frame"));
	m_frame->SetOrigin(Vector2::Zero);
	m_frame->SetDepth(0.0f);
	m_frame->SetActive(true);

	m_characterImage = new UIImageView();
	m_characterImage->Init(fmt::format("{} Character Image", name));
	m_characterImage->SetOrigin(Vector2::Zero);
	m_characterImage->SetDepth(0.0f);
	m_characterImage->SetActive(true);
}

void UIPortraitView::Render(Graphics* graphics)
{
	if(!m_isActive || m_isForcedHidden) return;

	m_frame->Render(graphics);
	m_characterImage->Render(graphics);
}

void UIPortraitView::Shutdown()
{
	delete m_frame;
	m_frame = nullptr;

	delete m_characterImage;
	m_characterImage = nullptr;
}

void UIPortraitView::SetPortraitTexture(Texture* texture)
{
	m_characterImage->GetSprite()->Init(texture);
	m_characterImage->SetOrigin(Vector2::Zero);
}

void UIPortraitView::SetPosition(const Vector2& position)
{
	m_frame->SetPosition(position);
	m_characterImage->SetPosition(position);
}
