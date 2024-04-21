#ifndef POINT_H
#define POINT_H

typedef enum {FALSE, TRUE} bool;

#define PISTE '#'
#define inSAND '~'
#define OFF_PISTE '.'
#define FINISH '='

typedef struct point {
    int x;
    int y;
    int vx;
    int vy;
} point;


#endif