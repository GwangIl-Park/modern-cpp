#include <math.h>

class Point
{
  Point(const float x, const float y)
    : x{x}, y{y}{}

  Point(const float r, const float theta)
  {
    x = r * cos(theta);
    y = r * sin(theta);
  }
  
  float x, y;
};