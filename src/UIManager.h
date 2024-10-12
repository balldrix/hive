#pragma once

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
	static void FadeOut();
	static void FadeIn();
	static bool IsFading();
	static void Destroy();

private:
	static UIManager* s_instance;
	
	void Shutdown();

	UISystemView* m_uiSystemView;
};