#include "plasma.h"


void plasma::inputPlasmaParameters(float inTe, float inns, float inV0, float inFreq, float inPressurePa)
{
  if (inTe>0)     Te = inTe;
  if (inns>0)     ns = inns;
  if (inV0>0)     V0 = inV0;
  if (inFreq>0) freq = inFreq;
  if (inPressurePa>0) pressurePa = inPressurePa; 
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


void plasma::calculateLambdai(void)
{ float pressuremTorr = pressurePa/0.13332237;
  Lambdai = 1.0/(30.*pressuremTorr); }
float plasma::returnLambdai(void)
{ calculateLambdai();
  return Lambdai; }


float plasma::returnDischargeCurrent(void)
{ return J; }



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



/* INHOMOGENEOUS RF DISCHARGE MODEL, Lieberman 1988 */

void plasma::calculateInhomDischargeParameters(void)
{
  float w = 2.*M_PI*freq;
  if (freq > 0) 
    {
      calculateLambdai();
      calculateDebyeLength();
      calculateBohmVelocity();
      
      J = w*(2./5.)*sqrt(6./5.)*sqrt(e*ns*epsilon_0*(sqrt(576.+125.*V0)-24.)); //collisionless
      J = returnJ(V0); //collisional

      float T = 1/freq;
      inhomCapSheathSize = returnInhomDischargeSheathPosition(T/2.);
      setPairsXPHI();
    }
  else cout << "ERROR: frequency, " << freq << ", is not >0" << endl;
}

float plasma::x(float phi) /* 0 to pi */
{
  float w  = 2.*M_PI*freq;
  float s0 = J /(e*ns*w);
  float DL = returnDebyeLength();
  float H;
  
  H = (1./M_PI)*(s0*s0/(DL*DL)); //collisionless
  H = sqrt(2.*Lambdai*s0/(M_PI*M_PI*DL*DL)); //collisional  
  
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
{ return inhomCapSheathSize; }

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
  int   Nz = 1000;
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
  float sm   = inhomCapSheathSize;
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




/*Functions to help find J for a given V0 in the collisional
  AC sheath*/

float plasma::SS0(float J)
{ float w  = 2.*M_PI*freq;  
  return J /(e*ns*w); }
float plasma::HH(float J)
{ return sqrt(2.*Lambdai*SS0(J)) / (M_PI * DebyeLength); }
float plasma::VV(float J)
{  float w  = 2.*M_PI*freq;  
  return J*SS0(J)*(2.+125.*M_PI*HH(J)/192.)/(epsilon_0*w); }


float plasma::returnJ(float Vinput)
{
  float j = 0;
  float dj = 1;
  while ( abs( VV(j)-Vinput) > 0.01 )
    {
      j = j + dj;
      if ( VV(j)>Vinput )
	{
	  j = j - dj;
	  dj = dj/2.;
	}
    }
  return j;
}


