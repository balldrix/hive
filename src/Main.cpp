#include "Window.h"
#include "Graphics.h"
#include "Game.h"
#include "AudioEngine.h"
#include "SoundManager.h"
#include "AssetLoader.h"
#include "UIManager.h"
#include "MenuSystem.h"

Graphics* graphics = nullptr;
Window* window	= nullptr;
Game* game = nullptr;

void Shutdown();

LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Logger::Init();
	Logger::LogInfo("Initialised Logger.");

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if(!XMVerifyCPUSupport())
		return 1;

	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	if(FAILED(hr))
		return 1;

	window = new Window();
	window->Init(hInstance, nCmdShow, WndProc);

	graphics = new Graphics();
	graphics->Init(window->GetHwnd(), hInstance);
	
	AudioEngine::Init();
	AssetLoader::Init(graphics, "data\\assets.json");
	UIManager::Init();
	MenuSystem::Init();

	game = new Game();
	game->Init(window, graphics);

	MSG msg = {0};
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			game->Run();
		}
	}

	game->ReleaseAll(); 
	Shutdown();
	
	CoUninitialize();

	return static_cast<int>(msg.wParam);
}

void Shutdown()
{
	delete game;
	MenuSystem::Destroy();
	UIManager::Destroy();
	AssetLoader::Shutdown();
	SoundManager::DeleteSounds();
	AudioEngine::Destroy();
	delete graphics;
	delete window;
	
	game = nullptr;
	graphics = nullptr;
	window = nullptr;	

	Logger::LogInfo("Shutdown Game.");
}

LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return game->MessageHandler(hWindow, msg, wParam, lParam);
}