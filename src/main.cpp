#include "rfea.h"

void printProgramDescription(void);

int main (int argc, char* argv[])
{
  printProgramDescription();
  
  rfea model;
  
  model.setParametersFromCommandLineInput(argc, argv);

  model.setDistanceSheathG0123C(2E-2, 100E-6, 200E-6, 200E-6, 100E-6);
  model.setVoltagePlasma0123C(1000, 0, -20, 500, -20, -10);
  model.setElectricField();
  model.setIon();

  model.executeSimulation();
  
  return 0;
}





void printProgramDescription(void)
{
  cout << "**********************************************" << endl;
  cout << "*                                            *" << endl;
  cout << "* Felipe Soberon (felipe.soberon@gmail.com)  *" << endl;
  cout << "* 2023                                       *" << endl;
  cout << "*                                            *" << endl;
  cout << "* Ion energy transport and RFEA model.       *" << endl;
  cout << "*                                            *" << endl;
  cout << "**********************************************" << endl;
  
  cout << "Usage:" << endl;
  cout << "$ ./rfea <-flag> <flag value>";
  cout << endl;
}
