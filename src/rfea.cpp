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
  commandLine.setFlagName("-ion_traj", "simulate and save an ion trajectory (0/1)");
  commandLine.setFlagName("-RFEA_scan", "simulate an RFEA scan (0/1)");
  commandLine.setFlagName("-G2", "Grid 2 voltage");
  commandLine.setFlagName("-spacerStack", "No. of 100um spacers between grids (e.g. 2332)");
  
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

  if (commandLine.flagValueIsNumber(5))
    trajectory =  bool( commandLine.returnFloatFlagValue(5) );

  if (commandLine.flagValueIsNumber(6))
    scan =  bool( commandLine.returnFloatFlagValue(6) );

  if (commandLine.flagValueIsNumber(7))
    G2 =  commandLine.returnFloatFlagValue(7);
  
  if (commandLine.flagValueIsNumber(8))
    spacerStack =  int( commandLine.returnFloatFlagValue(8) );
  
  cout << endl;
}



void rfea::setSpacerStack(void)
{
  G0G1d = spacerThickness * float( int(spacerStack/1000) ); 
  G1G2d = spacerThickness * float( int(spacerStack/100)%10 ); 
  G2G3d = spacerThickness * float( int(spacerStack/10)%10 );
  G3Cd  = spacerThickness * float( spacerStack%10); 
}


void rfea::setVoltagePlasma0123C(float pp, float g0, float g1, float g2, float g3, float c)
{
  plasmaPotential = pp;
  G0 = g0;
  G1 = g1;
  G3 = g3;
  C  = c;
}



void rfea::setElectricField(void)
{
  Ez.setPlasmaPotential(plasmaPotential);
  Ez.setG0(G0);
  Ez.setG1(G1);
  Ez.setG2(G2);
  Ez.setG3(G3);
  Ez.setC(C);
  
  Ez.setSheathSize(); 
  Ez.setG0G1d(G0G1d);
  Ez.setG1G2d(G1G2d);
  Ez.setG2G3d(G2G3d);
  Ez.setG3Cd(G3Cd);
  
  Ez.setCoordinate();
  
  Ez.saveVoltageAndElectricField("output/VEz.csv");
}




void rfea::setG2(float g2)
{
  G2 = g2;
  Ez.setG2(G2);
}




void rfea::setIon(void)
{
  ionAr.setCrossSection(2, 1.e-20);
  ionAr.setCrossSection(1,(char *)"Xsections/Ar++Ar.elastic.txt");
  ionAr.setCrossSection(2,(char *)"Xsections/Ar++Ar.charge.exchange.txt");
}



float rfea::collisionCrossSection(float energy)
{
  sigma1 = ionAr.sigma(1, energy);
  sigma2 = ionAr.sigma(2, energy);
  return sigma1 + sigma2;
}



float rfea::collisionCrossSectionArPhelps(float energy)
{
  XSection argonXSection;
  sigma1 = argonXSection.sigmaArElasticPhelps(energy);
  sigma2 = argonXSection.sigmaArCXPhelps(energy);
  return sigma1 + sigma2;  
}


int rfea::collisionType(void)
{
  float fraction = sigma1/(sigma1+sigma2);
  float random = random01();
  int   type;
  
  if (random < fraction) type = 1;
  else                   type = 2; 
  
  return type; 
}




void rfea::integrateIonTrajectory(bool saveTrajectory, long randomSeed)
{
  float dt =  ionAr.returndt();
  float zG0 = Ez.returnzG0();
  float zC =  Ez.returnzC();
  float zP =  Ez.returnzP();

  plasma vBohm;
  vBohm.calculateBohmVelocity();
  
  float z = zP;           // Initial position of the particle in m
  float v = -vBohm.returnBohmVelocity(); // Vz of the particle in m/s
  float v_= 0.0;          // Vperpendicular 
  float v__ = 0.0;        // Third velocity component (ignored)
  float t = 0.0;          // Initial time in seconds
  
  float Efz = 0.0;
  
  float k = 1.3806503E-23;       //m2 kg s-1 K-1
  float T = 300;                 //Kelvin
  float nGas = pressurePa/(k*T); //m-3
  
  float collisionProbability;
  float crossSection;
  float collisionRate;
  float collisionsindt;
  bool  crossedzG0 = false;
  
  ofstream file("output/trajectory.csv");
  if(saveTrajectory) file << "Time(s), z(m), vz(m/s), vp(m/s)" << endl;
  
  while ( zP >= z && z >= zC && t < simulationTime )
    {      
      /* 
	 The formula for the collision rate is 
	 collisionRate = nGas * cross section(E) * magnitude(v) 
      */
      crossSection = collisionCrossSectionArPhelps( ionAr.kineticEnergyeV(v,v_,v__) );
      collisionRate = nGas * crossSection * ionAr.magnitude(v,v_,v__);
      collisionsindt = collisionRate * dt; 
      collisionProbability = ran2(randomSeed);
      
      if (collisionProbability < collisionsindt)
	{
	  int type = collisionType();
	  if (type == 1) ionAr.elasticCollision(v, v_, v__);
	  else /*2*/ ionAr.cxCollision(v, v_, v__);
	}
      else
	{
	  Efz = Ez.returnElectricField(z);
	  ionAr.rungeKutta4th(z, v, t, Efz);
	}
      
      if(saveTrajectory) file  << t <<","<< z <<","<< v <<","<< v_ << endl;
      
      if( z < zG0 && !crossedzG0 )
	{
	  crossedzG0 = true;
	  ofstream file3("output/ionEnergy.csv", ios::app);
	  file3 << ionAr.kineticEnergyeV(v,0,0) << ","; /*energy due to vz only*/
	  file3 << ionAr.kineticEnergyeV(v,v_,v__);     /*total kinetic energy*/
	  file3 << endl;
	  file3.close();
	} 
      
      t = t + dt;
    }
  file.close();
  
  ofstream file2("output/ionCount.csv", ios::app);
  float energy = ionAr.kineticEnergyeV(v,v_,v__);
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




void rfea::executeSimulation(void)
{
	if (scan) energyScan();
	if (trajectory) integrateIonTrajectory(true, long( random01()*1000 ) );
}
