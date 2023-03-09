#ifndef XSECTION_H
#define XSECTION_H

#include <iostream>
#include <fstream>

using namespace std;

class XSection
{
 private:  
  char process[30];
  int M;
  float threshold;
  float * E;
  float * sigma;

 public:
  void Setup(char * name);
  void Data(void);
  float sigma_(float energy);
  void printProcessName(void);
  char * process__(void);
  float threshold_(void);
};

#endif /*XSECTION_H*/
