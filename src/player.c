#ifndef TR_PLAYER_C
#define TR_PLAYER_C


#define MV_KEY_UP 3
#define MV_KEY_DOWN 2

#define DEFAULT_PLAYER_X 10
#define DEFAULT_PLAYER_Y 10
#define DEFAULT_PLAYER_SKIN 'O'

#define BACKGROUND_ELEMENT ' '


 struct Player{
    int y;
    int x;
    int previous_y;

    int skin;
 };


 void player_move(struct Player *player, int key){
    switch(key){
        case MV_KEY_UP:
            player->y++;
            break;

        case MV_KEY_DOWN:
            player->y--;
            break;
    }
 }


 void draw_player(struct Player *player){
    mvaddch(player->previous_y, DEFAULT_PLAYER_X, BACKGROUND_ELEMENT);
    mvaddch(player->y, DEFAULT_PLAYER_X, player->skin);


 }
#endif
