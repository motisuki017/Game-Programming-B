#include "Shape.h"

Shape::Shape()
{
    x = 0;
    y = 0;
}

Shape::Shape(double ix, double iy)
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

void Shape::SetCenter(double ix, double iy)
{
    x = ix;
    y = iy;
}
