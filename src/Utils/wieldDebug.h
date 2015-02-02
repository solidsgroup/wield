#ifndef WIELD_DEBUG_H
#define WIELD_DEBUG_H

#include "Utils/wieldColor.h"

#define WIELD_DEBUG(MESSAGE)						\
  {									\
    std::cout << WIELD_COLOR_B_ON;					\
    std::cout << WIELD_COLOR_FG_BLUE;					\
    std::cout << "Debug at " << __FILE__ << ":" << __LINE__ << ": ";	\
    std::cout << WIELD_COLOR_RESET;					\
    std::cout << MESSAGE;						\
    std::cout << endl;							\
  }

#endif // WIELD_DEBUG_H
