#include <unistd.h>
#include <string.h>
#include "track.h"


Track treatOfTrack(FILE *input, FILE *output) {
    Track t = malloc(sizeof(struct track_t));
    if (t == NULL) {
        exit(1);
    }
    
    char c;
    int sf = fscanf(input, "%d %d %d", &(t->width), &(t->height), &(t->gasLevel));

    if (t->height == 0 || t->width == 0 || t->gasLevel == 0) {
        exit(1);
    }

    while (fread(&c, sizeof(char), 1, input) == 1 && c != '\n');

    t->track = calloc(sizeof(char *), t->height);

    fprintf(stderr, "=== >Map< ===\n");
    fprintf(stderr, "Size %d x %d\n", t->width, t->height);
    fprintf(stderr, "Gas at start %d \n\n", t->gasLevel);
    for (int row = 0; row < t->height; row++) {
        t->track[row] = calloc(sizeof(char), t->width);
        fread(t->track[row], sizeof(char), t->width, input);
        fprintf(output, "%s\n", t->track[row]);
        while (fread(&c, sizeof(char), 1, input) == 1 && c != '\n');
    }
    fflush(output);

    return t;
}
