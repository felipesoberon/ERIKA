#include "rfea.h"

int main()
{  
  rfea model;
  
  model.setDistanceSheathG0123C(2E-2, 100E-6, 200E-6, 200E-6, 100E-6);
  model.setVoltagePlasma0123C(1000, 0, -20, 500, -20, -10);
  model.setElectricField();
  
  for (int i = 0; i<1500; i=i+10)
    {
      cout << i << endl;
      for(int j = 1; j<=100; j++)
	{
	  model.setG2( float(i) );
	  model.integrateIonTrajectory(false, long(i+1+j));
	}
    }
  
  return 0;
}
