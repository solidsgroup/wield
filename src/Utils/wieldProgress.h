#ifndef WIELD_UTILS_PROGRESS_H
#define WIELD_UTILS_PROGRESS_H

#include "Utils/wieldColor.h"

#define WIELD_PROGRESS_BAR_WIDTH 30

#define WIELD_PROGRESS(MESSAGE, CURRENT, TOTAL, DD)	\
  {									\
    double p = (float)(CURRENT+DD)/(float)(TOTAL);			\
    cout << "\r";							\
    cout.width(30);							\
    cout << left << MESSAGE;						\
    cout.width(1);							\
    cout << WIELD_COLOR_B_ON;						\
    cout << "[";							\
    if ((int)(100*p) >= 100) cout << WIELD_COLOR_FG_GREEN;		\
    else cout << WIELD_COLOR_FG_YELLOW;					\
    for (int wpbi=0; wpbi<WIELD_PROGRESS_BAR_WIDTH; wpbi++)		\
      if ((float)wpbi/(float)WIELD_PROGRESS_BAR_WIDTH < p) cout << "=";	\
      else cout << " ";							\
    cout << WIELD_COLOR_FG_DEFAULT;					\
    cout << "]";							\
    cout.width(5);							\
    cout << right;							\
    if ((int)(100*p) >= 100) cout << 100;				\
    else cout << (int)(100*p);						\
    cout << "% " << flush;						\
    cout << WIELD_COLOR_RESET;						\
  }

#endif//WIELD_UTILS_PROGRESS_H
