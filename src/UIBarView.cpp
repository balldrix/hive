#include "UIBarView.h"

#include "Sprite.h"
#include "Texture.h"
#include "UIImageView.h"
#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>
#include <windef.h>
#include <winnt.h>

UIBarView::UIBarView() :
	m_currentValue(0),
	m_maxValue(0),
	m_width(0U),
	m_backgroundImage(nullptr),
	m_fillImage(nullptr),
	m_frameImage(nullptr)
{
}

UIBarView::~UIBarView()
{
	Shutdown();
}

void UIBarView::Init(std::string name)
{
	m_name = name;

	m_backgroundImage = new UIImageView();
	m_backgroundImage->Init(fmt::format("{} Background", name));

	m_fillImage = new UIImageView();
	m_fillImage->Init(fmt::format("{} Fill", name));

	m_frameImage = new UIImageView();
	m_frameImage->Init(fmt::format("{} Frame", name));
}

void UIBarView::Update(float deltaTime)
{
	if(!m_isActive) return;

	RECT rect{};
	rect.left = 0;
	rect.top = 0;
	rect.bottom = m_fillImage->GetHeight();
	rect.right = static_cast<LONG>((m_width / static_cast<float>(m_maxValue)) * m_currentValue);

	m_fillImage->GetSprite()->SetSourceRect(rect);

	rect.right = m_width;
	m_backgroundImage->GetSprite()->SetSourceRect(rect);
}

void UIBarView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	m_backgroundImage->Render(graphics);
	m_fillImage->Render(graphics);
	m_frameImage->Render(graphics);
}

void UIBarView::Shutdown()
{
	delete m_frameImage;
	m_frameImage = nullptr;

	delete m_fillImage;
	m_fillImage = nullptr;

	delete m_backgroundImage;
	m_backgroundImage = nullptr;
}

void UIBarView::SetBackgroundTexture(Texture* texture)
{
	m_backgroundImage->GetSprite()->Init(texture);
	m_backgroundImage->SetOrigin(Vector2::Zero);
	m_backgroundImage->SetDepth(0.0f);
	m_backgroundImage->SetActive(true);
}

void UIBarView::SetFillTexture(Texture* texture)
{
	m_fillImage->GetSprite()->Init(texture);
	m_fillImage->SetOrigin(Vector2::Zero);
	m_fillImage->SetDepth(0.0f);
	m_fillImage->SetActive(true);
}

void UIBarView::SetFrameTexture(Texture* texture)
{
	m_frameImage->GetSprite()->Init(texture);
	m_frameImage->SetOrigin(Vector2(1.0f, 1.0f));
	m_frameImage->SetDepth(0.0f);
	m_frameImage->SetActive(true);
}

void UIBarView::SetCurrentValue(const int& value)
{
	m_currentValue = value;
}

void UIBarView::SetMaxValue(const int& value)
{
	m_maxValue = value;
}

void UIBarView::SetPosition(const Vector2& position)
{
	m_backgroundImage->SetPosition(position);
	m_fillImage->SetPosition(position);
	m_frameImage->SetPosition(position);
}

void UIBarView::SetWidth(const unsigned int& value)
{
	m_width = value;
}

void UIBarView::SetBackgroundColour(Color colour)
{
	m_backgroundImage->SetColour(colour);
}
