#include "stdafx.h"
#include "LoadingScreen.h"

LoadingScreen::LoadingScreen() : _lolWindowHandle(LOL_WINDOW_NAME),
								 _loadingInProgress(true)
{
	_handle = createWindow();
	_pixelValueThread = std::thread(&LoadingScreen::lookForPixelValue, this);
}

HWND LoadingScreen::createWindow()
{
	HMODULE module = GetModuleHandleW(NULL);
	WNDCLASSW windowClass;
	windowClass.style = 0;
	windowClass.lpfnWndProc = &LoadingScreen::windowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = module;
	windowClass.hIcon = NULL;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = LOADINGSCREEN_CLASSNAME;
	RegisterClassW(&windowClass);
	HWND _handle = CreateWindowW(LOADINGSCREEN_CLASSNAME, LOADINGSCREEN_TITLE, WS_POPUP, 0, 0, 1920, 1080, NULL, NULL, module, this);
	ShowWindow(_handle, SW_SHOWMAXIMIZED);
	SetForegroundWindow(_handle);
	return _handle;
}

void LoadingScreen::displayLoop(std::string gameInfo, std::string imageDirectory)
{
	_loadingWebview = new Webview(_handle, "Overload");
	_loadingWebview->synchronizeVariant(GAME_INFO_KEY, gameInfo);
	_loadingWebview->synchronizeVariant(IMAGE_DIRECTORY_KEY, imageDirectory);
	std::string currentDirectory = utils::FileUtils::getCurrentDirectory() + "/";
	_loadingWebview->loadUrl("file://" + currentDirectory + LOADING_SCREEN_URL);

	while (_loadingInProgress)
	{
		Webview::updateWebviews();
	}
	_loadingWebview->close();
	DestroyWindow(_handle);
	_pixelValueThread.join();
}

LRESULT CALLBACK LoadingScreen::windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CLOSE:
		{
			break;
		} 
		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void LoadingScreen::lookForPixelValue()
{
	// Look at a specific pixel color to determine if the game loader started
	sf::Color color = _lolWindowHandle.getPixelValue(sf::Vector2u(0, 0));
	while (color == sf::Color::Black)
	{
		color = _lolWindowHandle.getPixelValue(sf::Vector2u(0, 0));
		Sleep(100);
	}

	// Loading screen available
	LOG(INFO) << "Game is loading.";
	sf::Color color2 = _lolWindowHandle.getPixelValue(sf::Vector2u(0, 0));
	while (utils::SFMLUtils::isColorNear(color2, color, 10))
	{
		color2 = _lolWindowHandle.getPixelValue(sf::Vector2u(0, 0));
		Sleep(100);
	}
	// Loading screen ended, we must close the window
	LOG(INFO) << "Loading screen ended.";
	_loadingInProgress = false;
}