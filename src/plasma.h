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


  int const static Npoints = 64+1; 
  float X[Npoints], PHI[Npoints]; //for RF inhomogenous solution
  float xs[Npoints];              //for collisional solution
  float integralFuncData[Npoints] = {  //integral values in x(phi) function for collisional solution
				     0.0, 4.32137e-6, 0.000048842, 0.000201554, 0.000550385,
				     0.00119826, 0.00225994, 0.00385949, 0.00612818, 0.00920244,
				     0.0132221, 0.0183285, 0.024663, 0.032365, 0.0415709, 0.052412,
				     0.0650132, 0.079492, 0.0959565, 0.114505, 0.135223, 0.158185,
				     0.18345, 0.211066, 0.241061, 0.27345, 0.308232, 0.345387, 0.384878,
				     0.426651, 0.470634, 0.516739, 0.564859, 0.61487, 0.666632, 0.719988,
				     0.774767, 0.830782, 0.887834, 0.94571, 1.00419, 1.06303, 1.12199,
				     1.18083, 1.23928, 1.29709, 1.35398, 1.4097, 1.46398, 1.51656,
				     1.56717, 1.61557, 1.66151, 1.70475, 1.74507, 1.78225, 1.81609,
				     1.84641, 1.87305, 1.89585, 1.91468, 1.92945, 1.94006, 1.94645,
				     1.94858};
  
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

  void setFunctionxs(void);
  float returnxs(float phiinput);

};

#endif //PLASMA
