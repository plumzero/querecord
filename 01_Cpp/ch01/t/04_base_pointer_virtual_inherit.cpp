#include <iostream>

class Polygon
{
protected:
    int width, height;
public:
    virtual ~Polygon(){}    // 方法1
    void set_value(int a, int b) { width = a; height = b; }
    virtual int area() { return 0; }   // 方法2
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
    
    // 派生类直接访问
    std::cout << rect.area() << std::endl;
    std::cout << trgl.area() << std::endl;
    
    // 方法1: 转换为派生类访问
    std::cout << dynamic_cast<Rectangle*>(ppoly1)->area() << std::endl;
    std::cout << dynamic_cast<Triangle*>(ppoly2)->area() << std::endl;
    
    // 方法2: 虚成员访问
    std::cout << ppoly1->area() << std::endl;
    std::cout << ppoly2->area() << std::endl;
    
    return 0;
}