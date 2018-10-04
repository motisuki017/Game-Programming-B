#include <iostream>
#include "Rectangle.h"
#include "Circle.h"

using namespace std;

int main()
{
    Circle circle(100.0, 100.0, 50.0);
    cout << "[" << circle.X() << ", " << circle.Y() << "], " << circle.Radius() << endl;
    cout << circle.Area() << ", " << circle.Circumference() << endl;

    Rectangle rect(100.0, 100.0, 100.0, 50.0);
    cout << "[" << rect.X() << ", " << rect.Y() << "], ";
    cout << "[" << rect.Width() << ", " << rect.Height() << "]" << endl;
    cout << rect.Area() << ", " << rect.Circumference() << endl;
}

