#include <iostream>
#include "Rectangle.h"

// TOOD: Rectangleクラスの宣言をRectangle.hに，定義をRectangle.cppに分解
class Rectangle
{
public:
    Rectangle(int ileft, int itop, int iwidth, int iheight)
    {
        left = ileft;
        top = itop;
        width = iwidth;
        height = iheight;
    }
public:
    int Width() const
    {
        return width;
    }
    int Height() const
    {
        return height;
    }
    int Area()
    {
        return width * height;
    }
private:
    int width;
    int height;
    int left;
    int top;
};

int main()
{
    Rectangle rect(0, 0, 50, 20);
    std::cout << "W" << rect.Width() << " x ";
    std::cout << "H" << rect.Height() << " = ";
    std::cout << rect.Area() << std::endl;
}
