#ifndef _TR_C
#define _TR_C


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

#include "setup_ncurses.c"
#include "player.c"
#include "paths.c"

    
void game_loop(){
    char key = 0;
    srand(time(NULL));

    struct Player player; 
    struct Path paths[NUMBER_OF_PATHS]; 
    char background[WINDOW_HEIGHT][WINDOW_WIDTH];        

    init_player(&player);    
    init_paths(paths);
    init_background(background);
    change_paths(paths);
    u_int8_t change_iterator = 0;
    u_int8_t background_iterator = 0;

    while((key = getch()) != 10){
        if(change_iterator == NUMBER_OF_Y_VALUES){
            change_paths(paths);
            change_iterator = 0;
        }
        if(background_iterator == WINDOW_WIDTH + 1)
            background_iterator = 1;

        draw_paths(paths, background, change_iterator, background_iterator);

        player_move(&player, key);
        check_if_hit(&player);
        draw_player(&player);

        refresh();
        usleep(33333);

        change_iterator++;
        background_iterator++;
    }
    clear();
}



int main(){
    init_ncurses();

    game_loop();     

    end_ncurses();
}


#endif
