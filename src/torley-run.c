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

    for(u_int8_t iterator = 0; (key = getch()) != 10; iterator++){
        if( iterator == NUMBER_OF_Y_VALUES){
            change_paths(paths);
            iterator = 0;
        }
        draw_paths(paths, background, iterator);

        player_move(&player, key);

        check_if_hit(&player);
        draw_player(&player);

        refresh();
        usleep(3333);
    }
    clear();
}



int main(){
    init_ncurses();

    game_loop();     

    end_ncurses();
}


#endif
