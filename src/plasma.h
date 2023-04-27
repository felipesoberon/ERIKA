#ifndef PLASMA_H
#define PLASMA_H

#include <cmath>
#include <iostream>

using namespace std;

class plasma
{
private:
  
  const float epsilon_0 = 8.8541878128e-12; //F m^-1
  const float e  = 1.60217662e-19; // Coulomb
  const float pi = 3.141592653589793;
  
  float Te = 3.0;   //electron temperature in eV
  float ns = 1.e15; //plasma density at edge of sheath (m^-3)
  float M = 6.6335209e-26; //ion mass (kg)
  float V0 = 1000.; //potential across sheath
  float freq = 0.;  //Hz, for RF driven discharges / 0 for DC
  float pressurePa = 0.0;
  
  float DebyeLength;
  float BohmVelocity;
  float Lambdai; 
  float J0; //Ion current (A/m2)
  float J; //The discharge current (A/m2)
  
  float ChildLawSheathSize;
  float homCapSheathSize;
  float inhomCapSheathSize;
  
  float X[64+1], PHI[64+1]; //for RF inhomogenous solution
  float xs[64+1];           //for collisional solution
  
  int const static NVJ = 1024;
  float xV[NVJ+1], yJ[NVJ+1]; //for RF inhomogenous sol, to find J from Vmax across sheath
  
public:
  
  void inputPlasmaParameters(float inTe, float inns, float inV0, float inFreq, float inPressurePa);
  
  void calculateDebyeLength(void);
  float returnDebyeLength(void);
  
  void calculateBohmVelocity(void);
  float returnBohmVelocity(void);

  void calculateLambdai(void);
  float returnLambdai(void);

  float returnDischargeCurrent(void);
  
  void calculateChildLawSheathSize(void);
  float returnChildLawSheathSize(void);
  float returnChildLawSheathPotential(float x);
  float returnChildLawSheathElectricField(float x);
  
  void calculateJ0(void);
  float returnJ0(void);
  
  void calculateInhomDischargeParameters(void);
  float x(float phi);
  float returnInhomDischargeSheathPosition(float t);
  float returnInhomDischargeSheathSize(void);
  void setPairsXPHI(void);
  float returnPhi(float xinput);
  float returnInhomDischargeSheathPotential(float z, float t);
  float returnInhomDischargeSheathElectricField(float z, float t);

  /*Functions to help find J for a given V0 in the collisional
    AC sheath*/
  float SS0(float J);
  float HH(float J);
  float VV(float J);
  float returnJ(float Vinput);

  void setFunctionxs(void);
  float returnxs(float phiinput);

};

#endif //PLASMA
