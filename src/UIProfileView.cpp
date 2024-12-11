#include "UIProfileView.h"

#include "AssetLoader.h"
#include "Sprite.h"
#include "UIImageView.h"
#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>

UIProfileView::UIProfileView() :
	m_frame(nullptr),
	m_characterImage(nullptr)
{
}

UIProfileView::~UIProfileView()
{
	Shutdown();
}

void UIProfileView::Init(std::string name)
{
	m_name = name;

	m_frame = new UIImageView();
	m_frame->Init(fmt::format("{} Frame", name));
	m_frame->GetSprite()->Init(AssetLoader::GetTexture("t_profile_frame"));
	m_frame->SetOrigin(Vector2::Zero);
	m_frame->SetDepth(0.0f);
	m_frame->SetPosition(Vector2(2.0f, 116.0f));
	m_frame->SetActive(true);

	m_characterImage = new UIImageView();
	m_characterImage->Init(fmt::format("{} Character Image", name));
	m_characterImage->GetSprite()->Init(AssetLoader::GetTexture("t_player_profile"));
	m_characterImage->SetOrigin(Vector2::Zero);
	m_characterImage->SetDepth(0.1f);
	m_characterImage->SetPosition(Vector2(4.0f, 118.0f));
	m_characterImage->SetActive(true);
}

void UIProfileView::Render(Graphics* graphics)
{
	m_frame->Render(graphics);
	m_characterImage->Render(graphics);
}

void UIProfileView::Shutdown()
{
	delete m_frame;
	m_frame = nullptr;

	delete m_characterImage;
	m_characterImage = nullptr;
}