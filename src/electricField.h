#ifndef ELECTRICFIELD_H
#define ELECTRICFIELD_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "plasma.h"

using namespace std;

class electricField
{
  
private:

  plasma Plasma;
  
  float sheathSize; 
  float G0G1d, G1G2d, G2G3d, G3Cd;  
  float zP, z0, z1, z2, z3, zC;
  float plasmaPotential;
  float plasmaDensity;
  float G0, G1, G2, G3, C;
  float E_z, V_z;
  
  struct point {float x, y;};  
  float interpolate(point p1, point p2, float x);
  
  
public:
  
  void  setSheathSize(void);
  
  void  setG0G1d(float inputDistance);
  void  setG1G2d(float inputDistance);
  void  setG2G3d(float inputDistance);
  void  setG3Cd(float inputDistance);
  
  void  setCoordinate(void);
  
  void  setPlasmaPotential(float inputPlasmaPotential, float inputPlasmaDensity);
  
  void  setG0(float inputG0);
  void  setG1(float inputG1);
  void  setG2(float inputG2);
  void  setG3(float inputG3);
  void  setC(float inputC);
  
  float returnzP(void);
  float returnzG0(void);
  float returnzG1(void);
  float returnzG2(void);
  float returnzG3(void);
  float returnzC(void);
  
  float returnElectricField(float z);
  float returnVoltage(float z);
  
  void  saveVoltageAndElectricField(const string& fileName);
  
  
};

#endif // ELECTRICFIELD
