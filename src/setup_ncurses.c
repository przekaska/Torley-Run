#ifndef _TR_SETUP_NCURSES_C
#define _TR_SETUP_NCURSES_C

#include <ncurses.h>

void init_ncurses(){
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
}

void end_ncurses(){
    nodelay(stdscr, FALSE);
    getch();
    endwin();
}




#endif
