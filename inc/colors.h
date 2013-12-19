#ifndef THE_WONDERFUL_WORLD_OF_COLOR
#define THE_WONDERFUL_WORLD_OF_COLOR


#define RESET               "\e[0m"

#define B_ON                "\e[1m"
#define I_ON                "\e[3m"
#define U_ON                "\e[4m"
#define INVERSE_ON          "\e[7m"
#define STRIKETHROUGH_ON    "\e[9m"
#define B_OFF               "\e[21m"
#define I_OFF               "\e[23m"
#define U_OFF               "\e[24m"
#define INVERSE_OFF         "\e[27m"
#define STRIKETHROUGH_OFF   "\e[29m"

#define FG_BLACK            "\e[30m"
#define FG_RED              "\e[31m"
#define FG_GREEN            "\e[32m"
#define FG_YELLOW           "\e[33m"
#define FG_BLUE             "\e[34m"
#define FG_MAGENTA          "\e[35m"
#define FG_CYAN             "\e[36m"
#define FG_WHITE            "\e[37m"
#define FG_DEFAULT          "\e[39m"

#define BG_BLACK            "\e[40m"
#define BG_RED              "\e[41m"
#define BG_GREEN            "\e[42m"
#define BG_YELLOW           "\e[43m"
#define BG_BLUE             "\e[44m"
#define BG_MAGENTA          "\e[45m"
#define BG_CYAN             "\e[46m"
#define BG_WHITE            "\e[47m"
#define BG_DEFAULT          "\e[49m"

#define PASS B_ON << "[" << B_ON << FG_GREEN << " PASS " << FG_DEFAULT << "]\t" << RESET 
#define FAIL B_ON << "[" << B_ON << FG_RED   << " FAIL " << FG_DEFAULT << "]\t" << RESET 

#define PASSf B_ON << "[" << B_ON << FG_GREEN << " PASS " << FG_DEFAULT << "]\t" << RESET 
#define FAILf B_ON << "[" << B_ON << FG_RED   << " FAIL " << FG_DEFAULT << "]\t" << RESET 

#define RED(STR) cout << B_ON << FG_RED << STR << RESET << endl
#define BLUE(STR) cout << B_ON << FG_BLUE << STR << RESET << endl
#define GREEN(STR) cout << B_ON << FG_GREEN << STR << RESET << endl
#define YELLOW(STR) cout << B_ON << FG_YELLOW << STR << RESET << endl


#endif //THE_WONDERFUL_WORLD_OF_COLOR
