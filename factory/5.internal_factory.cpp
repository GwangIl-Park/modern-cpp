#include <math.h>

class Point
{
private:
  Point(float x, float y) : x(x), y(y) {}
  
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

public:
  float x,y;
  static PointFactory Factory;
  //typedef PointFactory Factory;
};

int main()
{
  //auto p = Point::PointFactory::NewPolar(5, 4);
  
  auto p = Point::Factory.NewPolar(5, 4);

  //auto p = Point::Factory::NewPolar(5, 4);
}