#include "ion.h"


float ion::returndt(void)
{
  return dt;
}


void ion::derivative(float z, float vz, float& dzdt, float& dvzdt, float Ez)
{
  float a = charge*Ez/mass;
  dzdt = vz;
  dvzdt = a;
}




void ion::rungeKutta4th(float& z, float& vz, float t, float Ez)
{
  float dz1, dv1, dz2, dv2, dz3, dv3, dz4, dv4;
  derivative(z, vz, dz1, dv1, Ez);
  derivative(z + dz1*dt/2, vz + dv1*dt/2, dz2, dv2, Ez);
  derivative(z + dz2*dt/2, vz + dv2*dt/2, dz3, dv3, Ez);
  derivative(z + dz3*dt, vz + dv3*dt, dz4, dv4, Ez);
  z  += (dz1 + 2*dz2 + 2*dz3 + dz4)*dt/6;
  vz += (dv1 + 2*dv2 + 2*dv3 + dv4)*dt/6;
}

