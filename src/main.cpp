#include <QCoreApplication>
#include "QDebug"
#include <stdio.h>
#include <iostream>

#include "level.h"


#define BACKGROUND_WHITE BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED
#define FOREGROUND_WHITE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED

#define PRINT_WARNING DEBUG_COLORED("WARNUNG\t",FOREGROUND_RED | FOREGROUND_GREEN)
#define PRINT_ERROR   DEBUG_COLORED("WARNUNG\t",FOREGROUND_RED)

#define SET_CONSOLE_COLOR(color)\
{\
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);\
SetConsoleTextAttribute(hConsole, color);\
}
//__PRETTY_FUNCTION__
#define DEBUG_STR(message) printf("%s",message);


#define DBG_TXT_INFILE "In File: "
#define DBG_TXT_WHAT "what: "
#define DEBUG_PRINT_NL DEBUG_STR("\n")
#define DEBUG_PRINT_FUNCTION DEBUG_STR(__PRETTY_FUNCTION__)
#define DEBUG_FORMATED(message,color)\
    DEBUG_COLORED(DBG_TXT_INFILE,FOREGROUND_WHITE)\
    DEBUG_COLORED(__PRETTY_FUNCTION__,FOREGROUND_WHITE)\
    DEBUG_COLORED(message"\n",color)



#define DEBUG_COLORED(message,color)\
{\
SET_CONSOLE_COLOR(color)\
DEBUG_STR(message)\
SET_CONSOLE_COLOR(BACKGROUND_WHITE)\
}

#define DEBUG_ERROR(message) PRINT_WARNING DEBUG_PRINT_NL DEBUG_STR(DBG_TXT_WHAT) DEBUG_FORMATED(message,FOREGROUND_RED)
#define DEBUG_WARNING(message) PRINT_ERROR DEBUG_FORMATED(message,FOREGROUND_RED | FOREGROUND_GREEN)


int main(int argc, char *argv[])
{


    /*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole,
      FOREGROUND_RED);
    printf("red text\n");

    SetConsoleTextAttribute(hConsole,
      FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_BLUE);
    printf("yellow on blue\n");

*/

   /* DEBUG_ERROR("testerror");
    DEBUG_WARNING("testwarnung");
    return 0;
    getchar();*/
    unsigned int mapWidth   = 16*20; // Width of the Grid, the hight will be calculated depending of the windowSize
    float displayScale     = 1;
    Vector2u  windowSize(1900*displayScale,1000*displayScale);

    Level game(windowSize,mapWidth);
    game.setup();
    MAIN_END_BLOCK;
    MAIN_BLOCK("while",profiler::colors::Amber100);
    while(game.engineIsActive())
    {
        try {
            game.run();
        }  catch (...) {
            qDebug() << "error occured";
        }

    }
    MAIN_END_BLOCK;
    game.cleanup();
    return 1;
}
