#include "electricField.h"

void  electricField::setSheathSize(float inputSheathSize){ sheathSize = inputSheathSize; }

void  electricField::setG0G1d(float inputDistance){ G0G1d = inputDistance; }
void  electricField::setG1G2d(float inputDistance){ G1G2d = inputDistance; }
void  electricField::setG2G3d(float inputDistance){ G2G3d = inputDistance; }
void  electricField::setG3Cd(float inputDistance){  G3Cd  = inputDistance; }


void  electricField::setPlasmaPotential(float inputPlasmaPotential){ plasmaPotential = inputPlasmaPotential; }
	
void  electricField::setG0(float inputG0){ G0 = inputG0; }
void  electricField::setG1(float inputG1){ G1 = inputG1; }
void  electricField::setG2(float inputG2){ G2 = inputG2; }
void  electricField::setG3(float inputG3){ G3 = inputG3; }
void  electricField::setC(float inputC){ C = inputC; }




float electricField::returnElectricField(float z) 
{  
  if                   ( z >= 0)                                        E_z = -(plasmaPotential-G0)/sheathSize ; //The Sheath DC voltage
  else if ( 0     > z && z >= -G0G1d )                                  E_z = -(G0-G1)/G0G1d;   //Electron repulsion region G0-G1
  else if (-G0G1d > z && z >= -(G0G1d+G1G2d) )                          E_z = -(G1-G2)/G1G2d;  //Retarding field G1-G2
  else if (-(G0G1d+G1G2d) > z && z >= -(G0G1d+G1G2d+G2G3d) )            E_z = -(G2-G3)/G2G3d;  //Sec. e from collector repulsion G2-G3
  else if (-(G0G1d+G1G2d+G2G3d) > z && z >= -(G0G1d+G1G2d+G2G3d+G3Cd) ) E_z = -(G3-C)/G3Cd;   //Collector G3-C
  else                                                                  E_z = 0.0;
  
  return E_z;
}