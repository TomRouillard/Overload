#include "stdafx.h"
#include "windowHandle.h"


WindowHandle::WindowHandle(std::string windowName)
{
	_currentHandle = FindWindow(NULL, utils::StringUtils::stringToWString(windowName).c_str());
	while (_currentHandle == nullptr)
	{
		Sleep(100);
		_currentHandle = FindWindow(NULL, utils::StringUtils::stringToWString(windowName).c_str());
	}
}

sf::Color WindowHandle::getPixelValue(const sf::Vector2u& position)
{
	sf::Color result;
	sf::Image currentWindowImage = captureCurrentWindowImage();
	if (position.x < currentWindowImage.getSize().x && position.y < currentWindowImage.getSize().y)
	{
		result = currentWindowImage.getPixel(position.x, position.y);
	}
	return result;
}

sf::Image WindowHandle::captureCurrentWindowImage()
{
	WINDOWPLACEMENT wp = { 0 };
	wp.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(_currentHandle, &wp);

	ShowWindow(_currentHandle, SW_SHOWNOACTIVATE);

	return utils::WindowUtils::captureImageFromWindow(_currentHandle);
}

HWND WindowHandle::getCurrentHandle()
{
	return _currentHandle;
}