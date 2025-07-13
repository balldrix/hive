#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0601

#define NOMINMAX
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP
#define NOMCX
#define NOSERVICE
#define NOHELP

#define WIN32_LEAN_AND_MEAN

#include "AssetLoader.h"
#include "AudioEngine.h"
#include "Game.h"
#include "GameDataManager.h"
#include "Graphics.h"
#include "Logger.h"
#include "MenuSystem.h"
#include "SettingsManager.h"
#include "UIManager.h"
#include "Window.h"

#include <combaseapi.h>
#include <DirectXMathMisc.inl>
#include <sal.h>
#include <Windows.h>

Graphics* graphics = nullptr;
Window* window	= nullptr;
Game* game = nullptr;

void Shutdown();

LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Logger::Init();
	SettingsManager::Init();

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if(!XMVerifyCPUSupport())
		return 1;

	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	if(FAILED(hr))
		return 1;

	int width = SettingsManager::Instance()->GetScreenWidth();
	int height = SettingsManager::Instance()->GetScreenHeight();

	window = new Window();
	window->Init(width, height, hInstance, nCmdShow, WndProc);

	graphics = new Graphics();
	graphics->Init(width, height, window->GetHwnd(), hInstance);
	
	AudioEngine::Init();
	AssetLoader::Init(graphics, "assets\\assets.json");
	GameDataManager::Init();
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

	Shutdown();
	
	CoUninitialize();

	return static_cast<int>(msg.wParam);
}

void Shutdown()
{
	delete game;
	MenuSystem::Destroy();
	UIManager::Destroy();
	GameDataManager::Destroy();
	AssetLoader::Destroy();
	AudioEngine::Destroy();
	delete graphics;
	delete window;
	
	game = nullptr;
	graphics = nullptr;
	window = nullptr;	

	SettingsManager::Destroy();
	Logger::LogInfo("Destroy Game.");
}

LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return game->MessageHandler(hWindow, msg, wParam, lParam);
}