#ifndef WIELD_UTILS_COLOR_H
#define WIELD_UTILS_COLOR_H

#ifndef WIELD_NO_COLOR_GRAPHICS
#define WIELD_COLOR_RESET               "\033[0m"
#define WIELD_COLOR_B_ON                "\033[1m"
#define WIELD_COLOR_FG_RED              "\033[31m"
#define WIELD_COLOR_FG_GREEN            "\033[32m"
#define WIELD_COLOR_FG_YELLOW           "\033[33m"
#define WIELD_COLOR_FG_BLUE             "\033[34m"
#define WIELD_COLOR_FG_DEFAULT          "\033[39m"
#else
#define WIELD_COLOR_RESET               ""
#define WIELD_COLOR_B_ON                ""
#define WIELD_COLOR_FG_RED              ""
#define WIELD_COLOR_FG_GREEN            ""
#define WIELD_COLOR_FG_YELLOW           ""
#define WIELD_COLOR_FG_BLUE             ""
#define WIELD_COLOR_FG_DEFAULT          ""
#endif

#endif//WIELD_UTILS_COLOR_H
