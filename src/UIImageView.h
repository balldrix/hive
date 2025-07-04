#pragma once

#include "UISprite.h"
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

	UISprite* GetSprite() const { return m_uiSprite; }
	int GetHeight() const override { return (int)m_uiSprite->GetHeight(); }

	void SetPosition(Vector2 position);
	void SetOrigin(Vector2 origin);
	void SetDepth(float depth);
	void SetColour(Color colour) override;
	void SetAlpha(float alpha);
	void SetFlipped(float flipped);

	void Shutdown();

protected:
	UISprite* m_uiSprite;
};