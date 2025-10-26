#pragma once

#include "UIView.h"

#include <string>
#include <unordered_map>
#include <vector>

class EventManager;
class Graphics;
class SoundSource;
class UISprite;
class UISystemView;
class UIFrontEndView;
class UIMainView;

enum class UISoundType
{
	Navigate,
	Select,
	Load,
	Delete,
	Open,
	Close
};

class Window;
class Graphics;
class Input;

class UIManager
{
public:
	static void Init(Window* window, Graphics* graphics, Input* input, EventManager* eventManager);
	static void Update(float deltaTime);
	static void Render(Graphics* graphics);

	static void CreateUISystemView();

	static void CreateUIFrontEndView();
	static void DestroyUIFrontEndView();

	static void CreateUIMainView();
	static void DestroyUIMainView();

	static void RegisterUIView(UIView* uiView);
	static void UnregisterUIView(UIView* uiView);

	static void OnGameStateChange(std::string nextState);

	static void FadeOut();
	static void FadeIn();

	static bool IsFading();
	static bool AnyViewsInState(UIView::ViewStates state);

	static UIView* GetView(std::string name);

	static void PlayUISound(UISoundType type);

	static void Destroy();

	void ShowUI(bool show);

private:
	UIManager();
	~UIManager();

	static UIManager* s_instance;
	
	void SwitchState();
	void UpdateUIViews(float deltaTime);
	void Shutdown();

	UISystemView* m_uiSystemView;
	UIFrontEndView* m_uiFrontEndView;
	UIMainView* m_uiMainView;

	std::vector<UIView*> m_viewList;
	UIView::ViewStates m_currentViewState = UIView::ViewStates::NotVisible;
	UIView::ViewStates m_targetViewState = UIView::ViewStates::NotVisible;

	SoundSource* m_uiSoundSource;

	std::unordered_map<UISoundType, std::string> m_uiSoundMap =
	{
		{ UISoundType::Navigate, "uiNav" },
		{ UISoundType::Select, "uiSelect" },
		{ UISoundType::Load, "uiLoad" },
		{ UISoundType::Delete, "uiDelete" },
		{ UISoundType::Open, "uiOpen" },
		{ UISoundType::Close, "uiClose" }
	};

	Window* m_window;
	Graphics* m_graphics;
	Input* m_input;
	EventManager* m_eventManager;
};