#pragma once

class Point {
    int x;
    int y;
public:
    Point(int x = 0, int y = 0);
    int getX() {return x;}
    int getY() {return y;}
    void determinePoint(int dir, int x_start, int y_start);
};
