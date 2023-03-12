#ifndef PLASMA_H
#define PLASMA_H

#include <cmath>

class plasma
{
 private:
  
  const float epsilon_0 = 8.8541878128e-12; //F m^-1
  const float e = 1.60217662e-19; // Coulomb
  
  float Te = 3.0;   //electron temperature in eV
  float ns = 1.e15; //plasma density at edge of sheath (m^-3)
  float M = 6.6335209e-26; //ion mass (kg)
  float V0 = 1000.; //potential across sheath
  
  float DebyeLength;
  float BohmVelocity;
  float matrixSheathSize;


 public:

  void inputPlasmaParameters(float inTe, float inns, float inV0);

  void calculateDebyeLength(void);
  float returnDebyeLength(void);

  void calculateBohmVelocity(void);
  float returnBohmVelocity(void);

  void calculateMatrixSheathSize(void);
  float returnMatrixSheathSize(void);
  float returnMatrixSheathPotential(float x);
  float returnMatrixSheathElectricField(float x);
  
};


#endif //PLASMA
