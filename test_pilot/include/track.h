#ifndef TRACK_H
#define TRACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "point.h"


typedef struct track_t {
    int height;
    int width;
    int gasLevel;
    char **track;
} *Track;

Track treatOfTrack(FILE *input, FILE *output);


#endif