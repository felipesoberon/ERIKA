#include "XSection.h"

/*
  This subroutine sets up the cross section array. First the information on the cross
  section file is read. Then the number of data pairs is read. According to this number
  the subroutine generates an array of size (2^n+1), where n is an integer an is to be 
  determined. The condition is that if there are N pairs in the data file then
  2^n >= N-1. The array elements from the original data are
  
  0----1----2----3----4----5----6----7----.....----(N-1)
  
  To this array elements an extemsion is added
  
  ...----N----(N+1)----...----(2^n)
  
  So that the half section value searcher can be used to find the cross section value
  for a given energy. The final array must have (M = 2^n+1) elements. And index run
  from 0 to 2^n !
  
*/
void XSection::Setup(char * name)
{
  int N, i, aux;
  ifstream in(name);
  
  //Read the header of the data file 
  in >> process;
  in >> threshold;
  in >> N;
  
  //Search for the closest exponential of 2
  aux = 1;
  for (i=1; i<=25; i++)
    { 
      aux = aux *2;
      if ( aux >= N-1 )  
      {
	/*
	  This is the closest exponential of 2, this is
	  aux = 2^i, then the size of the array in order to
	  house all the elements is (aux+1)
	*/
	M = aux + 1;
	break;
      }
    }

  //Create the arrays, size M = 2^n +1
  E = new float[M];
  sigma = new float[M];
  
  //Assign the elements form 0 to M-1
  for (i=0; i<=M-1; i++)
    {
      if ( i<=N-1 ) 
	{
	  in >> E[i] >> sigma[i];
	}
      else 
	{
	  E[i] = E[N-1];
	  sigma[i] = sigma[N-1];
	}
    }
  in.close();
  
  /*
    If needed to check the setup cross section arrays
    then uncoment the next line. This will not affect 
    performance of the code. It will output on the
    screen the arrays at the setup (only).
  */
  //Data();
}



/*
  This subroutine prints the data of the cross section on the screen. This
  can be used to verify the setup subroutine.
*/
void XSection::Data()
{
  int i;
  cout << endl << process << endl;
  for (i=0; i<=M-1; i++) cout << i << "\t" << E[i] << "\t" << sigma[i] << endl;
}




/*
  This function returns the Cross Section as a function of the input Energy
  in electron volts. The search engine should take a fixed number of steps
  to find the interval in which the input energy is found and then perform 
  a linear interpolation to find the corresponding cross section. 
*/
float XSection::sigma_(float energy)
{
  float temp = -1.0;
  int i, i1, i2, i3;
  i1 = 0;
  i2 = (M-1)/2;  //M-1 = 2^n !
  i3 = (M-1);

  //The search algorithm
  for (i=0; i<=M-1; i++)
    {
      if ( E[i1] <= energy && energy < E[i2] )
	{
	  if (i1+1 == i2) 
	    {
	      temp = (sigma[i2] - sigma[i1])/(E[i2]-E[i1])*(energy - E[i1]) + sigma[i1];
	      break;
	    }
	  i3 = i2;
	  i2 = (i3+i1)/2;
	}//if
      else if ( E[i2] <= energy && energy <= E[i3] )
	{
	  if (i2+1 == i3) 
	    {
	      temp = (sigma[i3] - sigma[i2])/(E[i3]-E[i2])*(energy - E[i2]) + sigma[i2];
	      break;
	    }
	  i1 = i2;
	  i2 = (i3+i1)/2;
	}//else
    }//for
  
  //An alert flag in case the energy of the particle lies outside the cross section energy range
  if (temp == -1.0) cout << "ALERT: Xsection failed --> " << process << "   Energy --> " << energy << endl;
  return temp;
}

void XSection::printProcessName(void) { cout <<  process; }

char * XSection::process__(void) { return process; }

float XSection::threshold_(void) { return threshold; }


/* From LXCat, Phelps data on isotropic collision cross section Ar+ + Ar */
float XSection::sigmaArElasticPhelps(float energy)
{ return 2e-19/sqrt(2.*energy)/(1.+2.*energy) + 3e-19 *2.*energy/pow(1.+2.*energy/3.,2.3); }


/* From LXCat, Phelps data on bacscattering collision cross section Ar+ + Ar */
float XSection::sigmaArCXPhelps(float energy)
{ return 0.5 * ( 1.15e-18 * pow(1.+0.015/2./energy,0.6)/pow(2.*energy,0.1) - 2e-19/sqrt(2.*energy)/(1.+2.*energy)
	      -3E-19*2.*energy/pow(1.+2.*energy/3.,2.3)
		 ); }
