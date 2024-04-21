#include "graph.h"

Ladj *initLadj(Track t) {

    point p;
    Ladj *L = malloc(sizeof(Ladj));

    L->nbNode = 0;
    L->nbArc = 0;
    L->width = t->width;
    L->height = t->height;

    for (p.x = 0; p.x < t->height; p.x++) {
        for (p.y = 0; p.y < t->width; p.y++) {

            char trackValue = t->track[p.x][p.y];
            if (trackValue >= '1' && trackValue <= '3') {
                L->start[trackValue - '1'].x = p.x;
                L->start[trackValue - '1'].y = p.y;
            }
        }
    }// for this loop we serach for the start point of the track by checking the value of the track

    memset(L->start, 0, sizeof(L->start));

    L->node = (Lnode *****) malloc(t->height * sizeof(Lnode ****));
    for (p.x = 0; p.x < t->height; p.x++) {
        L->node[p.x] = (Lnode ****) malloc(t->width * sizeof(Lnode ***));
        for (p.y = 0; p.y < t->width; p.y++) {
            L->node[p.x][p.y] = (Lnode ***) malloc(11 * sizeof(Lnode **));
            for (p.vx = 0; p.vx < 11; p.vx++) {
                L->node[p.x][p.y][p.vx] = (Lnode **) calloc(11, sizeof(Lnode *));
                for (p.vy = 0; p.vy < 11; p.vy++) {
                    L->node[p.x][p.y][p.vx][p.vy] = createLnode();
                }
            }
        }
    }// here we only allocate memory for the node of the graph and for the number 11 its only the possibilities of the speed of the car
    return L;
}

void freeLadj(Ladj *L, Track t) {
    point p;
    for (p.x = 0; p.x < t->height; p.x++) {
        for (p.y = 0; p.y < t->width; p.y++) {
            for (p.vx = 0; p.vx < 11; p.vx++) {
                for (p.vy = 0; p.vy < 11; p.vy++) {
                    if(L->node[p.x][p.y][p.vx][p.vy]) {
                        freeCells(L->node[p.x][p.y][p.vx][p.vy]->dijNext);
                        freeCells(L->node[p.x][p.y][p.vx][p.vy]->dijPrev);
                        freeCells(L->node[p.x][p.y][p.vx][p.vy]->next);
                        freeCells(L->node[p.x][p.y][p.vx][p.vy]->prev);

                        free(L->node[p.x][p.y][p.vx][p.vy]);
                    }
                }
                if(L->node[p.x][p.y][p.vx]) {
                    free(L->node[p.x][p.y][p.vx]);
                }
            }
            if(L->node[p.x][p.y]) {
                free(L->node[p.x][p.y]);
            }
        }
        if(L->node[p.x]) {
            free(L->node[p.x]);
        }
    }
    if(L->node) {
        free(L->node);
    }
}


int loadLadj(Ladj *L, Track T, point p) {

    int normSpeed2, ax, ay, fuel;
    int f = 0;

    point t, h;
    Queue *Q = createQueue();
    enqueue(p, Q);

    while (!isEmpty(Q)) {

        t = dequeue(Q);

        *tag(L, t) = 2;
        L->nbNode++;

        for (ax = -2; ax <= 1; ax++) {
            for (ay = -1; ay <= 2; ay++) {

                h.vx = t.vx + ax;
                h.vy = t.vy + ay;
                h.x = t.x + h.vx;
                h.y = t.y + h.vy;

                normSpeed2 = h.vx * h.vx + h.vy * h.vy;
                fuel = ax * ax + ay * ay + (int) (sqrt(normSpeed2) * 1.5);
                fuel += testPt(T, t, '~');

                if (pointInTrack(h, L) && normSpeed2 <= 25 && reachable2(T, t, h) &&
                    (!testPt(T, t, '~') || normSpeed2 <= 1)) {

                    if ((testPt(T, h, '#') || testPt(T, h, '~')) && *tag(L, h) != 2) {

                        if (*tag(L, h) == 0) {
                            enqueue(h, Q);
                            *tag(L, h) = 1;
                        }
                        newArc(h, t, fuel, ax, ay, L);

                    } else if (testPt(T, h, '=')) {
                        newArc(h, t, fuel, ax, ay, L);
                        L->finish[f] = h;
                        f++;
                    }
                } else {

                    h = t;
                    h.vx = 0;
                    h.vy = 0;
                    if (*tag(L, h) == 0) {
                        enqueue(h, Q);
                        *tag(L, h) = 1;
                    }
                    newArc(h, t, fuel, ax, ay, L);
                }
            }
        }
    }

    L->nbFinish = f;
    if (f == 0) {
        printf("Error: finish not reached!\n");
        return -1;
    } else {
        return 0;
    }
}

int calculDistance(Ladj *L) {

    Queue *Q = createQueue();
    Cell *C;
    point p, q;
    int i;
    int d = 0;

    for (i = 0; i < L->nbFinish; i++) {
        enqueue(L->finish[i], Q);
        *distance(L, L->finish[i]) = 0;
    }

    while (!isEmpty(Q)) {
        p = dequeue(Q);
        d = *distance(L, p);
        C = *prev(L, p);
        while (C != NULL) {
            q = C->head;
            if (*distance(L, q) == -1) {
                *distance(L, q) = d + 1;
                enqueue(q, Q);
            }
            C = C->next;
        }
    }
    Free(Q); // Free the memory allocated for the queue after it's no longer needed
    return 0;
}


Stack *findRoute(Ladj *L, point p) {

    Stack *S = createStack();
    Cell *C;

    while (*totFuel(L, p) != 0) {
        pushStack(p, S);
        C = *dijPrev(L, p);
        p = C->head;
    }

    pushStack(p, S);
    return S;
}

point dijkstra(Ladj *L, Track t, point a, float x) {
    int w;
    int *TFa, *TFb;
    int *TWa, *TWb;
    point b;
    Cell *C;
    nodeABR* A = NULL;

    A = insert(A, a, 0);

    *totFuel(L, a) = 0;
    *totWeight(L, a) = 0;

    while (!testPt(t, a, '=')) {

        do {
            A = extractMin(A,&a);
        } while(*tag(L, a) == 4);



        C = *next(L, a);
        TFa = totFuel(L, a);
        TWa = totWeight(L, a);

        while (C != NULL) {
            b = C->head;

            if (*tag(L, b) != 4) {
                TFb = totFuel(L, b);
                TWb = totWeight(L, b);

                w = 1000 * C->fuel + (int) (1000 * x);

                if ((*totWeight(L, a) + w) < *totWeight(L, b)) {
                    *TFb = *TFa + C->fuel;
                    *TWb = *TWa + w;

                    if (*tag(L, b) < 3) {

                        *tag(L, b) = 3;
                        A = insert(A, b, *TWb);
                        newArcDij(b, a, w, C->ax, C->ay, L);

                    } else if (*tag(L, b) == 3) {

                        A = insert(A,b,*TWb);
                        newArcDij(b, a, w, C->ax, C->ay, L);
                    }
                }
            }
            C = C->next;
        }
    }
    return a;
}