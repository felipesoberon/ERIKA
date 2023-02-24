#include "electricField.h"
#include <iostream>

using namespace std;

int main()
{  
  electricField plasmaRFEA;
  
  plasmaRFEA.setSheathSize(2.0E-2); 
  plasmaRFEA.setG0G1d(100.E-6);
  plasmaRFEA.setG1G2d(200.E-6);
  plasmaRFEA.setG2G3d(200.E-6);
  plasmaRFEA.setG3Cd(100.E-6);
  
  plasmaRFEA.setPlasmaPotential(1000.);
  plasmaRFEA.setG0(0.);
  plasmaRFEA.setG1(-20.);
  plasmaRFEA.setG2(+500.);
  plasmaRFEA.setG3(-20.);
  plasmaRFEA.setC(-10.);
  
	
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
      cout << z << " , "  << plasmaRFEA.returnElectricField(z) << endl;
    }
  return 0;
}