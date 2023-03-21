#ifndef PLASMA_H
#define PLASMA_H

#include <cmath>
#include <iostream>

using namespace std;

class plasma
{
private:
  
  const float epsilon_0 = 8.8541878128e-12; //F m^-1
  const float e = 1.60217662e-19; // Coulomb
  
  float Te = 3.0;   //electron temperature in eV
  float ns = 1.e15; //plasma density at edge of sheath (m^-3)
  float M = 6.6335209e-26; //ion mass (kg)
  float V0 = 1000.; //potential across sheath
  float freq = 0.;  //Hz, for RF driven discharges / 0 for DC
  
  float DebyeLength;
  float BohmVelocity;
  float J0; //Ion current (A/m2)
  float J; //The discharge current (A/m2)
  
  float matrixSheathSize;
  float ChildLawSheathSize;
  float homCapSheathSize;
  float inHomCapSheathSize;
  
  float X[64+1], PHI[64+1]; //for RF inhomogenous solution
  
public:
  
  void inputPlasmaParameters(float inTe, float inns, float inV0, float inFreq);
  
  void calculateDebyeLength(void);
  float returnDebyeLength(void);
  
  void calculateBohmVelocity(void);
  float returnBohmVelocity(void);
  
  void calculateMatrixSheathSize(void);
  float returnMatrixSheathSize(void);
  float returnMatrixSheathPotential(float x);
  float returnMatrixSheathElectricField(float x);
  
  void calculateChildLawSheathSize(void);
  float returnChildLawSheathSize(void);
  float returnChildLawSheathPotential(float x);
  float returnChildLawSheathElectricField(float x);
  
  void calculateJ0(void);
  float returnJ0(void);
  
  void calculateHomDischargeParameters(void);
  float returnHomDischargeSheathSize(void);
  float returnHomDischargeSheathPotential(float x, float t);
  float returnHomDischargeSheathElectricField(float x, float t);
  
  void calculateInhomDischargeParameters(void);
  float x(float phi);
  float returnInhomDischargeSheathPosition(float t);
  float returnInhomDischargeSheathSize(void);
  void setPairsXPHI(void);
  float returnPhi(float xinput);
  float returnInhomDischargeSheathPotential(float x, float t);
  float returnInhomDischargeSheathElectricField(float z, float t);
  
};

#endif //PLASMA
