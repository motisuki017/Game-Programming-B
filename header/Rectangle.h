#ifndef Rectangle_h
#define Rectangle_h
#pragma once

// RectangleƒNƒ‰ƒX‚ÌéŒ¾
class Rectangle
{
public:
    Rectangle(int ileft, int itop, int iwidth, int iheight);
public:
    int Width() const;
    int Height() const;
    int Area();
private:
    int width;
    int height;
    int left;
    int top;
};

#endif
