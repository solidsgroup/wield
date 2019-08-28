#ifndef READER_TRANSLATORS_H
#define READER_TRANSLATORS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include <complex>

#include "Exception.h"
#include "StringUtils.h"

#ifdef MUPARSER
#include "muParser.h"
#endif

namespace Reader
{

template<class T> struct Interpreter;

double EvaluateMath(const std::string varUnparsed);

//
// Strings
// 

template<> struct Interpreter<std::string>
{
  void operator() (const std::string varUnparsed, std::string *varParsed)
  {
    READER_TRY;
    *varParsed = varUnparsed;
    READER_CATCH_MSG("Error parsing std::string: " << varUnparsed);
  }
};

template<> struct Interpreter<char *>
{
  void operator() (const std::string varUnparsed, char **varParsed)
  {
    READER_TRY;
    *varParsed = (char*)malloc(varUnparsed.size());
    memcpy(*varParsed, varUnparsed.c_str(), varUnparsed.size()+1);
    READER_CATCH_MSG("Error parsing string: " << varUnparsed);
  }
};

// chars

template<> struct Interpreter<std::vector<char> >
{
  void operator() (const std::string varUnparsed, std::vector<char> *varParsed)
  {
    READER_TRY;
    std::istringstream iss(varUnparsed); 
    std::string token;
    for (unsigned int i=0; iss >> token ;i++)
      {
	if (i<varParsed->size())
	  (*varParsed)[i] = token.at(0);
	else
	  (*varParsed).push_back(token.at(0));
      }
    READER_CATCH_MSG("Error parsing vector<char>: " << varUnparsed);
  }
};


//
// bool
//
template<> struct Interpreter<bool>
{
  void operator() (const std::string varUnparsed, bool *varParsed)
  {
    READER_TRY;
    if
      (varUnparsed.compare("True") == 0 ||
       varUnparsed.compare("true") == 0 ||
       varUnparsed.compare("T")    == 0 ||
       varUnparsed.compare("t")    == 0 ||
       varUnparsed.compare("Yes")  == 0 ||
       varUnparsed.compare("yes")  == 0 ||
       varUnparsed.compare("Y")    == 0 ||
       varUnparsed.compare("y")    == 0 ||
       varUnparsed.compare("1")    == 0 )
      *varParsed = true;
    else if 
      (varUnparsed.compare("False") == 0 ||
       varUnparsed.compare("false") == 0 ||
       varUnparsed.compare("F")     == 0 ||
       varUnparsed.compare("f")     == 0 ||
       varUnparsed.compare("No")    == 0 ||
       varUnparsed.compare("no")    == 0 ||
       varUnparsed.compare("N")     == 0 ||
       varUnparsed.compare("n")     == 0 ||
       varUnparsed.compare("0")     == 0 )
      *varParsed = false;
    else
      READER_NEW_EXCEPTION("Unacceptable boolean value");

    READER_CATCH_MSG("Error parsing string: " << varUnparsed);
  }
};



//
// integer
// 

template<> struct Interpreter<int>
{
  void operator() (const std::string varUnparsed, int *varParsed)
  {
    READER_TRY;
    *varParsed = (int)(EvaluateMath(varUnparsed));
    READER_CATCH_MSG("Error parsing integer: " << varUnparsed);
  }
};

//
// float
// 

template<> struct Interpreter<float>
{
  void operator() (const std::string varUnparsed, float *varParsed)
  {
    READER_TRY;
    *varParsed = EvaluateMath(varUnparsed);
    READER_CATCH_MSG("Error parsing float:" << varUnparsed);
  }
};

//
// double
// 

template<> struct Interpreter<double>
{
  void operator() (const std::string varUnparsed, double *varParsed)
  {
    READER_TRY;
    *varParsed = EvaluateMath(varUnparsed);
    READER_CATCH_MSG("Error parsing " << varUnparsed);
  }
};

//
// float vector
// 

template<> struct Interpreter<std::vector<float> >
{
  void operator() (const std::string varUnparsed, std::vector<float> *varParsed)
  {
    READER_TRY;
    std::istringstream iss(varUnparsed); 
    std::string token;
    for (unsigned int i=0; iss >> token ;i++)
      {
	if (i<varParsed->size())
	  (*varParsed)[i] = EvaluateMath(token);
	else
	  (*varParsed).push_back(EvaluateMath(token));
      }
    READER_CATCH_MSG("Error parsing vector<float>: " << varUnparsed);
  }
};

//
// double vector
// 

template<> struct Interpreter<std::vector<double> >
{
  void operator() (const std::string varUnparsed, std::vector<double> *varParsed)
  {
    READER_TRY;
    std::istringstream iss(varUnparsed); 
    std::string token;
    for (unsigned int i=0; iss >> token ;i++)
      {
	if (i<varParsed->size())
	  (*varParsed)[i] = EvaluateMath(token);
	else
	  (*varParsed).push_back(EvaluateMath(token));
      }
    READER_CATCH_MSG("Error parsing vector<double>: " << varUnparsed);
  }
};

//
// complex vector
//

template<> struct Interpreter<std::vector<std::complex<double> > >
{
  void operator() (const std::string varUnparsed, std::vector<std::complex<double> > *varParsed)
  {
    READER_TRY;
    std::istringstream iss(varUnparsed); 
    std::string token;
    for (unsigned int i=0; iss >> token ;i++)
      {
	std::string re=token, im=token;
	Reader::StringUtils::deleteAfter(re,"+i");
	Reader::StringUtils::deleteBefore(im,"+i");
	if (i<varParsed->size())
	  (*varParsed)[i] = std::complex<double>(atof(re.c_str()),atof(im.c_str()));
	else
	  (*varParsed).push_back(std::complex<double>(atof(re.c_str()),atof(im.c_str())));
      }
    READER_CATCH_MSG("Error parsing vector<double>: " << varUnparsed);
  }
};
}


#endif
