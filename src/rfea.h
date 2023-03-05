#ifndef RFEA_H
#define RFEA_H

#include "commandline.h"
#include "electricField.h"
#include "ion.h"
#include "random.h"

#include <fstream>
#include <string>

using namespace std;

class rfea
{
private:
  
  electricField Ez; 
  ion ionAr;        
  commandline commandLine;  

  
  float sheathSize; 
  float G0G1d, G1G2d, G2G3d, G3Cd;  
  float plasmaPotential;
  float G0, G1, G2, G3, C;

  int maxEnergy = 1500;
  int stepEnergy = 10;
  int ionsPerEnergy = 100;
  float pressurePa = 0.5;
  float simulationTime = 1.0E-6; 
  
  
public:
  
  void setParametersFromCommandLineInput(int numberOfArguments, char* valueOfArgument[]);
  
  void setDistanceSheathG0123C(float dS, float d01, float d12, float d23, float d3C);
  void setVoltagePlasma0123C(float pp, float g0, float g1, float g2, float g3, float c);
  void setElectricField(void);
  void setG2(float g2);
  
  void integrateIonTrajectory(bool saveTrajectory, long randomSeed);
  void energyScan(void);
  
};

#endif // RFEA
