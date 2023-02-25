#include "electricField.h"
#include <iostream>

using namespace std;

int main()
{  
  electricField fieldEz;
  
  fieldEz.setSheathSize(2.0E-2); 
  fieldEz.setG0G1d(100.E-6);
  fieldEz.setG1G2d(200.E-6);
  fieldEz.setG2G3d(200.E-6);
  fieldEz.setG3Cd(100.E-6);
  
  fieldEz.setPlasmaPotential(1000.);
  fieldEz.setG0(0.);
  fieldEz.setG1(-20.);
  fieldEz.setG2(+500.);
  fieldEz.setG3(-20.);
  fieldEz.setC(-10.);
  
  
  float z, zhigh, zlow, dz;
  const int n = 100;
  int i;
  
  zhigh =  1E-6;
  zlow  = -610E-6; 
  dz    = (zhigh - zlow)/n;
  
  cout << "z, Electric Field (Newton/Coulomb)" << endl;
  for (i=0; i<n; i++)
    {
      z = zhigh - float(i)*dz;
      cout << z << " , "  << fieldEz.returnElectricField(z) << endl;
    }
  return 0;
}
