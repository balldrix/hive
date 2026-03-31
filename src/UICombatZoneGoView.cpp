#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "UICombatZoneGoView.h"

#include "AssetLoader.h"
#include "AudioEngine.h"
#include "Sound.h"
#include "SoundSource.h"
#include "UIImageView.h"
#include "UIManager.h"

#include <algorithm>
#include <cmath>
#include <directxtk/SimpleMath.h>
#include <string>

UICombatZoneGoView::UICombatZoneGoView() :
	m_goImage(nullptr),
	m_loopingSoundSource(nullptr),
	m_timer(0.0f)
{
	m_loopingSoundSource = new SoundSource();
	m_loopingSoundSource->SetPriority(SoundPriority::Always);
	m_loopingSoundSource->SetRelative(true);
	m_loopingSoundSource->SetLooping(true);

	AudioEngine::Instance()->AddSoundSource(m_loopingSoundSource);
}

UICombatZoneGoView::~UICombatZoneGoView()
{
	Shutdown();
}

void UICombatZoneGoView::Init(std::string name)
{
	m_name = name;

	auto* texture = AssetLoader::GetTexture("t_go_sign");

	m_goImage = new UIImageView();
	m_goImage->Init("Combat Zone Go Image", texture);
	m_goImage->SetPosition(Vector2(220.0f, 30.0f));
	m_goImage->SetDepth(1.0f);
	m_goImage->SetActive(true);
	m_goImage->SetAlpha(0.0f);

	UIManager::RegisterUIView(this);
}

void UICombatZoneGoView::Update(float deltaTime)
{
	if(!m_isActive) return;

	m_timer -= deltaTime;

	const float elapsedTime = DisplayDuration - m_timer;
	const float flash = std::abs(std::sin(elapsedTime * FlashFrequency));
	float alpha = 0.4f + (flash * 0.6f);
	float scale = 1.0f + (flash * (MaxPulseScale - 1.0f));

	if(m_timer < FadeOutDuration)
	{
		const float fade = std::max(0.0f, m_timer / FadeOutDuration);
		alpha *= fade;
		scale = 1.0f + ((scale - 1.0f) * fade);
	}

	m_goImage->SetAlpha(alpha);
	m_goImage->GetSprite()->SetScale(scale);

	if(m_timer <= 0.0f)
	{
		TransitionOut(false);
	}
}

void UICombatZoneGoView::Render(Graphics* graphics)
{
	if(!m_isActive || m_isForcedHidden) return;

	m_goImage->Render(graphics);
}

void UICombatZoneGoView::ForceHide(bool isForced)
{
	UIView::ForceHide(isForced);

	if(isForced && m_loopingSoundSource != nullptr)
	{
		m_loopingSoundSource->Stop();
	}
	else if(!isForced && m_isActive)
	{
		Sound* goSound = AssetLoader::GetSound("uiGo");
		if(goSound != nullptr && m_loopingSoundSource->GetSound() != goSound)
		{
			m_loopingSoundSource->Play(goSound);
		}
		else if(goSound != nullptr && m_loopingSoundSource->GetSource() == nullptr)
		{
			m_loopingSoundSource->Play(goSound);
		}
	}
}

void UICombatZoneGoView::TransitionIn(bool isAnimating)
{
	m_currentViewState = UIView::ViewStates::Visible;
	m_isActive = true;
	m_timer = DisplayDuration;
	m_goImage->SetAlpha(1.0f);
	m_goImage->GetSprite()->SetScale(1.0f);

	if(!m_isForcedHidden)
	{
		Sound* goSound = AssetLoader::GetSound("uiGo");
		if(goSound != nullptr)
		{
			m_loopingSoundSource->Play(goSound);
		}
	}
}

void UICombatZoneGoView::TransitionOut(bool isAnimating)
{
	m_currentViewState = UIView::ViewStates::NotVisible;
	m_isActive = false;
	m_loopingSoundSource->Stop();

	if(m_goImage != nullptr)
	{
		m_goImage->SetAlpha(0.0f);
		m_goImage->GetSprite()->SetScale(1.0f);
	}
}

void UICombatZoneGoView::Shutdown()
{
	UIManager::UnregisterUIView(this);

	if(m_loopingSoundSource != nullptr)
	{
		AudioEngine::Instance()->RemoveSoundSource(m_loopingSoundSource);
		delete m_loopingSoundSource;
		m_loopingSoundSource = nullptr;
	}

	delete m_goImage;
	m_goImage = nullptr;
}
