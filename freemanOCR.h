#pragma once
#include "ocr.h"
#include "freeman.h"

class FreemanOCR: public OCR
{
public:
	FreemanOCR();

	std::string getText(const sf::Image& image);

	int getNumber(const sf::Image& image);

private:
	Freeman _freeman;
};

