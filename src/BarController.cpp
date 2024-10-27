#include "BarController.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Texture.h"
#include "pch.h"

BarController::BarController() :
	m_currentValue(0),
	m_maxValue(0),
	m_backgroundTexture(nullptr),
	m_fillTexture(nullptr),
	m_frameTexture(nullptr),
	m_backgroundSprite(nullptr),
	m_fillSprite(nullptr),
	m_frameSprite(nullptr),
	m_width(0U)
{
}

BarController::~BarController()
{
	DeleteAll();
}

void BarController::Init(Graphics* graphics)
{
	m_backgroundTexture = new Texture();
	m_backgroundTexture->LoadTexture(graphics, "data//textures//UI//player1_hud_healthbar_background.png");

	m_fillTexture = new Texture();
	m_fillTexture->LoadTexture(graphics, "data//textures//UI//player1_hud_healthbar_fill.png");

	m_frameTexture = new Texture();
	m_frameTexture->LoadTexture(graphics, "data//textures//UI//player1_hud_healthbar_frame.png");

	m_backgroundSprite = new Sprite();
	m_backgroundSprite->Init(m_backgroundTexture);
	m_backgroundSprite->SetOrigin(Vector2::Zero);
	m_backgroundSprite->SetDepth(0.8f);

	m_fillSprite = new Sprite();
	m_fillSprite->Init(m_fillTexture);
	m_fillSprite->SetOrigin(Vector2::Zero);
	m_fillSprite->SetDepth(0.9f);

	m_frameSprite = new Sprite();
	m_frameSprite->Init(m_frameTexture);
	m_frameSprite->SetOrigin(Vector2::Zero);
	m_frameSprite->SetDepth(1.0f);

	m_width = m_frameSprite->GetWidth();
}

void BarController::Render(Graphics* graphics)
{
	m_backgroundSprite->Render(graphics);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.bottom = m_fillSprite->GetHeight();
	rect.right = static_cast<LONG>((static_cast<float>(m_width) / static_cast<float>(m_maxValue)) * m_currentValue);

	m_fillSprite->SetSourceRect(rect);

	m_fillSprite->Render(graphics);
	m_frameSprite->Render(graphics);
}

void BarController::DeleteAll()
{
	if(m_frameSprite)
	{
		delete m_frameSprite;
		m_frameSprite = nullptr;
	}

	if(m_fillSprite != nullptr)
	{
		delete m_fillSprite;
		m_fillSprite = nullptr;
	}

	if(m_backgroundSprite != nullptr)
	{
		delete m_backgroundSprite;
		m_backgroundSprite = nullptr;
	}

	if(m_frameTexture != nullptr)
	{
		delete m_frameTexture;
		m_frameTexture = nullptr;
	}

	if(m_fillTexture != nullptr)
	{
		delete m_fillTexture;
		m_fillTexture = nullptr;
	}

	if(m_backgroundTexture != nullptr)
	{
		delete m_backgroundTexture;
		m_backgroundTexture = nullptr;
	}
}

void BarController::SetCurrentValue(const int& value)
{
	m_currentValue = value;
}

void BarController::SetMaxValue(const int& value)
{
	m_maxValue = value;
}

void BarController::SetPosition(const Vector2& position)
{
	m_backgroundSprite->SetPosition(position);
	m_fillSprite->SetPosition(position);
	m_frameSprite->SetPosition(position);
}

void BarController::SetWidth(const unsigned int& width)
{
	m_width = width;

	RECT rect;
	rect.left = m_backgroundSprite->GetWidth() - width;
	rect.top = 0;
	rect.bottom = m_fillSprite->GetHeight();
	rect.right = m_backgroundSprite->GetWidth();

	m_backgroundSprite->SetSourceRect(rect);
	m_frameSprite->SetSourceRect(rect);
}

void BarController::ReleaseAll()
{
	m_backgroundTexture->Release();
	m_fillTexture->Release();
	m_frameTexture->Release();
}
