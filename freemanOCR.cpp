#include "stdafx.h"
#include "freemanOCR.h"

FreemanOCR::FreemanOCR()
{
	_freeman.setComparativePictures("content/freeman/defaultPictures.fre");
}


std::string FreemanOCR::getText(const sf::Image& image)
{
	return "";
}

int FreemanOCR::getNumber(const sf::Image& image)
{
	_freeman.setImage(image);
	return _freeman.readNumber();
}