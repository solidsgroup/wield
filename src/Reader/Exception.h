#ifndef UTILS_EXCEPTION_H
#define UTILS_EXCEPTION_H
#include <stdexcept>
#include <sstream>
#include <string>
#include <iostream>

#include "Color.h"

#define READER_EXCEPTION(MESSAGE)					\
  {									\
    std::cout << READER_COLOR_B_ON;					\
    std::cout << "Exception " << READER_COLOR_FG_GREEN << "caught";	\
    std::cout << READER_COLOR_FG_DEFAULT << ": " << MESSAGE << std::endl ;	\
    std::cout << "\t" << READER_COLOR_B_ON << READER_COLOR_FG_BLUE << __FILE__;	\
    std::cout << READER_COLOR_FG_DEFAULT << ":";			\
    std::cout << READER_COLOR_FG_BLUE << __LINE__ <<READER_COLOR_FG_DEFAULT << std::endl; \
    std::cout << "\t" << READER_COLOR_FG_YELLOW << __func__;		\
    std::cout << READER_COLOR_RESET << std::endl;				\
    throw;								\
  }
#define READER_NEW_EXCEPTION(MESSAGE)					\
  {									\
    std::cout << READER_COLOR_B_ON << "Exception " <<READER_COLOR_FG_RED<< "thrown"; \
    std::cout << READER_COLOR_FG_DEFAULT << ": " << MESSAGE << std::endl ;	\
    std::cout << "\t" << READER_COLOR_B_ON << READER_COLOR_FG_BLUE<<__FILE__; \
    std::cout << READER_COLOR_FG_DEFAULT << ":";			\
    std::cout << READER_COLOR_FG_BLUE <<__LINE__ <<READER_COLOR_FG_DEFAULT << std::endl; \
    std::cout << "\t" << READER_COLOR_FG_YELLOW << __func__;		\
    std::cout << READER_COLOR_RESET<<std::endl;				\
    std::stringstream ss; ss << MESSAGE; throw std::runtime_error(ss.str()); \
  }

#define READER_TRY try {
#define READER_CATCH } catch (std::exception &e) {READER_EXCEPTION("");} catch (int i) {READER_EXCEPTION("");} 
#define READER_CATCH_MSG(MESSAGE) } catch (std::exception &e) {READER_EXCEPTION(MESSAGE);} catch (int i) {READER_EXCEPTION(MESSAGE);}

#endif // UTILS_EXCEPTION_H
