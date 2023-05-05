#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

namespace integration
{
  float trapezoidalIntegration(const function<float(float)>& f, float a, float b, int n);
  float adaptiveTrapezoidalIntegration(const function<float(float)>& f, float a, float b, float precision, int significant_digits);
}
