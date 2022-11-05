#ifndef _TR_PLAYER_C
#define _TR_PLAYER_C


#define MV_KEY_UP 3
#define MV_KEY_DOWN 2

#define DEFAULT_PLAYER_X 10
#define DEFAULT_PLAYER_Y 10
#define DEFAULT_PLAYER_SKIN 'O'

#define BACKGROUND_ELEMENT ' '

#define WINDOW_HEIGHT 20
#define WINDOW_WIDTH 70

 struct Player{
    int y;
    int x;
    int previous_y;

    int skin;
    bool did_hit;
};


void init_player(struct Player *player){
    player->y = DEFAULT_PLAYER_Y;
    player->x = DEFAULT_PLAYER_X;
    player->previous_y = 0;
    
    player->skin = DEFAULT_PLAYER_SKIN;
};


void player_move(struct Player *player, int key){
    player->previous_y = player->y;
    switch(key){
        case MV_KEY_UP:
            player->y++;
            break;

        case MV_KEY_DOWN:
            player->y--;
            break;
    }
 }


void check_if_hit(struct Player *player){
    if((A_CHARTEXT & mvwinch(stdscr, WINDOW_HEIGHT - player->y, DEFAULT_PLAYER_X)) == 'T')
        player->did_hit = true;
}



 void draw_player(struct Player *player){
    mvaddch(WINDOW_HEIGHT - player->previous_y, DEFAULT_PLAYER_X, BACKGROUND_ELEMENT);
    mvaddch(WINDOW_HEIGHT - player->y, DEFAULT_PLAYER_X, player->skin);
}

#endif
