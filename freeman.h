#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "point.h"

class Freeman
{
public:
	void setImage(sf::Image img);

    int readNumber();

	void setComparativePictures(std::string filePath);

protected:
    std::string freeman(int** m, sf::Vector2u size, int& lastX);

    bool equal(Point p1, Point p2);

    float editDistance(std::string str1, std::string str2, float cout_substitution, float cout_insertion, float cout_suppresion);

private:
    sf::Image _img;
	std::string _filePath;
};