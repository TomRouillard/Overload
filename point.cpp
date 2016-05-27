#include "stdafx.h"
#include "point.h"

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Point::determinePoint(int dir, int x_start, int y_start)
{
    switch(dir)
    {
    case 0:
        x = x_start - 1;
        y = y_start;
        break;
    case 1:
        x = x_start - 1;
        y = y_start + 1;
        break;
    case 2:
        x = x_start;
        y = y_start + 1;
        break;
    case 3:
        x = x_start + 1;
        y = y_start + 1;
        break;
    case 4:
        x = x_start + 1;
        y = y_start;
        break;
    case 5:
        x = x_start + 1;
        y = y_start - 1;
        break;
    case 6:
        x = x_start;
        y = y_start - 1;
        break;
    case 7:
        x = x_start - 1;
        y = y_start - 1;
        break;
    }
}
