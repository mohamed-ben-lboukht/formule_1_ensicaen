#include <time.h>
#include "track.h"
#include "graph.h"

int gasConsumption(int accX, int accY, int speedX, int speedY, int inSand)
{
  int gas = accX * accX + accY * accY;
  gas += (int)(sqrt(speedX * speedX + speedY * speedY) * 3.0 / 2.0);
  if (inSand) {
    gas += 1;
  }
  return -gas;
}

void sendAcceleration(int ax, int ay, int fuel, FILE *log) {
    char action[10];
    sprintf(action, "%d %d", ax, ay);
    fprintf(stdout, "%s\n", action);
    fprintf(log, "\t%s (carburant restant %d)\n", action, fuel);
    fflush(stdout);
    fflush(log);
}

int main() {

    int lowerFuel = 0, increaseFuel = 0, round = 0, crash = 1;
    int sf, ax, ay, gasLevel, bloque;
    float x0 = 0, x1 = 10, x = 2.5;
    char vb, vc;
    float i1 = 0.97f;
    float i2 = 0.93f;
    point a1, a2, b, c, finalPoint;
    Stack *route = NULL;
    Ladj *L = NULL;

    FILE *log = stderr;
    FILE *input = stdin;
    Track T = treatOfTrack(input, log);
    
    gasLevel = T->gasLevel;

    fflush(log);
    fprintf(log, "\n=== Race start ===\n");
    fprintf(log, "%f %f", i1, i2);

    do {

        round++;
        fprintf(log, "=== ROUND %d\n", round);
        fflush(log);
        fscanf(stdin, "%d %d\t%d %d\t%d %d", &(a1.y), &(a1.x), &(b.y), &(b.x), &(c.y), &(c.x));
        fprintf(log, "    Positions: A(%d,%d)  B(%d,%d), C(%d,%d)\n", a1.y, a1.x, b.y, b.x, c.y, c.x);
        fflush(log);

        if (round == 1 || a1.x != a2.x || a1.y != a2.y) {
            crash = 1;
            fprintf(log, "\tCRASH\n");
            fflush(log);
        } else {
            a1 = a2;
            a2 = popStack(route);
            crash = 0;
        }

        bloque = (a2.x == b.x && a2.y == b.y) || (a2.x == c.x && a2.y == c.y);

        if (crash || bloque || lowerFuel || increaseFuel) {

            fprintf(log, "\tNouvelle trajectoire : ");
            if (lowerFuel) {
                x1 = x;
                x = (x0 + x1) / 2;
                fprintf(log, " - lowFuel x = %.2f.\n", x);
            } else if (increaseFuel) {
                x0 = x;
                x = (x0 + x1) / 2;
                fprintf(log, " + incFuel x = %.2f.\n", x);
            } else if (round > 1) {

                x0 = 0;
                x = (x0 + x1) / 2;
                fprintf(log, " route bloquée.\n");
            }else{
                fprintf(log,"\n");
            }

            fflush(log);

            vb = T->track[b.x][b.y];
            vc = T->track[c.x][c.y];
            T->track[b.x][b.y] = '.';
            T->track[c.x][c.y] = '.';

            if (crash == 1) {
                a1.vx = 0;
                a1.vy = 0;
            }
            if (round > 1) {
                freeLadj(L, T);
            }
            L = initLadj(T);
            loadLadj(L, T, a1);
            finalPoint = dijkstra(L, T, a1, x);
            route = findRoute(L, finalPoint);

            lowerFuel = ((float) *totFuel(L, finalPoint)) > i1 * ((float) gasLevel);
            increaseFuel = ((float) *totFuel(L, finalPoint)) < i2 * ((float) gasLevel);


            a1 = popStack(route);
            a2 = popStack(route);

            T->track[b.x][b.y] = vb;
            T->track[c.x][c.y] = vc;
        }

        ay = a2.vx - a1.vx;
        ax = a2.vy - a1.vy;

        gasLevel += gasConsumption(ax, ay, a1.vx, a1.vy, testPt(T, a1, 'inSAND'));
        sendAcceleration(ax, ay, gasLevel, log);

    } while (!feof(stdin));
    return sf;
}