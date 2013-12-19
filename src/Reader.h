#ifndef READER_D
#define READER_D

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <array>
#include "colors.h"
#include "muParser.h"
#include "readline/readline.h"


#define ERROR_TAG_NOT_FOUND 1
#define ERROR_VECTOR_TOO_SHORT 2
#define ERROR_FILE_NOT_FOUND 3
#define ERROR_DEFINED_WITH_NO_VALUE 4

using namespace std;
using namespace mu;

class Reader
{
 public:
  Reader();
  Reader(string filename, bool _verbose = false)
    {
      verbose = _verbose;
      p.DefineConst("pi", 3.14159);
      p.DefineConst("e", 2.71828);
      file.open(filename.c_str());
      if (!file.good()) {cout << "Error: File not found" << endl; throw(ERROR_FILE_NOT_FOUND);}
      FindMacros(0,NULL);
    };

  Reader(string filename, int argc, char **argv, bool _verbose = false)
    {
      verbose = _verbose;
      p.DefineConst("pi", 3.14159);
      p.DefineConst("e", 2.71828);
      file.open(filename.c_str());
      if (!file.good()) {cout << "Error: File not found" << endl; throw(ERROR_FILE_NOT_FOUND);}
      FindMacros(argc, argv);
    };

  ~Reader()
    {file.close();};

  template <size_t cols>
    int ReadData(vector<array<double,cols> > &val)
  {
    file.clear(); file.seekg(0,ios::beg); 
      string line, token;
      string ret; ret = "";
      int cont_delim;
      getline(file,line);
      while (!file.eof())
	{
	  int comment = line.find("#");
	  if (comment != string::npos)
	    continue;   // In a data file, only allow full line comments
	  istringstream iss(line);
	  string token;
	  array<double, 2> row;
	  for (int j=0; j<2; j++)
	    {
	      iss >> token;
	      row[j] = atof(token.c_str());
	      if (verbose) cout << row[j] << " ";
	    }
	  if (verbose) cout << endl;
	  val.push_back(row);
	  getline(file, line);
	}
  }

  // Allow for a default value
  template <class Type>
    int Read(Type &val, string title, Type def) 
    {
      bool temp = verbose;
      try 
	{
	  
	  verbose = false;
	  Read(val, title);
	} 
      catch (int err) 
	{
	  verbose = temp;
	  val = def;
	  if (verbose)
	    cout << setw(5) << FG_YELLOW << B_ON << left << setw(20) << title << std::setw(50) << right << val << setw(5) << RESET << endl;
	}
      verbose = temp;
    };

  int Read(int &val, string title) 
  {
    val = atoi(FindTag(title).c_str());
    if (verbose) 
      cout << setw(5) << FG_GREEN << B_ON << left << setw(20) << title << std::setw(50) << right << val << setw(5) << RESET << endl;
  };

  int Read(double &val, string title) 
  {
    //    val = atof(FindTag(title).c_str());
    p.SetExpr(FindTag(title));
    val = p.Eval();
    if (verbose) 
      cout << setw(5) << FG_GREEN << B_ON << left << setw(20) << title << std::setw(50) << right << val << setw(5) << RESET << endl;
  };

  int Read(string &val, string title)
  {
    val = FindTag(title);
    if (verbose) 
      cout << setw(5) << FG_GREEN << B_ON << left << setw(20) << title << std::setw(50) << right << val << setw(5) << RESET << endl;
  };

  template <class EigenMatrix>
    int Read(EigenMatrix &val, string title)
  {
    string in = FindTag(title), token;
    istringstream iss(in);
    int rows = val.rows(); int cols = val.cols();
    for (int i=0; i<rows; i++)
      for (int j=0; j<cols; j++)
	if (iss >> token)
	  {val(i,j) = atof(token.c_str()); }
	else
	  {cout << "Error: vector \"" << title << "\" too short" << endl; throw(ERROR_VECTOR_TOO_SHORT);}
    if (verbose) 
      if (val.cols() == 1) 
	{
	  stringstream ss;
	  ss << val.transpose().row(0);
	  cout << setw(5) << FG_GREEN << B_ON << left << setw(20) << title << std::setw(50) << right << ss.str()  << setw(5) << RESET << endl;
	}
      else if (val.rows() == 1) 
	{
	  stringstream ss;
	  ss << val.transpose().row(0);
	  cout << setw(5) << FG_GREEN << B_ON << left << setw(20) << title << std::setw(50) << right << ss.str() << setw(5) << RESET << endl;
	}
      else 
	for (int i=0;i<val.rows();i++)
	  if (i==0)
	    {
	      stringstream ss;
	      ss << val.transpose().row(0);
	      cout << setw(5) << FG_GREEN << B_ON << left << setw(20) << title << std::setw(50) << right << ss.str() << setw(5) << RESET << endl;
	    }
	  else
	    {
	      stringstream ss;
	      ss << val.transpose().row(0);
	      cout << setw(5) << FG_GREEN << B_ON << left << setw(20) << "" << std::setw(50) << right << ss.str() << setw(5) << RESET << endl;
	    }
  };

  template <int size>
    int Read(double val[size][size][size], string title)
    {
      string in = FindTag(title), token;
      istringstream iss(in);
      for (int i=0; i<size; i++)
	for (int j=0; j<size; j++)
	  for (int k=0; k<size; k++)
	    if (iss >> token)
	      {val[i][j][k] = atof(token.c_str()); }
	    else
	      {cout << "Error: matrix \"" << title << "\" too short" << endl; throw(ERROR_VECTOR_TOO_SHORT);}
    };

 private:
  Parser p;
  bool verbose;
  ifstream file;
  map<string,string> macros;
  string FindTag(string title)
    {
      file.clear(); file.seekg(0,ios::beg); 
      string line, token;
      string ret; ret = "";
      int cont_delim;
      while (!file.eof())
	{
	  getline(file, line);
	  int comment = line.find("#");
	  if (comment != string::npos)
	    line.replace(comment, string::npos, "");
	  istringstream iss(line);
	  iss >> token;
	  if (token == title)
	    //if (line.find(title) != string::npos)
	    {
	      ret = ret + line;
	      while ((cont_delim=ret.find("...")) != string::npos)
	      	{
	      	  ret.erase(cont_delim, ret.size() - cont_delim);  // remove delimiting \
	      	  //getline(file, line); // get next line
	      	  getline(file, line); // get next line
		  int comment = line.find("#");
		  if (comment != string::npos)
		    line.replace(comment, string::npos, "");
	      	  ret = ret + line;  // add next to return value
	      	}
	      ret.erase(0,title.size()+1);
	      return MacroReplace(ret);
	    }
	}
      if (file.eof()) 
	{if(verbose) cout << B_ON << FG_RED << title << RESET << endl;throw(ERROR_TAG_NOT_FOUND);}
    }

  int FindMacros(int argc, char **argv)
  {
    file.clear(); file.seekg(0,ios::beg); 
    string line;
    string macroname;
    string macroval;
    while (!file.eof())
      {
	getline(file, line);
	int comment = line.find("#");
	if (comment != string::npos)
	  line.replace(comment, string::npos, "");
	int divide = line.find("=");
	if (divide != string::npos)
	  {
	    macroname = line.substr(0,divide);
	    macroval = line.substr(divide+1,line.size()-divide);
	    if (macroval.find("???") != string::npos)
	      {
		bool found = false;
		for (int i=0; i<argc; i++)
		  {
		    string arg(argv[i]);
		    if(arg.find("-D"+macroname) != string::npos)
		      if (i<(argc-1)) {macroval = argv[i+1];found=true;continue;}
		      else {cout << "Error: " << macroname << "defined in call but has no value" << endl; throw(ERROR_DEFINED_WITH_NO_VALUE); }
		  }
		if (!found)
		  {
		    macroval = readline(("Please set a value for " + macroname + ": ").c_str());
		    cout << "Macro set: "<< macroname << " = " << macroval << endl;
		  }
	      }
	    try
	      {
		p.SetExpr(macroval);
		macros.insert(make_pair(macroname, to_string(p.Eval())));
	      }
	    catch(Parser::exception_type &err)
	      {
		macros.insert(make_pair(macroname, macroval));
	      }
	  }
      }
  }
  string MacroReplace(string input)
  {
    string output = input;
    map<string,string>::iterator pmacros = macros.begin();
    for(pmacros=macros.begin();pmacros != macros.end(); pmacros++)
      {
	int loc = output.find(pmacros->first);
	while (loc != string::npos)
	  {
	    output.replace(loc,(pmacros->first).size(),pmacros->second);
	    loc = output.find(pmacros->first);
	  }
      }
    return output;
  }
};
#endif
