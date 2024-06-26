#include <math.h>

class Point
{
protected:
  Point(const float x, const float y)
    : x{x}, y{y} {}
public: 
  static Point NewCartesian(float x, float y)
  {
    return {x, y};
  }
  static Point NewPolar(float r, float theta)
  {
    return { r * cos(theta), r * sin(theta)};
  }
  float x, y;
};

int main()
{
  auto p = Point::NewPolar(5, 4);
}