#include "collision.h"

float magnitude(float x, float y, float z) { return sqrt(x*x + y*y + z*z); }

void normalize(float& x, float& y, float& z)
{
  float mag = magnitude(x, y, z);
  x /= mag;
  y /= mag;
  z /= mag;
}

float collision(float v)
{
  // Define the initial velocities of the particles
  float v1x = v;
  float v1y = 0;
  float v1z = 0.0;
  float v2x = 0;
  float v2y = 0;
  float v2z = 0.0;
  
  // Calculate the initial total kinetic energy and momentum
  float m = 39.948; // mass of argon atom in atomic mass units (AMU)
  float ke1 = 0.5*m*magnitude(v1x, v1y, v1z)*magnitude(v1x, v1y, v1z);
  float ke2 = 0.5*m*magnitude(v2x, v2y, v2z)*magnitude(v2x, v2y, v2z);
  float totalKE = ke1 + ke2;
  float px = m*(v1x + v2x);
  float py = m*(v1y + v2y);
  float pz = m*(v1z + v2z);

  //cout << "Total Kinetic energy before collision " << totalKE << endl;
  
  // Calculate the center of mass velocity
  float vcmx = px/(2*m);
  float vcmy = py/(2*m);
  float vcmz = pz/(2*m);
  
  // Transform to the center of mass frame
  v1x -= vcmx;
  v1y -= vcmy;
  v1z -= vcmz;
  v2x -= vcmx;
  v2y -= vcmy;
  v2z -= vcmz;
  
  // Calculate the relative velocity
  float vr1x = v1x - v2x;
  float vr1y = v1y - v2y;
  float vr1z = v1z - v2z;
  
  // Calculate the scattering angle using a random number generator
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(0, 1);
  float theta = acos(2*dis(gen) - 1); // Random angle between 0 and pi
  
  // Calculate the new velocities in the center of mass frame
  float vr2x = vr1x*cos(theta) + vr1y*sin(theta);
  float vr2y = -vr1x*sin(theta) + vr1y*cos(theta);
  
  // Transform back to the lab frame
  v1x = vcmx + 0.5*vr2x;
  v1y = vcmy + 0.5*vr2y;
  v1z = vcmz + 0.5*vr1z;
  v2x = vcmx - 0.5*vr2x;
  v2y = vcmy - 0.5*vr2y;
  v2z = vcmz - 0.5*vr1z;
  
  // Calculate the final total kinetic energy and momentum
  ke1 = 0.5*m*magnitude(v1x, v1y, v1z)*magnitude(v1x, v1y, v1z);
  ke2 = 0.5*m*magnitude(v2x, v2y, v2z)*magnitude(v2x, v2y, v2z);
  totalKE = ke1 + ke2;

  //cout << "Kinetic energy after collision " << totalKE << endl;
  //cout << "v1 after collision " << v1x << " " << v1y << " " << v1z << endl;
  //cout << "v2 after collision " << v2x << " " << v2y << " " << v2z << endl;

  return v1x;
}



//int main() { cout << collision(-1) << endl;	 }