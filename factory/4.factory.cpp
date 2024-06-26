#include <math.h>

class Point
{
  float x,y;
  friend class PointFactory;
private:
  Point(float x, float y) : x(x), y(y) {}
};

class PointFactory
{
public: 
  static Point NewCartesian(float x, float y)
  {
    return {x, y};
  }
  static Point NewPolar(float r, float theta)
  {
    return { r * cos(theta), r * sin(theta)};
  }
};

int main()
{
  auto p = PointFactory::NewPolar(5, 4);
}