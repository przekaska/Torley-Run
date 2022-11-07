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


void merge_paths(struct Path *upper_p, struct Path *lower_p, int uv, int lv, int endtopy, int endboty, int iterator){
    for(int i = iterator - STATE_LENGTH; i < iterator; i++){
        upper_p->topy[i] = upper_p->topy[i - 1];
        lower_p->boty[i] = lower_p->boty[i - 1];

        if(upper_p->topy[i] > endtopy)
            upper_p->topy[i] -= uv; 
        else if(upper_p->topy[i] < endtopy)     
            upper_p->topy[i] = endtopy;

        if(lower_p->boty[i] < endboty)
            lower_p->boty[i] += lv; 
        else if (lower_p->boty[i] > endboty)
            lower_p->boty[i] = endboty;
        
        upper_p->boty[i] = upper_p->topy[i] - rand()%(upper_p->topy[i] - endboty);
        lower_p->topy[i] = lower_p->boty[i] + rand()%(endtopy - lower_p->boty[i]);
    }
}



#endif
