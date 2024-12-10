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
}

void UIProfileView::Render(Graphics* graphics)
{
	m_frame->Render(graphics);
	//m_characterImage->Render(graphics);
}

void UIProfileView::Shutdown()
{
	delete m_frame;
	m_frame = nullptr;

	delete m_characterImage;
	m_characterImage = nullptr;
}

void UIProfileView::SetPosition(const Vector2& position)
{
	m_frame->SetPosition(position);
	m_characterImage->SetPosition(position);
}