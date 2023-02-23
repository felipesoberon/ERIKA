#include <iostream>
#include <cmath>
using namespace std;

float electricField(float z) 
{
  const float sheathSize = 2.0E-2; //Sheath size in m
  const float d = 100.E-6; // Distance in m  
  const float Vplasma = 1000.;
  const float G0 = 0.;
  const float G1 = -20.;
  const float G2 = +500.;
  const float G3 = -20.;
  const float C  = -10.;
  float E_z = 0;
  
  if                 ( z >= 0)     E_z = -(Vplasma-G0)/sheathSize ; //The Sheath DC voltage
  else if ( 0 >   z && z >= -d   ) E_z = -(G0-G1)/d;   //Electron repulsion region G0-G1
  else if (-d >   z && z >= -2*d ) E_z = -(G1-G2)/d;  //Retarding field G1-G2
  else if (-2*d > z && z >= -3*d ) E_z = -(G2-G3)/d;  //Sec. e from collector repulsion G2-G3
  else if (-3*d > z && z >= -4*d ) E_z = -(G3-C)/d;   //Collector G3-C
  else                             E_z = 0.0;
  
  return E_z;
}

int main()
{  
  float z, zhigh, zlow, dz;
  const int n = 10000;
  int i;
  
  zhigh =  1E-2;
  zlow  = -450E-6; 
  dz    = (zhigh - zlow)/n;
  
  cout << "z, Electric Field (Newton/Coulomb)" << endl;
  for (i=0; i<n; i++)
    {
      z = zhigh - float(i)*dz;
      cout << z << " , "  << electricField(z) << endl;
    }
  return 0;
}
