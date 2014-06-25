#ifndef WIELD_EXCEPTION_H
#define WIELD_EXCEPTION_H
#include <stdexcept>
#include <sstream>
#include <string>
#include <iostream>

#ifndef WIELD_NO_COLOR_GRAPHICS
#define WIELD_C_RESET               "\033[0m"
#define WIELD_C_B_ON                "\033[1m"
#define WIELD_C_FG_RED              "\033[31m"
#define WIELD_C_FG_GREEN            "\033[32m"
#define WIELD_C_FG_YELLOW           "\033[33m"
#define WIELD_C_FG_BLUE             "\033[34m"
#define WIELD_C_FG_DEFAULT          "\033[39m"
#else
#define WIELD_C_RESET               ""
#define WIELD_C_B_ON                ""
#define WIELD_C_FG_RED              ""
#define WIELD_C_FG_GREEN            ""
#define WIELD_C_FG_YELLOW           ""
#define WIELD_C_FG_BLUE             ""
#define WIELD_C_FG_DEFAULT          ""
#endif

#define WIELD_EXCEPTION(MESSAGE)					\
  {									\
    std::cout << WIELD_C_B_ON;						\
    std::cout << "Exception " << WIELD_C_FG_GREEN << "caught";		\
    std::cout << WIELD_C_FG_DEFAULT << ": " << MESSAGE << endl ;	\
    std::cout << "\t" << WIELD_C_B_ON << WIELD_C_FG_BLUE << __FILE__;	\
    std::cout << WIELD_C_FG_DEFAULT << ":";				\
    std::cout << WIELD_C_FG_BLUE << __LINE__ <<WIELD_C_FG_DEFAULT << endl; \
    std::cout << "\t" << WIELD_C_FG_YELLOW << __func__;		\
    std::cout << WIELD_C_RESET << endl;				\
  }
#define WIELD_NEW_EXCEPTION(MESSAGE)					\
  {									\
    std::cout << WIELD_C_B_ON << "Exception " <<WIELD_C_FG_RED<< "thrown"; \
    std::cout << WIELD_C_FG_DEFAULT << ": " << MESSAGE << endl ;	\
    std::cout << "\t" << WIELD_C_B_ON << WIELD_C_FG_BLUE<<__FILE__;	\
    std::cout << WIELD_C_FG_DEFAULT << ":";				\
    std::cout << WIELD_C_FG_BLUE <<__LINE__ <<WIELD_C_FG_DEFAULT << endl; \
    std::cout << "\t" << WIELD_C_FG_YELLOW << __func__;		\
    std::cout << WIELD_C_RESET<<endl;					\
    stringstream ss; ss << MESSAGE; throw std::runtime_error(ss.str());	\
  }

#define WIELD_TRY try {
#define WIELD_CATCH } catch (exception &e) {WIELD_EXCEPTION("");throw;} catch (int i) {WIELD_EXCEPTION("");throw;}
#define WIELD_CATCH_FINAL } catch (exception &e) {WIELD_EXCEPTION("");} catch (int i) {WIELD_EXCEPTION("");}
#define WIELD_CATCH_MSG(MESSAGE) } catch (exception &e) {WIELD_EXCEPTION(MESSAGE);throw;} catch (int i) {WIELD_EXCEPTION(MESSAGE);throw;}

#endif // WIELD_EXCEPTION_H
