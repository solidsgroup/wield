#ifndef TCLAP_IGNORE_ARGUMENT_H
#define TCLAP_IGNORE_ARGUMENT_H
 
#include <string>
#include <vector>
 
#include <tclap/Arg.h>
#include <tclap/Constraint.h>
 
namespace TCLAP {
 
class IgnoreArg : public Arg 
{
protected:
 
  std::string _typeDesc;
 
  // void _extractValue( const std::string& val );
 
public:
 
  IgnoreArg( const std::string& flag, 
	    const std::string& desc, 
	    const std::string& typeDesc,
	    Visitor* v = NULL);
                  
                  
  IgnoreArg( const std::string& flag, 
	    const std::string& desc, 
	    const std::string& typeDesc,
	    CmdLineInterface& parser,
	    Visitor* v = NULL );
  
  
  virtual bool processArg(int* i, std::vector<std::string>& args); 
 
  virtual std::string shortID(const std::string& val = "val") const;
 
  virtual std::string longID(const std::string& val = "val") const;
         
  virtual void reset() ;
 
private:
  IgnoreArg(const IgnoreArg& rhs);
  IgnoreArg& operator=(const IgnoreArg& rhs);
};
 
 
IgnoreArg::IgnoreArg(const std::string& flag, 
		      const std::string& desc, 
		      const std::string& typeDesc,
		      Visitor* v)
  : Arg(flag, "", desc, false, false, v),
    _typeDesc( typeDesc )
{ }
 
IgnoreArg::IgnoreArg(const std::string& flag, 
		      const std::string& desc, 
		      const std::string& typeDesc,
		      CmdLineInterface& parser,
		      Visitor* v)
  : Arg(flag, "", desc, false, false, v),
    _typeDesc( typeDesc )
{ 
  parser.add( this );
}

bool IgnoreArg::processArg(int *i, std::vector<std::string>& args)
{
  if (args[*i].find("-"+_flag) == 0) {(*i)++; return true;}
  else return false;
}
 
std::string IgnoreArg::shortID(const std::string& val) const
{
  // TODO
  static_cast<void>(val); // Ignore input, don't warn
  return Arg::shortID( _typeDesc ); 
}
 
std::string IgnoreArg::longID(const std::string& val) const
{
  // TODO
  static_cast<void>(val); // Ignore input, don't warn
  return Arg::longID( _typeDesc ); 
}
 
void IgnoreArg::reset()
{
  Arg::reset();
}
 
} // namespace TCLAP
 
#endif
