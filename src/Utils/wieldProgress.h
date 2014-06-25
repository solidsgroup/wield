#ifndef WIELD_UTILS_PROGRESS_H
#define WIELD_UTILS_PROGRESS_H

#define WIELD_PROGRESS(MESSAGE, CURRENT, TOTAL) \
      cout << "\r"; \
      cout.width(30); \
      cout << left << MESSAGE; \
      cout.width(5); \
      cout << right << (int)ceil(100*(float)(CURRENT)/(float)(TOTAL)) << "% " << flush; 

#endif
