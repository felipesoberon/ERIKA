#include "plasma.h"


void plasma::inputPlasmaParameters(float inTe, float inns, float inV0, float inFreq)
{
  if (inTe>0)     Te = inTe;
  if (inns>0)     ns = inns;
  if (inV0>0)     V0 = inV0;
  if (inFreq>0) freq = inFreq;
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






void plasma::calculateHomDischargeParameters(void)
{
  if (freq > 0)
    {
      J = 2*M_PI*freq*sqrt(e*ns*epsilon_0*V0/2);
      homCapSheathSize = 2* J/(e*ns*2*M_PI*freq); //the fully expanded sheath size
    }
  else cout << "ERROR: frequency, " << freq << ", is not >0" << endl;
}
float plasma::returnHomDischargeSheathSize(void)
{ return homCapSheathSize; }
float plasma::returnHomDischargeSheathPotential(float x, float t)
{
  float wt  = 2*M_PI*freq*t;
  float s0  = homCapSheathSize/2;
  float sa  = s0*(1-sin(wt));
  float fac = e*ns/(2*epsilon_0);
  float Vpa = -fac*s0*s0*pow(1-sin(wt),2);
  float Vpp = 0;
  if (x<=sa) Vpp = -fac*pow(-s0+x+s0*sin(wt),2);
  return Vpp-Vpa;
}
float plasma::returnHomDischargeSheathElectricField(float x, float t)
{
  float wt  = 2*M_PI*freq*t;
  float s0  = homCapSheathSize/2;
  float sa  = s0*(1-sin(wt));
  float fac = e*ns/epsilon_0;
  float Ef  = 0;
  if (x<=sa) Ef = fac*(x-sa);   
  return Ef;
}
