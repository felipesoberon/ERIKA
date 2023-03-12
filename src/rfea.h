#ifndef RFEA_H
#define RFEA_H

#include "commandline.h"
#include "electricField.h"
#include "ion.h"
#include "random.h"
#include "plasma.h"

#include <fstream>
#include <string>

using namespace std;

class rfea
{
private:
  
  electricField Ez; 
  ion ionAr;        
  commandline commandLine;  
  
  bool  trajectory = false;
  bool  scan = true;
  
  float sheathSize; 
  float G0G1d, G1G2d, G2G3d, G3Cd;
  const float spacerThickness = 100.0E-6;
  int spacerStack = 1221;
  
  float plasmaPotential;
  float G0, G1, G2 =0.0, G3, C;
  
  int maxEnergy = 1500;
  int stepEnergy = 10;
  int ionsPerEnergy = 100;
  float pressurePa = 0.5;
  float simulationTime = 1.0E-6; 

  float sigma1=1, sigma2=1; 
  
public:
  
  void setParametersFromCommandLineInput(int numberOfArguments, char* valueOfArgument[]);

  void setPlasmaSheathSize(float dS);
  void setSpacerStack(void);
  void setVoltagePlasma0123C(float pp, float g0, float g1, float g2, float g3, float c);
  void setElectricField(void);
  void setG2(float g2);
  
  void  setIon(void);
  float collisionCrossSection(float energy);
  int   collisionType(void);
  
  void integrateIonTrajectory(bool saveTrajectory, long randomSeed);
  void energyScan(void);
  
  void executeSimulation(void);
  
};

#endif // RFEA
