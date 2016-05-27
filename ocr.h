#pragma once
#include <SFML/Graphics.hpp>

class OCR
{
public:
	virtual std::string getText(const sf::Image& image) = 0;

	virtual int getNumber(const sf::Image& image) = 0;
};
