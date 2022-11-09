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
    int change_buffer = 0;

    for(u_int8_t iterator = 0; (key = getch()) != 10; iterator++){
        iterator &= ~(1U << 7);     //  set the most significant bit to 0, so iterator can be treated as 7-bit value.
                                    //  Thanks to that iterator can assigned values between 0 and 127, so exactly the
                                    //  same as indexes of topy and boty of path (Look at Path structure in paths.c)      

        player_move(&player, key);
        

        change_paths(iterator);


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
