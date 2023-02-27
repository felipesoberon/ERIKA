#include "rfea.h"

int main()
{  
  
  rfea model;
  
  model.setDistanceSheathG0123C(2E-2, 100E-6, 200E-6, 200E-6, 100E-6);
  model.setVoltagePlasma0123C(1000, 0, -20, 500, -20, -10);
  model.setElectricField();
  
  
  
  return 0;
}
