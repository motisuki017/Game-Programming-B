#include <iostream>
#include "Rectangle.h"
#include "Circle.h"

using namespace std;

// TODO: main関数は書き換えずに正常動作するプログラムを作成
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

