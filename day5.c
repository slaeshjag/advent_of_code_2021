#include <stdio.h>
#include <stdlib.h>

#define	MAX_X			1024
#define	MAX_Y			1024

int main(int argc, char **argv) {
	for (int x1, x2, y1, y2, state = 0, substate = 0, count = 0, *field = calloc(MAX_X, 4*MAX_Y); state <3; state = (state == 0 ? ((fscanf(stdin, "%i,%i -> %i,%i\n", &x1, &y1, &x2, &y2) == 4) ? 1 : 2) : (state == 1 ? ((substate = (x1 == x2 && y1 == y2 ? 0 : 1), ((field[y1*MAX_X+x1]++), (x1 != x2) ? ((x1 > x2) ? x1-- : x1++) : (void) (x1)), ((y1 != y2) ? ((y1 > y2) ? y1-- : y1++) : (void) x1), substate)) : ((substate < MAX_X*MAX_Y) ? ((field[substate] >= 2 ? count++ : (void) count), substate++, 2) : (printf("2+ lines intersect at %i points\n", count), 3)))));

}
