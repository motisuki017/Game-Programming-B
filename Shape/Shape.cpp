#include "Shape.h"

Shape::Shape()
{
    x = 0;
    y = 0;
}

Shape::Shape(int ix, int iy)
{
    x = ix;
    y = iy;
}

double Shape::X()
{
    return x;
}

double Shape::Y()
{
    return y;
}

void Shape::SetCenter(int ix, int iy)
{
    x = ix;
    y = iy;
}
