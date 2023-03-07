#include "functions.h"

float alpha(float x, float y) { return atan2(y,x); }


void rotateVector(float& x, float& y, float alpha)
{
  float x2, y2;
  alpha = -1.0 * alpha;

  x2 = x*cos(alpha) - y*sin(alpha);
  y2 = x*sin(alpha) + y*cos(alpha);

  x = x2;
  y = y2;
}


void addVectors(float& x, float& y, float& z,
		float x1, float y1, float z1,
		float x2, float y2, float z2)
{
  x = x1 + x2;
  y = y1 + y2;
  z = z1 + z2;
}


void subtractVectors(float& x, float& y, float& z,
		     float x1, float y1, float z1,
		     float x2, float y2, float z2)
{
  x = x1 - x2;
  y = y1 - y2;
  z = z1 - z2;
}
