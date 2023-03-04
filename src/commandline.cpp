#include "commandline.h"


commandline::commandline(void)
{
  flagValue.clear();
  flagName.clear();
  flagDescription.clear();
}



void commandline::setArgumentList(int inputNumberOfArguments, char* valueOfArgument[])
{
  for (int i=0; i<inputNumberOfArguments; i++)
    argument.push_back( valueOfArgument[i] );
}



void commandline::printArgumentList(void)
{
  cout << "\nECHO COMMAND: ";
  for (int i=0; i<argument.size(); i++)
    {
      cout << argument[i];
      cout << " ";
    }
  cout << endl;
}



void commandline::setFlagName(string flagTag, string flagDescriptionValue)
{
  flagName.push_back(flagTag);
  flagDescription.push_back(flagDescriptionValue);
  flagValue.push_back("EMPTY");
}




void commandline::printFlagNameList(void)
{
  cout << endl;
  for (int i=0; i<flagName.size(); i++)
    cout << i << "   " << setw(12) << flagName[i] << "\t" << flagDescription[i] << endl;
}





void commandline::setFlagValues(void)
{
  cout << endl;
  for (int i=0; i<flagName.size(); i++)
    {
      for (int j=0; j<argument.size(); j++)
	{
	  if ( flagName[i] == argument[j])
	    if( j+1 < argument.size() ) flagValue[i] = argument[j+1];
	    else flagValue[i] = "EMPTY";
	}
    }
}





void commandline::printFlagValues(void)
{
  for (int i=0; i<flagName.size(); i++)
    {
      cout << i << "   " << setw(12) << flagName[i] << "\t" << flagValue[i] <<  endl;
    }
}




string commandline::returnFlagValue(int flagIndex)
{
  if (flagIndex < flagValue.size())
    return flagValue[flagIndex];
  else
    return "ERROR";
}




float commandline::returnFloatFlagValue(int flagIndex)
{
  float result = 0.0;
  if (flagValueIsNumber(flagIndex))
    { result = stof( flagValue[flagIndex] ); }
  else
    { cout << "ERROR: flag value is not a number." << endl; }    
  return result;
}




bool commandline::flagValueIsEMPTY(int flagIndex)
{
  bool result = false;
  if (flagIndex < flagValue.size())
    if (flagValue[flagIndex] == "EMPTY")
      result = true;
  return result;
}




bool commandline::flagValueIsNumber(int flagIndex)
{
  if (flagIndex < flagValue.size())
    {
      try
	{
	  stof( flagValue[flagIndex] );
	  return true;
	}
      catch (invalid_argument)
	{ return false; }
    }
  else
    {
      cout << "ERROR: flag index exceeds limits." << endl;
      return false;
    }
}







