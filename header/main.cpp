#include <iostream>
#include "Rectangle.h"

int main()
{
    Rectangle rect(0, 0, 50, 20);
    std::cout << "W" << rect.Width() << " x ";
    std::cout << "H" << rect.Height() << " = ";
    std::cout << rect.Area() << std::endl;
}
