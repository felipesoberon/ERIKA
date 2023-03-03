#include "random.h"

/*Subroutine taken form Numerical recipies in C*/
float ran2(long idum)
{
  int j;
  long kk;
  static long idum2=123456789;
  static long iy=0;
  static long iv[NTAB];
  float temp;
  if (idum <= 0) 
    { 
      if (-(idum) < 1) idum=1; 
      else idum = -(idum);
      idum2=(idum);
      for (j=NTAB+7;j>=0;j--) 
	{ 
	  kk=(idum)/IQ1;
	  idum=IA1*(idum-kk*IQ1)-kk*IR1;
	  if (idum < 0) idum += IM1;
	  if (j < NTAB) iv[j] = idum;
	}
      iy=iv[0];
    }
  kk=(idum)/IQ1; 
  idum=IA1*(idum-kk*IQ1)-kk*IR1; 
  if (idum < 0) idum += IM1;
  kk=idum2/IQ2;
  idum2=IA2*(idum2-kk*IQ2)-kk*IR2; 
  if (idum2 < 0) idum2 += IM2;
  j=iy/NDIV; 
  iy=iv[j]-idum2; 
  iv[j] = idum;
  if (iy < 1) iy += IMM1;
  if ((temp=AM*iy) > RNMX) return RNMX; 
  else return temp;
}
