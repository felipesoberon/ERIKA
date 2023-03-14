#include "rfea.h"

void printProgramDescription(void);

int main (int argc, char* argv[])
{
  printProgramDescription();
  
  rfea model;
  
  model.setParametersFromCommandLineInput(argc, argv);

  model.setSpacerStack();
  model.setVoltagePlasma0123C(1000, 0, -60, 0.0, -70, -60);
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
