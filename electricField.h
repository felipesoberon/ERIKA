#ifndef ELECTRICFIELD_H
#define ELECTRICFIELD_H

#include <iostream>
#include <cmath>

using namespace std;

class electricField
{
  
private:
  
  float sheathSize; 
  float G0G1d, G1G2d, G2G3d, G3Cd;  
  float zP, z0, z1, z2, z3, zC;
  float plasmaPotential;
  float G0, G1, G2, G3, C;
  float E_z;
  
  
public:
  
  void  setSheathSize(float inputSheathSize);
  
  void  setG0G1d(float inputDistance);
  void  setG1G2d(float inputDistance);
  void  setG2G3d(float inputDistance);
  void  setG3Cd(float inputDistance);
  
  void  setCoordinate(void);
  
  void  setPlasmaPotential(float inputPlasmaPotential);
  
  void  setG0(float inputG0);
  void  setG1(float inputG1);
  void  setG2(float inputG2);
  void  setG3(float inputG3);
  void  setC(float inputC);
  
  float returnElectricField(float z);
  
  void  showElectricField(void);
  
  
  
};

#endif // ELECTRICFIELD
