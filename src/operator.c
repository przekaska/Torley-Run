#ifndef _TR_OPERATOR_C
#define _TR_OPERATOR_C

#include "paths.c"

#define NUMBER_OF_PATHS 16



void change_states(struct Path *paths, int iterator){
    int z = 0;
    int upath_width;
    int lpath_width;
    int endtopy;
    int endboty;

    for(int i = 0; i < NUMBER_OF_PATHS; i++){
        z = rand()%100;
        if(z < 10){
            upath_width = paths[i].topy[iterator - STATE_LENGTH] - paths[i].boty[iterator - STATE_LENGTH];
            lpath_width = paths[i + 1].topy[iterator - STATE_LENGTH] - paths[i + 1].boty[iterator - STATE_LENGTH]; 
            
            endtopy = paths[i + 1].minboty + rand(paths[i].maxtopy - paths[i + 1].minboty);
            endboty = endtopy - rand(endtopy - paths[i + 1].minboty);

            merge_paths(&paths[i], &paths[i + 1], rand()%upath_width, rand()%lpath_width, endboty, endboty, iterator);
        }
    }
}




#endif
