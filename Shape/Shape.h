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
    Shape(int ix, int iy);
public:
    double X();
    double Y();
    void SetCenter(int ix, int iy);
private:
    double x;
    double y;
};

#endif
