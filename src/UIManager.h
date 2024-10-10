#pragma once

class Graphics;
class Sprite;

class UIManager
{
public:
	UIManager();
	~UIManager();

	static void Init();
	static void Destroy();
	static void RenderUI(Graphics* graphics);
	static void CreateSystemUI();

private:

	static UIManager* s_instance;

	void Render(Graphics* graphics);
	void Shutdown();

	Sprite* m_uiFadeScreen;

};