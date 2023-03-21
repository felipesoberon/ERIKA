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


/* MATRIX DC Sheath */

void plasma::calculateMatrixSheathSize(void)
{ matrixSheathSize = sqrt( 2.0*epsilon_0*V0/(e*ns) ); }
float plasma::returnMatrixSheathSize(void)
{ return matrixSheathSize; }
float plasma::returnMatrixSheathPotential(float x)
{ return -0.5*e*ns*x*x/epsilon_0; }
float plasma::returnMatrixSheathElectricField(float x)
{ return e*ns*x/epsilon_0; }



/* CHILD LAW DC Sheath */

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



/* HOMOGENEOUS RF MODEL, Lieberman book, Capacitive RF Sheath */

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




/* INHOMOGENEOUS RF DISCHARGE MODEL, Lieberman 1988 */

void plasma::calculateInhomDischargeParameters(void)
{
  float w = 2.*M_PI*freq;
  if (freq > 0) 
    {
      J = w*(2./5.)*sqrt(6./5.)*sqrt(e*ns*epsilon_0*(sqrt(576.+125.*V0)-24.));
      float T = 1/freq;
      inHomCapSheathSize = returnInhomDischargeSheathPosition(T/2.);
      setPairsXPHI();
    }
  else cout << "ERROR: frequency, " << freq << ", is not >0" << endl;
}

float plasma::x(float phi) /* 0 to pi */
{
  float w  = 2.*M_PI*freq;
  float s0 = J /(e*ns*w);
  float DL = returnDebyeLength();
  float H  = (1./M_PI)*(s0*s0/(DL*DL));
  
  return s0*( 
	     1.-cos(phi) 
	     +
	     (H/8.)*( (3./2.)*sin(phi) +(11./18.)*sin(3.*phi) -3.*phi*cos(phi)  -(1./3.)*phi*cos(3.*phi) ) 
	      );	
}

float plasma::returnInhomDischargeSheathPosition(float t)
{
  float w  = 2.*M_PI*freq;
  float T  = 1./freq;
  float tau = fmod(t+T/2., T) -T/2.;
  float phi = abs( w*tau );

  return x(phi);	
}

float plasma::returnInhomDischargeSheathSize(void)
{ return inHomCapSheathSize; }

void plasma::setPairsXPHI(void)
{
  float phi;
  for (int i =0; i<=64; i++)
    {
      phi    = float( i*M_PI/64.);
      PHI[i] = phi;
      X[i]   = x(phi);
    }
}

float plasma::returnPhi(float xinput)
{	
  float phiout = -1.;
  int i, i1, i2, i3;
  int M = 65; //M-1 = 2^n 
  i1 = 0;
  i2 = (M-1)/2;  
  i3 = (M-1);
  
  //The search algorithm
  for (i=0; i<=M-1; i++)
    {
      if ( X[i1] <= xinput && xinput < X[i2] )
	{
	  if (i1+1 == i2) 
	    {
	      phiout = (PHI[i2] - PHI[i1])/(X[i2]-X[i1])*(xinput - X[i1]) + PHI[i1];
	      break;
	    }
	  i3 = i2;
	  i2 = (i3+i1)/2;
	}//if
      else if ( X[i2] <= xinput && xinput <= X[i3] )
	{
	  if (i2+1 == i3) 
	    {
	      phiout = (PHI[i3] - PHI[i2])/(X[i3]-X[i2])*(xinput - X[i2]) + PHI[i2];
	      break;
	    }
	  i1 = i2;
	  i2 = (i3+i1)/2;
	}//else
    }//for
  
  if (phiout == -1.0) cout << "ERROR, " << xinput << ", is out of function range" << endl;
  return phiout;
}


float plasma::returnInhomDischargeSheathPotential(float z, float t)
{
  int   Nz = 100;
  float dz = z/Nz;
  float sum = 0.;
  
  for (int i=0; i<=Nz; i++) sum = sum-returnInhomDischargeSheathElectricField(i*dz,t);
  sum = sum * dz;    
  return sum;
}


float plasma::returnInhomDischargeSheathElectricField(float z, float t)
{
  float w    = 2.*M_PI*freq;
  float wt   = w*t;
  float sm   = inHomCapSheathSize;
  float fac  = J/(epsilon_0*w);
  float st   = returnInhomDischargeSheathPosition(t);
  float Ef  = 0;
  
  if ( st<sm-z )
    {
      float phix = returnPhi(sm-z);
      Ef = -fac*(cos(wt)-cos(phix));
    }
  
  return Ef;
}
