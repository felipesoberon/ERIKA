#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;


class commandline
{
 private:

  vector<string> argument;
  vector<string> flagName;
  vector<string> flagValue;
  vector<string> flagDescription;
 
  
 public:
  
  commandline(void);
  
  void setArgumentList(int inputNumberOfArguments, char* valueOfArgument[]);
  void printArgumentList(void);
  
  void setFlagName(string flagTag, string flagDescriptionValue);
  void printFlagNameList(void);

  void setFlagValues(void);
  void printFlagValues(void);
  
  string returnFlagValue(unsigned int flagIndex);
  float returnFloatFlagValue(unsigned int flagIndex);

  bool flagValueIsEMPTY(unsigned int flagIndex);
  bool flagValueIsNumber(unsigned int flagIndex);

  
};

#endif
