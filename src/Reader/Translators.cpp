#include <string>
#include "Utils/wieldExceptions.h"
#include "Translators.h"

namespace Reader
{
double EvaluateMath(const std::string varUnparsed)
{
#ifdef MUPARSER
  try
    {
      mu::Parser p;
      p.SetExpr(varUnparsed);
      return p.Eval();
    }
  catch(mu::ParserError e)
    {
      READER_NEW_EXCEPTION("MuParser had an error parsing the expression: " << varUnparsed);
    }
#else
  WIELD_EXCEPTION_TRY;
  return atof(varUnparsed.c_str());
  WIELD_EXCEPTION_CATCH;
#endif
}
}