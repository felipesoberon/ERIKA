#include "rfea.h"


void rfea::setParametersFromCommandLineInput(int numberOfArguments, char* valueOfArgument[])
{
  cout << "\nCOMMAND_LINE_INPUT_PARAMETERS\n\n";
  
  commandLine.setArgumentList(numberOfArguments, valueOfArgument);
  commandLine.printArgumentList();
  
  commandLine.setFlagName("-max_eV", "Scan's maximum energy in eV.");
  commandLine.setFlagName("-step_eV", "Scan's energy step in eV.");
  commandLine.setFlagName("-no._ion", "Scan's number of ions per step.");
  commandLine.setFlagName("-pressure_Pa", "Argon gas pressure in Pa.");
  commandLine.setFlagName("-sim_time", "Maximum simulation time per ion (s).");
  commandLine.printFlagNameList();
  
  commandLine.setFlagValues();
  commandLine.printFlagValues();
  
  if (commandLine.flagValueIsNumber(0))
    maxEnergy = int( commandLine.returnFloatFlagValue(0) );
  
  if (commandLine.flagValueIsNumber(1))
    stepEnergy = int(  commandLine.returnFloatFlagValue(1) );
  
  if (commandLine.flagValueIsNumber(2))
    ionsPerEnergy =  int( commandLine.returnFloatFlagValue(2) );
  
  if (commandLine.flagValueIsNumber(3))
    pressurePa =  commandLine.returnFloatFlagValue(3);
  
  if (commandLine.flagValueIsNumber(4))
    simulationTime =  commandLine.returnFloatFlagValue(4);
    
  cout << endl;
}



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




void rfea::integrateIonTrajectory(bool saveTrajectory, long randomSeed)
{
  float dt = ionAr.returndt();
  float zG0 = Ez.returnzG0();
  float zC = Ez.returnzC();
  float zP = Ez.returnzP();
  
  float z = zP;           // Initial position of the particle in m
  float v = 0.0;          // Vz of the particle in m/s
  float v_= 0.0;          // Vperpendicular 
  float t = 0.0;          // Initial time in seconds
  
  float Efz = 0.0;
  
  float collisionProbability;
  float crossSection = 40E-20; //m2
  float k = 1.3806503E-23; //m2 kg s-1 K-1
  float T = 300; //Kelvin
  float nGas = pressurePa / (k * T); //m-3
  float collisionRate;
  float collisionsindt;
  bool  crossedzG0 = false;
  
  collisionRate = nGas * crossSection; // x abs(v)
  
  ofstream file("output/trajectory.csv");
  if(saveTrajectory) file << "Time(s), z(m), vz(m/s)" << endl;
  
  while ( zP >= z && z >= zC /*&& v <= 0.0*/ && t < simulationTime )
    {
      collisionsindt = collisionRate * ionAr.magnitude(v, v_, 0.0) * dt; 
      collisionProbability = ran2(randomSeed);
      
      if (collisionProbability < collisionsindt)
	{
	  /*ionAr.collision(v, v_);*/
	  float v__ = 0.0;
	  ionAr.collision(v, v_, v__);
	}
      else
	{
	  Efz = Ez.returnElectricField(z);
	  ionAr.rungeKutta4th(z, v, t, Efz);
	}
      
      if(saveTrajectory) file  << t << ","<< z << ","<< v << endl;
      
      if( z < zG0 && !crossedzG0 )
	{
	  crossedzG0 = true;
	  ofstream file3("output/ionEnergy.csv", ios::app);
	  file3 << 0.5 * ionAr.returnMass() * v*v / ionAr.returnCharge() << ",";
	  file3 << 0.5 * ionAr.returnMass() * ionAr.magnitudeSquare(v, v_, 0.0) / ionAr.returnCharge();
	  file3 << endl;
	  file3.close();
	} 
      
      t = t + dt;
    }
  file.close();
  
  ofstream file2("output/ionCount.csv", ios::app);
  float energy = 0.5 * ionAr.returnMass() * ionAr.magnitudeSquare(v, v_, 0.0) / ionAr.returnCharge();
  if ( z <= zC ) file2 << G2 << "  ,  " << 1 << "  ,  " << energy << endl;
  else           file2 << G2 << "  ,  " << 0 << "  ,  " << energy << endl;
  file2.close();
}




void rfea::energyScan(void)
{
  for (int i=0; i<maxEnergy; i=i+stepEnergy)
    {
      cout << "Energy (eV) = " << i << endl;
      for(int j=1; j<=ionsPerEnergy; j++)
	{
	  setG2( float(i) );
	  integrateIonTrajectory(false, long(i+1+j));
	}
    }
}
