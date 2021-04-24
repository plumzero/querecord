
#include <iostream>

class Polygon
{
protected:
    int width, height;
public:
    void set_value(int a, int b) { width = a; height = b; }
    int area() {}
};

class Rectangle : public Polygon
{
public:
    int area() { return width * height; }
};

class Triangle : public Polygon
{
public:
    int area() { return width * height / 2; }
};

int main()
{
    Rectangle rect;
    Triangle trgl;
    Polygon* ppoly1 = &rect;
    Polygon* ppoly2 = &trgl;
    ppoly1->set_value(4, 5);
    ppoly2->set_value(4, 5);
    std::cout << rect.area() << std::endl;
    std::cout << trgl.area() << std::endl;
    
    return 0;
}