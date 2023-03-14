#include "plasma.h"


void plasma::inputPlasmaParameters(float inTe, float inns, float inV0)
{
  if (inTe>0) Te = inTe;
  if (inns>0) ns = inns;
  if (inV0>0) V0 = inV0;
}


void plasma::calculateDebyeLength(void)
{ DebyeLength = sqrt( epsilon_0*Te/(e*ns) ); }
float plasma::returnDebyeLength(void)
{ calculateDebyeLength();
  return DebyeLength; }


void plasma::calculateBohmVelocity(void)
{ BohmVelocity = sqrt( e * Te / M ); }
float plasma::returnBohmVelocity(void)
{ calculateBohmVelocity();
  return BohmVelocity; }


void plasma::calculateMatrixSheathSize(void)
{ matrixSheathSize = sqrt( 2.0*epsilon_0*V0/(e*ns) ); }
float plasma::returnMatrixSheathSize(void)
{ return matrixSheathSize; }
float plasma::returnMatrixSheathPotential(float x)
{ return -0.5*e*ns*x*x/epsilon_0; }
float plasma::returnMatrixSheathElectricField(float x)
{ return e*ns*x/epsilon_0; }



void plasma::calculateChildLawSheathSize(void)
{ calculateDebyeLength();
  ChildLawSheathSize = (sqrt(2)/3.) * DebyeLength * pow(2.*V0/Te, 3./4.); }
float plasma::returnChildLawSheathSize(void)
{ return ChildLawSheathSize; }
float plasma::returnChildLawSheathPotential(float x)
{ float s = ChildLawSheathSize;
  return -V0*pow(x/s, 4./3.); }
float plasma::returnChildLawSheathElectricField(float x)
{ float s = ChildLawSheathSize;
  return (4./3.)*(V0/s)*pow(x/s, 1./3.); }




void plasma::calculateJ0(void)
{ J0 = e * ns * BohmVelocity; }
float plasma::returnJ0(void)
{ calculateBohmVelocity();
  calculateJ0();
  return J0; }
