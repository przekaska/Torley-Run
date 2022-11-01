#ifndef TR_SETUP_NCURSES_C
#define TR_SETUP_NCURSES_C

#include <ncurses.h>

void init_ncurses(){
    initscr();
}

void end_ncurses(){
    getch();
    endwin();
}




#endif
