#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "track.h"
#include "list.h"
#include "abr.h"
#include "listeAdjacence.h"


Ladj* initLadj(Track t);

int loadLadj(Ladj *l, Track T, point p);

int calculDistance(Ladj* L);

Stack* findRoute(Ladj* L, point p);

point dijkstra(Ladj* L, Track t, point a, float x);

void freeLadj(Ladj* L, Track T);

#endif