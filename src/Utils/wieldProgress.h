#ifndef WIELD_UTILS_PROGRESS_H
#define WIELD_UTILS_PROGRESS_H

#include "Utils/wieldColor.h"

#define WIELD_PROGRESS_BAR_WIDTH 30

#define WIELD_PROGRESS(MESSAGE, CURRENT, TOTAL, DD)			\
  {									\
    double p = (float)(CURRENT+DD)/(float)(TOTAL);			\
    std::cout << "\r";							\
    std::cout.width(30);						\
    std::cout << std::left << MESSAGE;					\
    std::cout.width(1);							\
    std::cout << WIELD_COLOR_B_ON;					\
    std::cout << "[";							\
    if ((int)(100*p) >= 100) std::cout << WIELD_COLOR_FG_GREEN;		\
    else std::cout << WIELD_COLOR_FG_YELLOW;				\
    for (int wpbi=0; wpbi<WIELD_PROGRESS_BAR_WIDTH; wpbi++)		\
      if ((float)wpbi/(float)WIELD_PROGRESS_BAR_WIDTH < p)		\
	std::cout << "=";						\
      else std::cout << " ";						\
    std::cout << WIELD_COLOR_FG_DEFAULT;				\
    std::cout << "]";							\
    std::cout.width(5);							\
    std::cout << std::right;						\
    if ((int)(100*p) >= 100) std::cout << 100;				\
    else std::cout << (int)(100*p);					\
    std::cout << "% " << std::flush;					\
    std::cout << WIELD_COLOR_RESET;					\
  }

#define WIELD_PROGRESS_COMPLETE(MESSAGE)				\
  {									\
    std::cout << "\r";							\
    std::cout.width(30);						\
    std::cout << std::left << MESSAGE;					\
    std::cout.width(1);							\
    std::cout << WIELD_COLOR_B_ON;					\
    std::cout << "[";							\
    std::cout << WIELD_COLOR_FG_GREEN;					\
    for (int wpbi=0; wpbi<WIELD_PROGRESS_BAR_WIDTH; wpbi++)		\
      std::cout << "=";							\
    std::cout << WIELD_COLOR_FG_DEFAULT;				\
    std::cout << "]";							\
    std::cout.width(5);							\
    std::cout << std::right;						\
    std::cout << 100;							\
    std::cout << "% " << std::flush;					\
    std::cout << WIELD_COLOR_RESET;					\
    std::cout << std::endl;						\
  }

#endif//WIELD_UTILS_PROGRESS_H
