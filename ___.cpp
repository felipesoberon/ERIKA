#include <iostream>
#include <cmath>

using namespace std;

// Constants
const double M = 6.6335209e-26;   // Mass of Argon ion in kg
const double q = 1.60217662e-19;  // Charge of Argon ion in Coulombs
const double Ez = 1000.0;         // Electric field strength in V/m

// Time step
const double dt = 1.0e-12;


void derivative(double z, double v, double& dzdt, double& dvdt) {
  double a = q*Ez/M;
  dzdt = v;
  dvdt = a;
}


void rungeKutta4th(double& z, double& v, double t) {
  double dz1, dv1, dz2, dv2, dz3, dv3, dz4, dv4;
  derivative(z, v, dz1, dv1);
  derivative(z + dz1*dt/2, v + dv1*dt/2, dz2, dv2);
  derivative(z + dz2*dt/2, v + dv2*dt/2, dz3, dv3);
  derivative(z + dz3*dt, v + dv3*dt, dz4, dv4);
  z += (dz1 + 2*dz2 + 2*dz3 + dz4)*dt/6;
  v += (dv1 + 2*dv2 + 2*dv3 + dv4)*dt/6;
}

int main()
{
  double z = 0.0;          // Initial position of the particle in m
  double v = 0.0;          // Initial velocity of the particle in m/s
  double t = 0.0;          // Initial time in seconds
  
  // Simulation loop
  while (t < 1.0e-6) {     // Integrate for 1 microsecond
    
    // Integrate position and velocity using the fourth-order Runge-Kutta method
    rungeKutta4th(z, v, t);
    
    // Print the position of the particle at each time step
    cout << "t = " << t << ", z = " << z << endl;
    
    // Update time
    t += dt;
  }
  
  return 0;
}
