#include "Rectangle.h"

Rectangle::Rectangle(int ileft, int itop, int iwidth, int iheight)
{
    left = ileft;
    top = itop;
    width = iwidth;
    height = iheight;
}

int Rectangle::Width() const
{
    return width;
}

int Rectangle::Height() const
{
    return height;
}

int Rectangle::Area()
{
    return width * height;
}
