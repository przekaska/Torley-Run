#ifndef _TR_C
#define _TR_C


#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#include "setup_ncurses.c"
#include "player.c"
#include "paths.c"


struct Path *paths[NUMBER_OF_PATHS];    // decided to make paths global, instead of artifically keeping them
                                        // local by passing pointer across the functions
void game_loop(){
    char key = 0;
    struct Player player;
    init_player(&player);    

    for(int iterator = 0; (key = getch()) != 10; iterator++){
        if(iterator == WINDOW_WIDTH + STATE_LENGTH)
            iterator = 0;

        player_move(&player, key);
        
        if(iterator%STATE_LENGTH == 0){
            change_paths(iterator);
        }

        check_if_hit(&player);
        draw_player(&player);

        refresh();
        usleep(33333);
    }
}



int main(){
    init_ncurses();
    
    game_loop();    

    end_ncurses();
}


#endif
