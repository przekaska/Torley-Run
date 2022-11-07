#ifndef TR_PATHS_C
#define TR_PATHS_C

#include <stdbool.h>

#include "player.c"


#define STATE_LENGTH 24


struct Path{
    int topy[WINDOW_HEIGHT + STATE_LENGTH];
    int boty[WINDOW_HEIGHT + STATE_LENGTH];

    int maxtopy;
    int maxboty;
};


void continue_path(struct Path *p, int iterator){
    for(int i = iterator - STATE_LENGTH; i < iterator; i++){
        p->topy[i] = p->boty[i - 1] + rand()%(p->maxtopy - p->boty[i - 1]);

        if(p->topy[i - 1] < p->topy[i])
            p->boty[i] = p->topy[i - 1] - rand()%(p->maxtopy - p->boty[i - 1]);
        else
            p->boty[i] = p->topy[i] - rand()%(p->topy[i] - p->maxboty); 
    }
}




#endif
