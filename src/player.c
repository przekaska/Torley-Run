#ifndef TR_PLAYER_C
#define TR_PLAYER_C


#define MV_KEY_UP 3
#define MV_KEY_DOWN 2


 struct Player{
    int y;
    int x;
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


#endif
