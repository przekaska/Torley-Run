#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#include "setup_ncurses.c"
#include "player.c"
#include "paths.c"


void game_loop(){
    char key = 0;
    struct Player player;
    init_player(&player);

    while( (key = getch()) != 10){
        player_move(&player, key);
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


