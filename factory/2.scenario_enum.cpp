#include <math.h>

enum class PointType
{
  cartesian,
  polar
};

class Point
{
  Point(const float a, const float b, PointType type = PointType::cartesian)
  {
    if(type == PointType::cartesian)
    {
      x = a;
      y = b;
    }
    else
    {
      x = a * cos(b);
      y = a * sin(b);
    }
  }  
  float x, y;
};