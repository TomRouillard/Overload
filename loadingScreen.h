#pragma once
#include "webview.h"
#include "windowHandle.h"

#define LOADING_SCREEN_URL "assets/loadingScreen/overloader/index.html"  
#define LOL_WINDOW_NAME "League of Legends (TM) Client"
#define GAME_INFO_KEY "gameInfo"
#define IMAGE_DIRECTORY_KEY "imageDirectory"

#define LOADINGSCREEN_TITLE L"Overload"
#define LOADINGSCREEN_CLASSNAME L"Overload"

class LoadingScreen
{
public:
	LoadingScreen();

	void displayLoop(std::string gameInfo, std::string imageDirectory);

	static LRESULT CALLBACK windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void lookForPixelValue();

	HWND createWindow();

private:
	HWND _handle;
	CefRefPtr<Webview> _loadingWebview;
	sf::RenderWindow _loadingWindow;
	WindowHandle _lolWindowHandle;
	std::thread _pixelValueThread;
};

