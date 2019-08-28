#ifndef UTILS_WARNING_H
#define UTILS_WARNING_H
#include <stdexcept>
#include <sstream>
#include <string>
#include <iostream>

#include "Color.h"

#define READER_WARNING(MESSAGE)						\
  {									\
    std::cout << READER_COLOR_B_ON << READER_COLOR_FG_YELLOW;		\
    std::cout << "Reader Warning: ";					\
    std::cout << READER_COLOR_RESET;					\
    std::cout << MESSAGE;						\
    std::cout << std::endl;						\
  }

#endif // UTILS_WARNING_H
