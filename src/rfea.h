#ifndef RFEA_H
#define RFEA_H

#include "commandline.h"
#include "electricField.h"
#include "ion.h"
#include "random.h"
#include "plasma.h"
#include "XSection.h"

#include <fstream>
#include <string>

using namespace std;

class rfea
{
private:
  
  electricField Ez; 
  ion ionAr;        
  commandline commandLine;  

  int simulationType = 0; //0:trj, 1:scan, 2:space charge
  
  float sheathSize; 
  float G0G1d, G1G2d, G2G3d, G3Cd;
  const float spacerThickness = 100.0E-6;
  int spacerStack = 1221;
  int gridTransparency = 100; 
  
  float plasmaPotential = 1000.;
  float plasmaDensity = 1e16;
  float radioFrequency = 0.;
  float G0, G1, G2 =0.0, G3, C;
  
  int maxEnergy = 1500;
  int stepEnergy = 10;
  int ionsPerEnergy = 100;
  float pressurePa = 0.5;
  float simulationTime = 1.0E-6; 

  bool saveLastPosition = false;
  bool saveTrajectory = false;
  
  float sigma1=1, sigma2=1; 
  
public:
  
  void setParametersFromCommandLineInput(int numberOfArguments, char* valueOfArgument[]);

  void setPlasmaSheathSize(float dS);
  void setSpacerStack(void);
  void setVoltageGrids013C(float g0, float g1, float g3, float c);
  void setElectricField(void);
  void setG2(float g2);
  
  void  setIon(void);
  float collisionCrossSection(float energy);
  float collisionCrossSectionArPhelps(float energy);
  int   collisionType(void);
  
  void integrateIonTrajectory(long randomSeed);
  void energyScan(void);
  void spaceCharge(void);
  
  void executeSimulation(void);

  bool isAtGrid(float zi, float zii);

};

#endif // RFEA
