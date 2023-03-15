#include "rfea.h"

void printProgramDescription(void);

int main (int argc, char* argv[])
{
  printProgramDescription();
  
  rfea model;
  
  model.setParametersFromCommandLineInput(argc, argv);

  model.setSpacerStack();
  model.setVoltageGrids013C(/*G0=*/0, /*G1=*/-60, /*G3=*/-70, /*C=*/-60);
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
  cout << "* E_mulating                                 *" << endl;
  cout << "* R_etarding-field-energy-analyzer           *" << endl;
  cout << "* I_on                                       *" << endl;
  cout << "* K_inetic-transport in                      *" << endl;
  cout << "* A_rgon gas                                 *" << endl;
  cout << "*                                            *" << endl;
  cout << "**********************************************" << endl;
  
  cout << "Usage:" << endl;
  cout << "$ ./rfea <-flag> <flag value>";
  cout << endl;
}
