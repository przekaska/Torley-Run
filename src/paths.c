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

    int is_upper_done;
    int is_lower_done;
};


void continuePath(struct Path *path, int i){
    path->topy[i] = path->boty[i - 1] + rand()%(path->maxtopy - path->boty[i - 1]);

    if(path->topy[i - 1] < path->topy[i])
        path->boty[i] = path->topy[i - 1] - rand()%(path->topy[i - 1] - path->maxboty);
    else
        path->boty[i] = path->topy[i] - rand()%(path->topy[i] - path->maxboty); 
}



#endif