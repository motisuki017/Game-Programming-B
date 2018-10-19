#ifndef Shape_hpp
#define Shape_hpp
#pragma once

class Shape
{
public:
    Shape();
    Shape(double ix, double iy);
public:
    virtual double Area() const = 0;
    virtual double Circumference() const = 0;
protected:
    double x;
    double y;
};

#endif
