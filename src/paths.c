#ifndef TR_PATHS_C
#define TR_PATHS_C

#include <stdbool.h>
#include <string.h>

#include "player.c"


#define STATE_LENGTH 24


struct Path{
    int topy[WINDOW_WIDTH + STATE_LENGTH];
    int boty[WINDOW_WIDTH + STATE_LENGTH];

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


void merge_paths(struct Path *upper_p, struct Path *lower_p, int uvelocity, int lvelocity, int endtopy, int endboty, int iterator){
    for(int i = iterator - STATE_LENGTH; i < iterator; i++){
        upper_p->topy[i] = upper_p->topy[i - 1];
        lower_p->boty[i] = lower_p->boty[i - 1];

        if(upper_p->topy[i] > endtopy){
            upper_p->topy[i] -= uvelocity; 
            if(upper_p->topy[i] < endtopy)     
                upper_p->topy[i] = endtopy;
        }

        if(lower_p->boty[i] < endboty){
            lower_p->boty[i] += lvelocity; 
            if (lower_p->boty[i] > endboty)
                lower_p->boty[i] = endboty;
        }

        upper_p->boty[i] = upper_p->topy[i] - rand()%(upper_p->topy[i] - endboty);
        lower_p->topy[i] = lower_p->boty[i] + rand()%(endtopy - lower_p->boty[i]);
    }
}


void fork_paths(struct Path *upper_p, int uvelocity, int lvelocity, int iterator,
                 int end_up_topy, int end_up_boty, int end_lp_topy, int end_lp_boty){

    static struct Path lower_p;
    memcpy(lower_p.topy, upper_p->topy, WINDOW_WIDTH + STATE_LENGTH);    
    memcpy(lower_p.boty, upper_p->boty, WINDOW_WIDTH + STATE_LENGTH);

    for(int i = iterator - STATE_LENGTH; i < iterator; i++){
        upper_p->boty[i] = upper_p->boty[i - 1];
        lower_p.topy[i] = lower_p.topy[i - 1];

        if(upper_p->boty[i] < end_up_boty){
            upper_p->boty[i] += uvelocity;
            if(upper_p->boty[i] >= end_up_boty)
                upper_p->boty[i] = end_up_boty;
        }

        if(lower_p.topy[i] > end_lp_topy){
            lower_p.topy[i] -= lvelocity;
            if(lower_p.topy[i] <= end_lp_topy)
                lower_p.topy[i] = end_lp_topy;
        }

        upper_p->topy[i] = upper_p->boty[i] + rand()%(end_up_topy - upper_p->boty[i]);
        lower_p.boty[i] = lower_p.topy[i] - rand()%(lower_p.topy[i] - end_lp_boty);
    }    

    upper_p->maxtopy = end_up_topy;
    upper_p->maxboty = end_up_boty;

    lower_p.maxtopy = end_lp_topy;
    lower_p.maxboty = end_lp_topy;
}



#endif
