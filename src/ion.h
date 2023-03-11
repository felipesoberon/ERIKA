#ifndef ION_H
#define ION_H

#include <cmath>
#include <iostream>
#include "random.h"
#include "functions.h"
#include "XSection.h"

using namespace std;

class ion
{
private:

  const float k = 1.3806503E-23; //m2 kg s-1 K-1
  const float T = 300.0; //Kelvin
  const float mass = 6.6335209e-26;    // Mass of Argon ion in kg
  const float charge = 1.60217662e-19; // Charge of Argon ion in Coulombs
  const float dt = 1.0e-10;  //time step  

  XSection * process;            //Array of cross sections for all collision processes of the specie
  int numberCollisionProcesses;  //Number of collision processes to be considered per specie
  float crossSectionFactor;      //Order of magnitude factor to get the area in m^2
  
public:
  
  float returndt(void);
  float returnMass(void);
  float returnCharge(void);
  float averageVelocity(void);
  
  void derivative(float z, float vz, float& dzdt, float& dvzdt, float Ez);
  void rungeKutta4th(float& z, float& vz, float t, float Ez);
  
  float magnitude(float x, float y, float z);
  float magnitudeSquare(float x, float y, float z);
  void  normalize(float& x, float& y, float& z);
  float totalKineticEnergy(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z);
  void  randomAverageVelocityVector(float& vx, float& vy, float& vz);
  float kineticEnergyeV(float vx, float vy, float vz);

  void collision(float& v1z, float& v1y, float& v1x);
  
  void  setCrossSection(int n, float factor);
  void  setCrossSection(int i, char * name);
  float crossSectionThreshold(int i);
  float sigma(int i, float energy);
  void  printCollisionProcess(int i);
  char * collisionProcessName(int i);
  
};

#endif // ION
