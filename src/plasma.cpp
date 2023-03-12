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
{ return DebyeLength; }


void plasma::calculateBohmVelocity(void)
{ BohmVelocity = sqrt( e * Te / M ); }
float plasma::returnBohmVelocity(void)
{ return BohmVelocity; }


void plasma::calculateMatrixSheathSize(void)
{ matrixSheathSize = sqrt( 2.0*epsilon_0*V0/(e*ns) ); }
float plasma::returnMatrixSheathSize(void)
{ return matrixSheathSize; }
float plasma::returnMatrixSheathPotential(float x)
{ return -0.5*e*ns*x*x/epsilon_0; }
float plasma::returnMatrixSheathElectricField(float x)
{ return e*ns*x/epsilon_0; }
