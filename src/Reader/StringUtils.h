#ifndef READER_STRINGUTILS_H
#define READER_STRINGUTILS_H
#include <string.h>

namespace Reader
{
namespace StringUtils
{
int replaceFirst(std::string &str, const std::string before, const std::string after);
int replaceAll(std::string &str, const std::string before, const std::string after);
int deleteAfter(std::string &str, const std::string find);
int deleteBefore(std::string &str, const std::string find);
bool contains(std::string &str, const std::string find);
bool beginsWith(std::string &str, const std::string find);
}
}
#endif
