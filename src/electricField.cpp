#include "electricField.h"




float electricField::interpolate(point p1, point p2, float x)
{
  float y, slope, y_intercept;

  if (p1.x == p2.x)  y = p1.y;
  else
    {
      slope = (p2.y - p1.y) / (p2.x - p1.x);
      y_intercept = p1.y - slope * p1.x;
      y = slope * x + y_intercept;
    }
  return y;
}




void  electricField::setSheathSize(float inputSheathSize){ sheathSize = inputSheathSize; }

void  electricField::setG0G1d(float inputDistance){ G0G1d = inputDistance; }
void  electricField::setG1G2d(float inputDistance){ G1G2d = inputDistance; }
void  electricField::setG2G3d(float inputDistance){ G2G3d = inputDistance; }
void  electricField::setG3Cd(float inputDistance){  G3Cd  = inputDistance; }


void  electricField::setCoordinate(void)
{
  zP = sheathSize;
  z0 = 0;
  z1 = -G0G1d;
  z2 = -(G0G1d+G1G2d);
  z3 = -(G0G1d+G1G2d+G2G3d);
  zC = -(G0G1d+G1G2d+G2G3d+G3Cd);
}


void  electricField::setPlasmaPotential(float inputPlasmaPotential){ plasmaPotential = inputPlasmaPotential; }

void  electricField::setG0(float inputG0){ G0 = inputG0; }
void  electricField::setG1(float inputG1){ G1 = inputG1; }
void  electricField::setG2(float inputG2){ G2 = inputG2; }
void  electricField::setG3(float inputG3){ G3 = inputG3; }
void  electricField::setC(float inputC){ C = inputC; }


float electricField::returnzG0(void){ return z0;}
float electricField::returnzG1(void){ return z1;}
float electricField::returnzG2(void){ return z2;}
float electricField::returnzG3(void){ return z3;}
float electricField::returnzC(void){ return zC;}




float electricField::returnElectricField(float z) 
{  
  if      ( zP >= z && z >= z0)  E_z = -(plasmaPotential-G0)/sheathSize ; //The Sheath DC voltage
  else if ( z0 > z  && z >= z1 ) E_z = -(G0-G1)/G0G1d;   //Electron repulsion region G0-G1
  else if ( z1 > z  && z >= z2 ) E_z = -(G1-G2)/G1G2d;  //Retarding field G1-G2
  else if ( z2 > z  && z >= z3 ) E_z = -(G2-G3)/G2G3d;  //Sec. e from collector repulsion G2-G3
  else if ( z3 > z  && z >= zC ) E_z = -(G3-C)/G3Cd;   //Collector G3-C
  else                           E_z = 0.0;
  
  return E_z;
}



float electricField::returnVoltage(float z)
{
  if      ( zP >= z && z >= z0)  V_z = interpolate({zP,plasmaPotential},{z0,G0},z);
  else if ( z0 > z  && z >= z1 ) V_z = interpolate({z0,G0},{z1,G1},z);
  else if ( z1 > z  && z >= z2 ) V_z = interpolate({z1,G1},{z2,G2},z);
  else if ( z2 > z  && z >= z3 ) V_z = interpolate({z2,G2},{z3,G3},z);
  else if ( z3 > z  && z >= zC ) V_z = interpolate({z3,G3},{zC,C},z);
  else                           V_z = 0.0;
  
  return V_z;
}





void electricField::showVoltageAndElectricField(void)
{
  float z, zhigh, zlow, dz;
  int n;
  
  zhigh = zP;
  zlow  = zC;
  dz    = 5E-6;
  n     = int( floor( (zhigh - zlow)/dz ) ) + 1;
  
  cout << "z, Voltage (V), Electric Field (Newton/Coulomb)" << endl;
  for (int i=0; i<n; i++)
    {
      z = zhigh - float(i)*dz;
      cout << z;
      cout << " , " << returnVoltage(z);
      cout << " , " << returnElectricField(z);
      cout << endl;
    }
}






