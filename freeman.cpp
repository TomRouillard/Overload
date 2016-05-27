#include "stdafx.h"
#include "freeman.h"
#include <algorithm>
#include <SFML/Graphics.hpp>


void Freeman::setImage(sf::Image img)
{
	_img = img;
}

void Freeman::setComparativePictures(std::string filePath)
{
	_filePath = filePath;
}

std::string Freeman::freeman(int** img, sf::Vector2u size, int& lastX)
{
	std::string result;
    std::vector<int> code_freeman;
    Point p;
    Point p_start;
    Point p_current;
    for(unsigned int i=0; i<size.x; i++)
    {
        bool found = false;
        for(unsigned int j = 0; j < size.y; j++)
        {
            if(img[i][j] == 0)
            {
                p = Point(i, j);
                found = true;
				lastX = i;
                break;
            }
        }
        if (found)
            break;
    }
	
    p_start = p;
    for(int i=2; i<6; i++)
    {
        p_current = p_start;
        p_current.determinePoint(i, p_current.getX(), p_current.getY());
        if(img[p_current.getX()][p_current.getY()] == 0)
        {
            code_freeman.push_back(i);
            break;
        }

    }
	
    while(!equal(p_start, p_current))
    {
        Point p_temp;
        int dir = ((code_freeman.at(code_freeman.size()-1)+4)%8)+1;
        dir = dir % 8;
        do
        {
            p_temp = p_current;
            p_temp.determinePoint(dir, p_current.getX(), p_current.getY());
			if (dir == 7)
            {
                dir = 0;
            }
            else
            {
                dir++;
            }

			if(p_temp.getX() > lastX)
			{
				lastX = p_temp.getX();
			}
        }
        while(img[p_temp.getX()][p_temp.getY()] != 0);
		
        if (dir == 0) dir = 8;
        code_freeman.push_back(dir-1);
        p_current = p_temp;
		
    }
	
	for(unsigned int i = 0; i < code_freeman.size(); i++)
    {
        std::ostringstream oss;
        oss << code_freeman.at(i);
        result.append(oss.str());
    }
	return result;
}

bool Freeman::equal(Point p1, Point p2)
{
    return ((p1.getX() == p2.getX()) && (p1.getY() == p2.getY()));
}

float Freeman::editDistance(std::string str1, std::string str2, float cout_substitution, float cout_insertion, float cout_suppresion)
{
	int t = str1.size();
	int v = str2.size();
	float** d = new float*[t+1];
	for(int i = 0; i < t+1; i++)
	{
		d[i] = new float[v+1];
	}

	float d1,d2,d3;
	for(int r = 0; r <= t; r++)
	{
		for(int k = 0; k <= v; k++)
		{
			d[r][k]=0;
		}
	}
	for(int r = 1; r <= t; r++)
	{
		d[r][0] = d[r-1][0] + cout_suppresion;
	}
	for(int k = 1; k <= v; k++)
	{
		d[0][k] = d[0][k-1] + cout_insertion;
	}
	for(int r = 1; r <= t; r++)
	{
		for(int k = 1;k <= v; k++)
		{
			if(str1.at(r-1) == str2.at(k-1))
				d1 = d[r-1][k-1] + 0;
			else
				d1 = d[r-1][k-1]  + cout_substitution;
			d2 = d[r-1][k] + cout_insertion;
			d3 = d[r][k-1] + cout_suppresion;
			d[r][k] = (std::min)((std::min)(d1, d2), d3);
		}
	}
	
	return d[t][v];
}

int Freeman::readNumber()
{

	int result = -1;
	sf::Vector2u imgSize = _img.getSize();

    int** t2 = new int*[imgSize.x];
	for(unsigned int i = 0; i < imgSize.x; i++)
	{
		t2[i] = new int[imgSize.y];
	}

    bool empty = true;
    for (unsigned int i = 0; i < imgSize.x; i++)
    {
        for (unsigned int j = 0; j < imgSize.y; j++)
        {
			sf::Color pixel = _img.getPixel(i,j);
            if (pixel == sf::Color::Black)
			{
				empty = false;
			}
            t2[i][j] = pixel.g/255;
        }
    }
	
    if(!empty)
    {
		int lastX = 0;
		while(imgSize.x - lastX > 7)
		{
			sf::Vector2u newSize(imgSize.x - lastX, imgSize.y);
			int** tmp = new int*[newSize.x];
			for(unsigned int i = 0; i < newSize.x; i++)
			{
				tmp[i] = new int[newSize.y];
			}
			
			memcpy(tmp, t2+lastX, newSize.x * newSize.y);
			
			std::string freemanCode = freeman(tmp, imgSize, lastX);
			lastX++;
			std::ifstream file(_filePath.c_str(), std::ios::in);

			std::string line;
			char classe;
			float distance_min;

			getline(file, line);
			classe = line.at(0);
			line.erase(0, 1);

			distance_min = editDistance(freemanCode, line, 4, 0.5, 0.5);
		
			while(getline(file, line))
			{
				char c = line.at(0);
				line.erase(0, 1);

				float d = editDistance(freemanCode, line, 4, 0.5, 0.5);

				if(d<distance_min)
				{
					distance_min=d;
					classe=c;
				}

			}
			result = classe;
		}
    }
	
	for(unsigned int i = 0; i < imgSize.x; i++)
	{
		delete[] t2[i];
	}
	
	delete[] t2;
	return result;
}

