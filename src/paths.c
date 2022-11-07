#ifndef TR_PATHS_C
#define TR_PATHS_C

#include <stdbool.h>
#include <string.h>

#include "player.c"


#define STATE_LENGTH 24     // how much iteration takes to change a state


struct Path{
    /*  Length of array of y-values is equal to WINDOW_WIDTH (part of the path
        that is displayed) + STATE_LENGTH (this part is modified by state functions)*/
    int topy[WINDOW_WIDTH + STATE_LENGTH];      // y-values at the top of the path
    int boty[WINDOW_WIDTH + STATE_LENGTH];      // y-values at the bottom

    int maxtopy;    // topy cannot exceed this value
    int minboty;    // boty cannot be lower than this value
};

/* This function performes state: CONTINUE */
void continue_path(struct Path *p, int iterator){
    for(int i = iterator - STATE_LENGTH; i < iterator; i++){    // change the end of path that won't be displayed
    
        p->topy[i] = p->boty[i - 1] + rand()%(p->maxtopy - p->boty[i - 1]); // add rand()%(p->maxtopy - p->boty[i - 1] so the topy[i] >= boty[i-1] and 
                                                                            // topy[i] <= maxtopy, thanks to that there is at least one block for player
                                                                            // to pass through
        if(p->topy[i - 1] < p->topy[i]) // boty[i] needs to be created relative to smaller one to make sure that at least one block is to pass through
            p->boty[i] = p->topy[i - 1] - rand()%(p->topy[i - 1] - p->minboty);
        else
            p->boty[i] = p->topy[i] - rand()%(p->topy[i] - p->minboty); 
    }
}

/*  Merge two paths by bringing them together. Upper path is going down by 'uvelocity' blocks per iteration
    untill it reaches 'endtopy'. Lower path is going up by 'lvelocity' untill it reaches 'endboty'*/
void merge_paths(struct Path *upper_p, struct Path *lower_p, int uvelocity, 
                int lvelocity, int endtopy, int endboty, int iterator){
    for(int i = iterator - STATE_LENGTH; i < iterator; i++){ // change the end of path that won't be displayed
        upper_p->topy[i] = upper_p->topy[i - 1];
        lower_p->boty[i] = lower_p->boty[i - 1];

        if(upper_p->topy[i] > endtopy){     
            upper_p->topy[i] -= uvelocity; 
            if(upper_p->topy[i] < endtopy)  // topy[i-1] - uvelocity may be lower than endtopy, and even lower    
                upper_p->topy[i] = endtopy; // than endboty, so change topy[i] to endtopy just in case
        }

        if(lower_p->boty[i] < endboty){
            lower_p->boty[i] += lvelocity; 
            if (lower_p->boty[i] > endboty) // the same as comment above
                lower_p->boty[i] = endboty;
        }

        upper_p->boty[i] = upper_p->topy[i] - rand()%(upper_p->topy[i] - endboty);  // upper_p->topy[i] >= boty[i] >= endboty
        lower_p->topy[i] = lower_p->boty[i] + rand()%(endtopy - lower_p->boty[i]);  // lower_p->boty[i] <= lower_p->topy[i] <= endtopy 
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
    upper_p->minboty = end_up_boty;

    lower_p.maxtopy = end_lp_topy;
    lower_p.minboty = end_lp_topy;
}



#endif
