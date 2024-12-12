#pragma once

#include "Sprite.h"
#include "UIView.h"

#include <DirectXTK/SimpleMath.h>
#include <string>

using namespace DirectX::SimpleMath;

class Graphics;

class UIImageView : public UIView
{
public:
	UIImageView();
	virtual ~UIImageView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;

	Sprite* GetSprite() const { return m_sprite; }
	int GetHeight() const override { return (int)m_sprite->GetHeight(); }

	void SetPosition(Vector2 position);
	void SetOrigin(Vector2 origin);
	void SetDepth(float depth);
	void SetColour(Color colour) override;

	void Shutdown();

protected:
	Sprite* m_sprite;
};