#include "rfea.h"


void rfea::setParametersFromCommandLineInput(int numberOfArguments, char* valueOfArgument[])
{
  cout << "\nCOMMAND_LINE_INPUT_PARAMETERS\n\n";
  
  commandLine.setArgumentList(numberOfArguments, valueOfArgument);
  commandLine.printArgumentList();
  
  commandLine.setFlagName("-max_eV", "Scan's maximum energy in eV.");                     //0
  commandLine.setFlagName("-step_eV", "Scan's energy step in eV.");                       //1
  commandLine.setFlagName("-no._ion", "Scan's number of ions per step.");                 //2
  commandLine.setFlagName("-pressure_Pa", "Argon gas pressure in Pa.");                   //3
  commandLine.setFlagName("-sim_time", "Maximum simulation time per ion (s).");           //4
  commandLine.setFlagName("-sim_type", "Trajectory (0), Scan (1), or Space Charge (2) "); //5
  commandLine.setFlagName("-G2", "Grid 2 voltage");                                       //6
  commandLine.setFlagName("-spacerStack", "No. of 100um spacers between grids (e.g. 2332)"); //7
  commandLine.setFlagName("-plasmaDensity", "Density of plasma at edge of sheath (m-3)");    //8
  commandLine.setFlagName("-plasmaPotential", "Plasma sheath voltage");                      //9
  commandLine.setFlagName("-gridTransparency", "Transparency of the grids in percentage");   //10
  commandLine.setFlagName("-RF", "Frequency (Hz) (input 0 for DC)");                         //11
  commandLine.setFlagName("-Te", "Electron temperature (eV)");                               //12
  
    
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
    simulationType =  int( commandLine.returnFloatFlagValue(5) );
  
  if (commandLine.flagValueIsNumber(6))
    G2 =  commandLine.returnFloatFlagValue(6);
  
  if (commandLine.flagValueIsNumber(7))
    spacerStack =  int( commandLine.returnFloatFlagValue(7) );

  if (commandLine.flagValueIsNumber(8))
    plasmaDensity = commandLine.returnFloatFlagValue(8);
  
  if (commandLine.flagValueIsNumber(9))
    plasmaPotential = commandLine.returnFloatFlagValue(9);

  if (commandLine.flagValueIsNumber(10))
    gridTransparency = int( commandLine.returnFloatFlagValue(10) );
  
  if (commandLine.flagValueIsNumber(11))
    radioFrequency = commandLine.returnFloatFlagValue(11);

  if (commandLine.flagValueIsNumber(12))
    electronTemperature = commandLine.returnFloatFlagValue(12);

  cout << endl;
}



void rfea::setSpacerStack(void)
{
  G0G1d = spacerThickness * float( int(spacerStack/1000) ); 
  G1G2d = spacerThickness * float( int(spacerStack/100)%10 ); 
  G2G3d = spacerThickness * float( int(spacerStack/10)%10 );
  G3Cd  = spacerThickness * float( spacerStack%10); 
}


void rfea::setVoltageGrids013C(float g0, float g1, float g3, float c)
{ G0 = g0;  G1 = g1;  G3 = g3;  C  = c; }



void rfea::setElectricField(void)
{
  Ez.setPlasma(plasmaPotential, plasmaDensity, radioFrequency, pressurePa, electronTemperature);
  
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




void rfea::integrateIonTrajectory(long randomSeed)
{
  float dt =  ionAr.returndt();
  float zG0 = Ez.returnzG0();
  float zC =  Ez.returnzC();
  float zP =  Ez.returnzP();

  plasma vBohm;
  vBohm.calculateBohmVelocity();
  
  float z = zP;           // Initial position of the particle in m
  float z_= z;            // previous position
  float v = -vBohm.returnBohmVelocity(); // Vz of the particle in m/s
  float v_= 0.0;          // Vperpendicular 
  float v__ = 0.0;        // Third velocity component (ignored)
  float t = 0.0;          // Initial time in seconds
  
  float Efz = 0.0;
  
  float k = 1.3806503E-23;       //m2 kg s-1 K-1
  float T = 300;                 //Kelvin
  float nGas = pressurePa/(k*T); //m-3
  
  float collisionProbability = 0.0;
  float crossSection;
  float collisionRate;
  float collisionsindt = 0.0;
  bool  crossedzG0 = false;
  int   gridNo = -1;

  float period = 0;
  float phase = 0;
  if (radioFrequency>0)
    { period = 1/radioFrequency;
      phase = random01()*period; }
  
  ofstream file("output/trajectory.csv");
  if(saveTrajectory) file << "Time(s), z(m), vz(m/s), vp(m/s)" << endl;
  
  while ( zP >= z && z >= zC && t < simulationTime )
    {

      if (pressurePa > 0.0) {
	/* The formula for the collision rate is 
	   collisionRate = nGas * cross section(E) * magnitude(v)  */
	crossSection   = collisionCrossSectionArPhelps( ionAr.kineticEnergyeV(v,v_,v__) );
	collisionRate  = nGas * crossSection * ionAr.magnitude(v,v_,v__);
	collisionsindt = collisionRate * dt; 
	collisionProbability = ran2(randomSeed);
      }
      
      if (pressurePa > 0.0 && collisionProbability < collisionsindt)
	{
	  int type = collisionType();
	  if    (type == 1)  ionAr.elasticCollision(v, v_, v__);
	  else /*type == 2*/ ionAr.cxCollision(v, v_, v__);
	}
      else
	{
	  Efz = Ez.returnElectricField(z, t+phase);
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
      
      if ( isAtGrid(z,z_,gridNo) && random01()*100 > gridTransparency ) break;
      else gridNo = -1;
      
      t = t + dt;
      z_= z;
    }
  file.close();
  
  ofstream file2("output/ionCount.csv", ios::app);
  float energy = ionAr.kineticEnergyeV(v,v_,v__);
  if ( z <= zC ) file2 << G2 << "  ,  " << 1 << "  ,  " << energy << endl;
  else           file2 << G2 << "  ,  " << 0 << "  ,  " << energy << endl;
  file2.close();

  if (saveLastPosition == true)
    {
      if ( z <= zC ) gridNo = 4;
      ofstream file3("output/spaceCharge.csv", ios::app);
      file3 << z << "," << v << "," << v_ << "," << gridNo << endl;
      file3.close();
    }
}




void rfea::energyScan(void)
{
  for (int i=0; i<maxEnergy; i=i+stepEnergy)
    {
      cout << "Energy (eV) = " << i << endl;
      for(int j=1; j<=ionsPerEnergy; j++)
	{
	  setG2( float(i) );
	  integrateIonTrajectory(long(i+1+j));
	}
    }
}




void rfea::spaceCharge(void)
{
  float simTime = simulationTime;
  for(int j=1; j<=ionsPerEnergy; j++)
    {
      simulationTime = simTime*random01();
      integrateIonTrajectory(long(1+j));
    }
}





void rfea::executeSimulation(void)
{
  switch (simulationType)
    {
    case 0:
      {
	cout << "\nComputing single trajectory" << endl;
	saveTrajectory = true;
	integrateIonTrajectory(long( random01()*1000 ) );
	break;
      }
    case 1:
      {
	cout << "\nRFEA scan" << endl;
	energyScan();
	break;
      }
    case 2:
      {
	cout << "\nComputing multiple trajectories for space charge" << endl;
	saveLastPosition = true;
	spaceCharge();
	break;
      }
    default:
      {
	cout << "\nERROR: simulation type option, " << simulationType << ", invalid." << endl;
	cout << "Program termination(!)" << endl;
      }
    }
}




bool rfea::isAtGrid(float zi, float zii, int & gridNumber)
{
  bool atGrid = false;
  
  if ( gridTransparency <100 )
    {
      float zG0 = Ez.returnzG0();
      float zG1 = Ez.returnzG1();
      float zG2 = Ez.returnzG2();
      float zG3 = Ez.returnzG3();
      
      float zz = zi;
      
      if (zi < zii)
	{
	  zi  = zii;
	  zii = zz;
	}
      
      if      (zi > zG0 && zG0 > zii) { atGrid = true; gridNumber = 0; }
      else if (zi < zG0 && zG0 < zii) { atGrid = true; gridNumber = 0; }
      else if (zi > zG1 && zG1 > zii) { atGrid = true; gridNumber = 1; }
      else if (zi < zG1 && zG1 < zii) { atGrid = true; gridNumber = 1; }
      else if (zi > zG2 && zG2 > zii) { atGrid = true; gridNumber = 2; }
      else if (zi < zG2 && zG2 < zii) { atGrid = true; gridNumber = 2; }
      else if (zi > zG3 && zG3 > zii) { atGrid = true; gridNumber = 3; }
      else if (zi < zG3 && zG3 < zii) { atGrid = true; gridNumber = 3; }
      else atGrid = false; 
    }
  return atGrid;
}
