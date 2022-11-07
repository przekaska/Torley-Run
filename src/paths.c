#ifndef TR_PATHS_C
#define TR_PATHS_C

#include <stdbool.h>
#include <string.h>

#include "player.c"


#define STATE_LENGTH 24     // how much iterations takes to change a state


struct Path{
    /*  Length of array of y-values is equal to WINDOW_WIDTH (part of the path
        that is displayed) + STATE_LENGTH (this part is modified by state functions)*/
    int topy[WINDOW_WIDTH + STATE_LENGTH];      // y-values at the top of the path
    int boty[WINDOW_WIDTH + STATE_LENGTH];      // y-values at the bottom of the path

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
    untill its topy reaches 'endtopy'. Lower path is going up by 'lvelocity' untill its boty reaches 'endboty'*/
void merge_paths(struct Path *upper_p, struct Path *lower_p, int uvelocity, 
                int lvelocity, int endtopy, int endboty, int iterator){
    for(int i = iterator - STATE_LENGTH; i < iterator; i++){ // change the end of the path that won't be displayed
        upper_p->topy[i] = upper_p->topy[i - 1];
        lower_p->boty[i] = lower_p->boty[i - 1];

        if(upper_p->topy[i] > endtopy){     
            upper_p->topy[i] -= uvelocity; 
            if(upper_p->topy[i] < endtopy)  // topy[i-1] - uvelocity may be lower than endtopy, and even lower    
                upper_p->topy[i] = endtopy; // than endboty, so topy[i] = endtopy just in case
        }

        if(lower_p->boty[i] < endboty){
            lower_p->boty[i] += lvelocity; 
            if (lower_p->boty[i] > endboty) // boty[i-1] + lvelocity may be greater than endboty, and even greater    
                lower_p->boty[i] = endboty; // than endtopy, so boty[i] = endboty just in case
        }

        upper_p->boty[i] = upper_p->topy[i] - rand()%(upper_p->topy[i] - endboty);  // upper_p->topy[i] >= boty[i] >= endboty
        lower_p->topy[i] = lower_p->boty[i] + rand()%(endtopy - lower_p->boty[i]);  // lower_p->boty[i] <= lower_p->topy[i] <= endtopy 
    }
}


/*  Make a fork of the path. The parent path becomes the upper path and the child path becomes the lower path.
    Upper path is going up by 'uvelocity' per iteration untill its boty reaches the 'up_endboty' (upper path end boty)
    Lower path is going down by 'lvelocity' per iteration untill its topy reaches the 'lp_endtopy' (lower path end topy)*/
void fork_paths(struct Path *upper_p, int uvelocity, int lvelocity, int iterator,
                 int up_endtopy, int up_endboty, int lp_endtopy, int lp_endboty){

    static struct Path lower_p; // at the beggining lower and upper path are in the same place
    memcpy(lower_p.topy, upper_p->topy, WINDOW_WIDTH + STATE_LENGTH);   // copy values of the topy and boty arrays instead of pointers to them
    memcpy(lower_p.boty, upper_p->boty, WINDOW_WIDTH + STATE_LENGTH);   // because lower_path's y-coords are going to be changed independently

    for(int i = iterator - STATE_LENGTH; i < iterator; i++){ // change the end of the path that won't be displayed
        upper_p->boty[i] = upper_p->boty[i - 1];
        lower_p.topy[i] = lower_p.topy[i - 1];

        if(upper_p->boty[i] < up_endboty){
            upper_p->boty[i] += uvelocity;
            if(upper_p->boty[i] > up_endboty)   // boty[i-1] + uvelocity may be greater than endboty, and even greater    
                upper_p->boty[i] = up_endboty;  // than endtopy, so boty[i] = endboty just in case
        }

        if(lower_p.topy[i] > lp_endtopy){
            lower_p.topy[i] -= lvelocity;
            if(lower_p.topy[i] < lp_endtopy)    // topy[i-1] - lvelocity may be lower than endtopy, and even lower    
                lower_p.topy[i] = lp_endtopy;   // than boty, so topy[i] = endtopy just in case
        }

        upper_p->topy[i] = upper_p->boty[i] + rand()%(up_endtopy - upper_p->boty[i]); // upper->boty <= upper->topy <= endtopy
        lower_p.boty[i] = lower_p.topy[i] - rand()%(lower_p.topy[i] - lp_endboty);    // lower->topy >= lower->boty >= endboty
    }    

    // new limit values for each path
    upper_p->maxtopy = up_endtopy;
    upper_p->minboty = up_endboty;

    lower_p.maxtopy = lp_endtopy;
    lower_p.minboty = lp_endtopy;
}



#endif
