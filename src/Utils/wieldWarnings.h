#ifndef WIELD_WARNINGS_H
#define WIELD_WARNINGS_H

#include "Utils/wieldColor.h"

#define WIELD_WARNING(MESSAGE)						\
  {									\
    std::cout << WIELD_COLOR_B_ON;					\
    std::cout << WIELD_COLOR_FG_YELLOW;					\
    std::cout << "Warning at " << __FILE__ << ":" << __LINE__ << ": ";	\
    std::cout << WIELD_COLOR_RESET;					\
    std::cout << MESSAGE;						\
    std::cout << endl;							\
  }

#endif // WIELD_EXCEPTION_H
