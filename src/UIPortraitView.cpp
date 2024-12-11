#include "UIPortraitView.h"

#include "AssetLoader.h"
#include "Sprite.h"
#include "UIImageView.h"
#include "UIView.h"

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
	m_frame->GetSprite()->Init(AssetLoader::GetTexture("t_profile_frame"));
	m_frame->SetOrigin(Vector2::Zero);
	m_frame->SetDepth(0.0f);
	m_frame->SetActive(true);

	m_characterImage = new UIImageView();
	m_characterImage->Init(fmt::format("{} Character Image", name));
	m_characterImage->GetSprite()->Init(AssetLoader::GetTexture("t_player_profile"));
	m_characterImage->SetOrigin(Vector2::Zero);
	m_characterImage->SetDepth(0.0f);
	m_characterImage->SetActive(true);
}

void UIPortraitView::Render(Graphics* graphics)
{
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

void UIPortraitView::SetPosition(const Vector2& position)
{
	m_frame->SetPosition(position);
	m_characterImage->SetPosition(position);
}
