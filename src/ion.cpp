#include "ion.h"


float ion::returndt(void) { return dt; }

float ion::returnMass(void) { return mass; }
float ion::returnCharge(void) { return charge; }
float ion::averageVelocity(void) { return sqrt(3.0 * k * T / mass); }

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


float ion::magnitude(float x, float y, float z) { return sqrt(x*x + y*y + z*z); }


float ion::magnitudeSquare(float x, float y, float z) { return x*x + y*y + z*z; }


void ion::normalize(float& x, float& y, float& z)
{
  float mag = magnitude(x, y, z);
  x = x / mag;
  y = y / mag;
  z = z / mag;
}


float ion::totalKineticEnergy(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z)
{
  float m = 39.948; // mass of argon atom in atomic mass units (AMU)
  float ke1 = 0.5*m*magnitudeSquare(v1x, v1y, v1z);
  float ke2 = 0.5*m*magnitudeSquare(v2x, v2y, v2z);
  float totalKE = ke1 + ke2;
  return totalKE;
}



void ion::randomAverageVelocityVector(float& vx, float& vy, float& vz)
{
  float meanV  = averageVelocity();
  float psi    = M_PI * random01();
  float theta  = 2 * M_PI * random01();
  
  vx = meanV * cos(psi);
  vy = meanV * sin(psi) * cos(theta);
  vz = meanV * sin(psi) * sin(theta); 
}



void ion::collision(float& v1z, float& v1y, float& v1x)
{
  float vx,  vy,  vz;
  float v2x, v2y, v2z;
  randomAverageVelocityVector(v2z, v2y, v2x);
  subtractVectors(vx,  vy,  vz,
		  v1x, v1y, v1z,
		  v2x, v2y, v2z);
  float beta = alpha(vz, vy);
  rotateVector(vz, vy, beta);
  float v = vz;
  float theta = 0.5 * M_PI * random01();
  float costheta = cos(theta);
  float sintheta = sin(theta);
  vz = v * costheta * costheta;
  vy = v * costheta * sintheta;
  rotateVector(vz, vy, -beta);
  addVectors(v1x, v1y, v1z,
	     vx,  vy,  vz,
	     v2x, v2y, v2z);
}




void ion::collision(float& v, float& v_)
{
  // Define the initial velocities of the particles
  float v1x = - magnitude(v, v_, 0.0);
  float v1y = 0.0;
  float v1z = 0.0;
  
  float v2x = 0.0;
  float v2y = 0.0;
  float v2z = 0.0;
  
  // Calculate the center of mass velocity
  float vcmx = (v1x + v2x)/2.0;
  float vcmy = (v1y + v2y)/2.0;
  float vcmz = (v1z + v2z)/2.0;
  
  // Transform to the center of mass frame
  v1x = v1x - vcmx;
  v1y = v1y - vcmy;
  v1z = v1z - vcmz;

  v2x = v2x - vcmx;
  v2y = v2y - vcmy;
  v2z = v2z - vcmz;
  
  // Calculate the relative velocity
  float vr1x = v1x - v2x;
  float vr1y = v1y - v2y;
  float vr1z = v1z - v2z;
  
  // Calculate the scattering angle using a random number generator
  float theta = acos(2*random01() - 1); // Random angle between 0 and pi
  
  // Calculate the new velocities in the center of mass frame
  float vr2x =  vr1x*cos(theta) + vr1y*sin(theta);
  float vr2y = -vr1x*sin(theta) + vr1y*cos(theta);
  
  // Transform back to the lab frame
  v1x = vcmx + 0.5*vr2x;
  v1y = vcmy + 0.5*vr2y;
  
  float meanV = averageVelocity();
  float psi = M_PI * random01();
  theta  = 2 * M_PI * random01();
 
  v  = v1x + meanV * cos(psi);
  v_ = v1y + meanV * sin(psi) * cos(theta); 
}




void ion::setCrossSection(int n, float factor)
{
  process = new XSection[n+1];
  numberCollisionProcesses = n;
  crossSectionFactor = factor;
}


void ion::setCrossSection(int i, char * name) { process[i].Setup(name); }


float ion::sigma(int i, float energy)
{
  float temp;
  temp = process[i].sigma_(energy) * crossSectionFactor;
  return temp;
}


float ion::crossSectionThreshold(int i) { return process[i].threshold_(); }


void ion::printCollisionProcess(int i) { process[i].printProcessName(); }


char * ion::collisionProcessName(int i) { return process[i].process__(); }


