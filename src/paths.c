#ifndef TR_PATHS_C
#define TR_PATHS_C

#include <stdbool.h>

#include "player.c"

struct Path{
    int topy[WINDOW_WIDTH];
    int boty[WINDOW_WIDTH];

    int maxtopy;
    int maxboty;

    void (*behaviour)(struct Path*, int);
};


struct PathMerger{
    struct Path *upperPath;
    struct Path *lowerPath;
    
    int upperVelocity;
    int lowerVelocity;

    int endtopy;
    int endboty;

    bool is_upper_done;
    bool is_lower_done;
};


void continuePath(struct Path *path, int i){
    path->topy[i] = path->boty[i - 1] + rand()%(path->maxtopy - path->boty[i - 1]);

    if(path->topy[i - 1] < path->topy[i])
        path->boty[i] = path->topy[i - 1] - rand()%(path->topy[i - 1] - path->maxboty);
    else
        path->boty[i] = path->topy[i] - rand()%(path->topy[i] - path->maxboty); 
}


void mergePaths(struct PathMerger *pmerger, int i){
    pmerger->upperPath->topy[i] = pmerger->upperPath->topy[i - 1];
    pmerger->lowerPath->boty[i] = pmerger->lowerPath->boty[i - 1];

    if(!pmerger->is_upper_done){
        pmerger->upperPath->topy[i] -= pmerger->upperVelocity; 
        
        if(pmerger->upperPath->topy[i] <= pmerger->endtopy){
            pmerger->is_upper_done = true;
            pmerger->upperPath->topy[i] = pmerger->endtopy;
        }
    }

    if(!pmerger->is_lower_done){
        pmerger->lowerPath->boty[i] += pmerger->lowerVelocity; 
        
        if(pmerger->lowerPath->boty[i] >= pmerger->endboty){
            pmerger->is_lower_done = true;
            pmerger->upperPath->boty[i] = pmerger->endboty;
        }
    }

    pmerger->upperPath->boty[i] = pmerger->upperPath->topy[i] - rand()%(pmerger->upperPath->topy[i] - pmerger->upperPath->maxboty);
    pmerger->lowerPath->topy[i] = pmerger->lowerPath->boty[i] + rand()%(pmerger->lowerPath->maxtopy - pmerger->lowerPath->boty[i]);
}



#endif