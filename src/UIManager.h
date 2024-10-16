#pragma once

#include "UIView.h"

#include <string>
#include <vector>

class Graphics;
class Sprite;
class UISystemView;
class UIFrontEndView;

class UIManager
{
public:
	UIManager();
	~UIManager();

	static void Init();
	static void Update(float deltaTime);
	static void Render(Graphics* graphics);
	
	static void CreateUISystemView();

	static void CreateUIFrontEndView();
	static void DestroyUIFrontEndView();
	
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
	bool AnyViewsInState(UIView::ViewStates state);
	void UpdateUIViews(float deltaTime);
	void Shutdown();

	UISystemView* m_uiSystemView;
	UIFrontEndView* m_uiFrontEndView;
	std::vector<UIView*> m_viewList;
	UIView::ViewStates m_currentViewState = UIView::ViewStates::NotVisible;
	UIView::ViewStates m_targetViewState = UIView::ViewStates::NotVisible;
};