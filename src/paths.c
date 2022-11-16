#ifndef TR_PATHS_C
#define TR_PATHS_C

#include <stdlib.h>

#include <stdbool.h>
#include <string.h>

#include "player.c"


#define STATE_LENGTH 30     // how much iterations takes to change a state

#define NUMBER_OF_PATHS 10
#define NUMBER_OF_Y_VALUES 32

#define BACKGROUND_BLOCK 'T';

struct Path{
    /*  Length of array of y-values is equal to WINDOW_WIDTH (part of the path
        that is displayed) + STATE_LENGTH (this part is modified by state functions)*/
    int8_t topy[NUMBER_OF_Y_VALUES];      // y-values at the top of the path
    int8_t boty[NUMBER_OF_Y_VALUES];      // y-values at the bottom of the path

    int8_t maxtopy;    // topy cannot exceed this value
    int8_t minboty;    // boty cannot be lower than this value
};


void init_paths(struct Path paths[NUMBER_OF_PATHS]){
    for(int i = 0; i < NUMBER_OF_PATHS; i++)
        paths[i].maxtopy = -1;

    paths[0].topy[NUMBER_OF_Y_VALUES - 1] = 15;

    paths[0].boty[NUMBER_OF_Y_VALUES - 1] = 10;

    paths[0].maxtopy = WINDOW_HEIGHT - 1;
    paths[0].minboty = 0;
}


uint8_t add_path(struct Path paths[NUMBER_OF_PATHS], struct Path new_path){
    if(paths[NUMBER_OF_PATHS - 1].maxtopy == -1){  // replace only disabled path, which is at the end of the paths array        
        uint8_t i = NUMBER_OF_PATHS - 1;
        for(;(new_path.maxtopy > paths[i - 1].maxtopy) && (i > 0); i--)   // create place for the new path   
            paths[i] = paths[i - 1];
        paths[i] = new_path;
        return i;   // return index at which path has been added
    }
    else return -1; // if there is no disabled path, array is full
}

/* Function moves given path to the end of the paths array, and then disables the path
   by changing it maxtopy to -1. Disabling the path instead of deleting it provides possibility
   of restoring the path really easily just by changing its maxtopy*/
void delete_path(struct Path *paths[NUMBER_OF_PATHS], uint8_t index){
    struct Path *path_buffer = paths[index];

    for(uint8_t i = index; i < NUMBER_OF_PATHS - 1; i++)    // disabled path needs to be at the end, so move 
        paths[i] = paths[i + 1];                        // every other path one index to the front

    paths[NUMBER_OF_PATHS] = path_buffer;  
    paths[NUMBER_OF_PATHS]->maxtopy = -1;   // path which maxtopy = -1 is supposed to be ignored
}


void continue_path(struct Path *p, uint8_t startpoint){
    if(startpoint == 1) {
        p->topy[0] = p->topy[NUMBER_OF_Y_VALUES - 1];
        p->boty[0] = p->boty[NUMBER_OF_Y_VALUES - 1];
    }

    for(uint8_t i = startpoint; i < NUMBER_OF_Y_VALUES; i++){ 
        p->topy[i] = p->boty[i - 1] + rand()%(p->maxtopy - p->boty[i - 1]);
                                   
        if(p->topy[i - 1] < p->topy[i])  
            p->boty[i] = p->topy[i - 1] - rand()%(p->topy[i - 1] - p->minboty);
        else
            p->boty[i] = p->topy[i] - rand()%(p->topy[i] - p->minboty);
    }
}



void fork_path(struct Path paths[NUMBER_OF_PATHS], struct Path *upper_p){
    if(upper_p->topy[NUMBER_OF_Y_VALUES - 1] - upper_p->boty[NUMBER_OF_Y_VALUES - 1] >= 2){
        upper_p->topy[0] = upper_p->topy[NUMBER_OF_Y_VALUES - 1];
        upper_p->boty[0] = upper_p->boty[NUMBER_OF_Y_VALUES - 1];

        u_int8_t new_border = upper_p->boty[0] + 1 + rand()%(upper_p->topy[0] - upper_p->boty[0] - 1);
        
        struct Path lower_p;
        lower_p.maxtopy = new_border;
        lower_p.minboty = upper_p->minboty;
        lower_p.topy[0] = upper_p->topy[NUMBER_OF_Y_VALUES - 1];
        lower_p.boty[0] = upper_p->boty[NUMBER_OF_Y_VALUES - 1];
        lower_p.topy[1] = new_border - 1;
        lower_p.boty[1] = lower_p.topy[1] - rand()%(lower_p.topy[1] - lower_p.minboty);

        upper_p->boty[1] = new_border + 1;
        upper_p->topy[1] = upper_p->boty[1] + rand()%(upper_p->maxtopy - upper_p->boty[1]);
        upper_p->minboty = new_border;

        continue_path(upper_p, 2);
        continue_path(&lower_p, 2);
        
        add_path(paths, lower_p);        
    }
    else continue_path(upper_p, 1);    
}


void change_paths(struct Path paths[NUMBER_OF_PATHS]){
    uint8_t r;
    for(uint8_t i = 0; (i < NUMBER_OF_PATHS && paths[i].maxtopy != -1); i++){
        r = rand()%100;
        if(r < -1){
            if(paths[i + 1].maxtopy != -1){       
                i++;
            }   
            else
                continue_path(&paths[i], 1);
        }
        else if(r > 49){
            fork_path(paths, &paths[i]);
            i++;
        }      
        else
            continue_path(&paths[i], 1);
    }            
}


void init_background(char background[WINDOW_HEIGHT][WINDOW_WIDTH]){
    for(int y = 0; y < WINDOW_HEIGHT; y++)
        for(int x = 0; x < WINDOW_WIDTH; x++)
            background[y][x] = ' ';
}


void draw_paths(struct Path paths[NUMBER_OF_PATHS], char background[WINDOW_HEIGHT][WINDOW_WIDTH],
                u_int8_t change_iterator, u_int8_t background_iterator){
    for(int y = WINDOW_HEIGHT - 1; y >= 0; y--)
        background[y][(background_iterator - 1)%WINDOW_WIDTH] = 'T';
    
    for(int8_t i = 0; paths[i].maxtopy != -1 && i < NUMBER_OF_PATHS; i++)
        for(int8_t y = paths[i].topy[change_iterator]; y >= paths[i].boty[change_iterator]; y--)
            background[y][(background_iterator - 1)%WINDOW_WIDTH] = ' ';

    for(int y = WINDOW_HEIGHT - 1; y >= 0; y--){
        for(int x = 0; x < WINDOW_WIDTH; x++)
            mvaddch(WINDOW_HEIGHT - y, x + 1, background[y][(background_iterator + x)%WINDOW_WIDTH]);
        mvprintw(WINDOW_HEIGHT - y, WINDOW_WIDTH + 1, " %i", y);
    }
}


#endif
