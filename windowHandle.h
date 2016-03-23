#pragma once

class WindowHandle
{
public:
	WindowHandle(std::string windowName);

	sf::Color getPixelValue(const sf::Vector2u& position);

	HWND getCurrentHandle();

private:
	sf::Image captureCurrentWindowImage();

private:
	HWND _currentHandle;
	sf::Texture _texture;
};

