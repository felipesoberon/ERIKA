#include "integration.h"


float integration::trapezoidalIntegration(const function<float(float)>& f, float a, float b, int n)
{
  float h = (b - a) / n;
  float result = 0.5 * (f(a) + f(b));
  
  for (int i = 1; i < n; ++i) {
    result += f(a + i * h);
  }
  
  return result * h;
}

float integration::adaptiveTrapezoidalIntegration(const function<float(float)>& f, float a, float b,
						  float precision, int significant_digits = 0)
{
  int n = 1;
  float old_sum = trapezoidalIntegration(f, a, b, n);
  float new_sum;
  
  do {
    n *= 2;
    new_sum = trapezoidalIntegration(f, a, b, n);
    
    if (significant_digits > 0)
      {
	float relative_error = abs((new_sum - old_sum) / new_sum);
	float required_relative_error = pow(10, -significant_digits);
	
	if (relative_error < required_relative_error)
	  {
	    break;
	  }
      }
    else if (abs(new_sum - old_sum) < precision)
      {
	break;
      }
    
    old_sum = new_sum;
  } while (true);
  
  return new_sum;
}

