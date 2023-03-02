#ifndef ION_H
#define ION_H

#include <cmath>
#include <iostream>

using namespace std;

class ion
{
private:
  
  const float mass = 6.6335209e-26;    // Mass of Argon ion in kg
  const float charge = 1.60217662e-19; // Charge of Argon ion in Coulombs
  const float dt = 1.0e-10;  //time step  
  
public:
  
  float returndt(void);
  float returnMass(void);
  float returnCharge(void);
  
  void derivative(float z, float vz, float& dzdt, float& dvzdt, float Ez);
  void rungeKutta4th(float& z, float& vz, float t, float Ez);
  
  
};

#endif // ION
