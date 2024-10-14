#pragma once

#include "UIView.h"

#include <string>
#include <vector>

class Graphics;
class Sprite;
class UISystemView;

class UIManager
{
public:
	UIManager();
	~UIManager();

	static void Init();
	static void Update(float deltaTime);
	static void Render(Graphics* graphics);
	
	static void CreateUISystemView();
	
	static void RegisterUIView(UIView* uiView);
	static void UnregisterUIView(UIView* uiView);

	static void OnGameStateChange(std::string nextState);

	static void FadeOut();
	static void FadeIn();
	static bool IsFading();

	static void Destroy();

private:
	static UIManager* s_instance;
	
	void SwitchState();
	bool AnyViewsInState(UIView::ViewState state);
	void UpdateUIViews(float deltaTime);
	void Shutdown();

	UISystemView* m_uiSystemView;
	std::vector<UIView*> m_viewList;
	UIView::ViewState m_currentViewState = UIView::ViewState::NotVisible;
	UIView::ViewState m_targetViewState = UIView::ViewState::NotVisible;
};