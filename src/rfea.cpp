#include "rfea.h"


void rfea::setDistanceSheathG0123C(float dS, float d01, float d12, float d23, float d3C)
{
  sheathSize = dS;
  G0G1d = d01; 
  G1G2d = d12; 
  G2G3d = d23; 
  G3Cd  = d3C; 	
}



void rfea::setVoltagePlasma0123C(float pp, float g0, float g1, float g2, float g3, float c)
{
  plasmaPotential = pp;
  G0 = g0;
  G1 = g1;
  G2 = g2; 
  G3 = g3;
  C  = c;
}



void rfea::setElectricField(void)
{
  Ez.setSheathSize(sheathSize); 
  Ez.setG0G1d(G0G1d);
  Ez.setG1G2d(G1G2d);
  Ez.setG2G3d(G2G3d);
  Ez.setG3Cd(G3Cd);
  
  Ez.setPlasmaPotential(plasmaPotential);
  Ez.setG0(G0);
  Ez.setG1(G1);
  Ez.setG2(G2);
  Ez.setG3(G3);
  Ez.setC(C);
  
  Ez.setCoordinate();
  
  Ez.saveVoltageAndElectricField("output/VEz.csv");
}




void rfea::setG2(float g2)
{
  G2 = g2;
  Ez.setG2(G2);
}




void rfea::integrateIonTrajectory(void)
{
  float dt = ionAr.returndt();
  float zC = Ez.returnzC();
  float zP = Ez.returnzP();

  float z = zP;           // Initial position of the particle in m
  float v = 0.0;          // Initial velocity of the particle in m/s
  float t = 0.0;          // Initial time in seconds

  float Efz = 0.0;

  cout << "Time(s), z(m), vz(m/s)" << endl;
  while (t < 10.0e-6 && zP >= z && z > zC)
    {
      Efz = Ez.returnElectricField(z);
      ionAr.rungeKutta4th(z, v, t, Efz);
      cout  << t << " ,  ";
      cout  << z << " ,  ";
      cout  << v << endl;
      t = t + dt;
    }
}
