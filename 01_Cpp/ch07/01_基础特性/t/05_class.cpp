
#include <iostream>

class Point {
public:
  constexpr Point(double x = 0, double y = 0) noexcept
    : _x(x), _y(y) {}
  constexpr double x() const noexcept { return _x; }
  constexpr double y() const noexcept { return _y; }
  void set_x(double x) noexcept { _x = x; }
  void set_y(double y) noexcept { _y = y; }
private:
  double _x, _y;
};

constexpr Point midpoint(const Point& p1, const Point& p2) noexcept {
  return { (p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2 };
}

int main()
{
  constexpr Point p1(9.4, 27.7);
  constexpr Point p2(28.8, 5.3);

  constexpr auto mid = midpoint(p1, p2);

  std::cout << "x = " << mid.x() << std::endl;
  std::cout << "y = " << mid.y() << std::endl;

  return 0;
}