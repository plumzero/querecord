
#include <iostream>

class Polygon
{
protected:
	int width, height;
public:
	void set_value(int a, int b) { width = a; height = b; }
	virtual int area() { return 0; }
};

class Rectangle : public Polygon
{
public:
	int area() { return width * height; }
};

class Triangle : public Polygon
{
public:
	int area() { return (width * height) / 2; }
	int print() { std::cout << "Triangle" << std::endl; }
};

int main()
{
	Rectangle rect;
	Triangle trgl;
	Polygon poly;
	Polygon* ppoly1 = &rect;
	Polygon* ppoly2 = &trgl;
	Polygon* ppoly3 = &poly;
	ppoly1->set_value(4, 5);
	ppoly2->set_value(4, 5);
	ppoly3->set_value(4, 5);
	std::cout << ppoly1->area() << std::endl;
	std::cout << ppoly2->area() << std::endl;
	std::cout << ppoly3->area() << std::endl;
	ppoly2->print();
	
	return 0;
}