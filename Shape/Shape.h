#ifndef Shape_h
#define Shape_h
#pragma once

class Shape
{
public:
    virtual double Area() const = 0;
    virtual double Circumference() const = 0;
public:
    Shape();
    Shape(double ix, double iy);
public:
    double X();
    double Y();
    void SetCenter(double ix, double iy);
private:
    double x;
    double y;
};

#endif
