#include <iostream>
#include "Shape.h"

int main()
{
    const int NumShapes = 6;
    Shape *shapes[NumShapes];
    
    // data input
    for (int i = 0; i < NumShapes; ++i)
    {
        int type;
        double cx, cy;
        std::cin >> type;
        std::cin >> cx >> cy;
        std::cout << type << ", ";
        std::cout << cx << ", " << cy << std::endl;
    }
    
    // data output
    for (int i = 0; i < NumShapes; ++i)
    {
    }
    
    std::cout << "Finished" << std::endl;
}
