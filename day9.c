#include <stdio.h>
#include <stdlib.h>

#define	MAP_W	100
#define	MAP_H	100
//#define	MAP_W	10
//#define	MAP_H	5

#define	INDEX(x, y) ((x) + (y) * MAP_W)

int g_height[MAP_W * MAP_H];

int *g_basin;
int g_basins;

int get_pos(int cur, int dx, int dy) {
	int cur_x, cur_y;

	cur_x = cur % MAP_W;
	cur_y = cur / MAP_W;
	cur_x += dx;
	cur_y += dy;

	if (cur_x < 0 || cur_x >= MAP_W)
		return 11;
	if (cur_y < 0 || cur_y >= MAP_H)
		return 11;
	return g_height[INDEX(cur_x, cur_y)];
}


int basin_size(int i) {
	int cur_x, cur_y, size, here;

	cur_x = i % MAP_W;
	cur_y = i / MAP_W;

	if (g_height[i] == 9)
		return 0;
		
	here = g_height[i];
	
	g_height[i] = 9;
	size = 1;
	if (cur_x > 0 && here <= get_pos(i, -1, 0))
		size += basin_size(INDEX(cur_x - 1, cur_y));
	if (cur_x + 1 < MAP_W && here <= get_pos(i, 1, 0))
		size += basin_size(INDEX(cur_x + 1, cur_y));
	if (cur_y > 0 && here <= get_pos(i, 0, -1))
		size += basin_size(INDEX(cur_x, cur_y - 1));
	if (cur_y + 1 < MAP_H && here <= get_pos(i, 0, 1))
		size += basin_size(INDEX(cur_x, cur_y + 1));
	return size;
}


void analyze_basin(int i) {
	int q;

	q = g_basins++;
	g_basin = realloc(g_basin, sizeof(*g_basin) * g_basins);
	g_basin[q] = basin_size(i);
}


int basin_cmp(const void *q1, const void *q2) {
	return *((int *) q1) - *((int *) q2);
}


int main(int argc, char **argv) {
	int i;
	int risk;

	for (i = 0; i < MAP_W * MAP_H; i++)
		fscanf(stdin, "%1d", &g_height[i]);
	for (i = risk = 0; i < MAP_W * MAP_H; i++) {
		if (get_pos(i, -1, 0) <= g_height[i])
			continue;
		if (get_pos(i, 1, 0) <= g_height[i])
			continue;
		if (get_pos(i, 0, -1) <= g_height[i])
			continue;
		if (get_pos(i, 0, 1) <= g_height[i])
			continue;
		risk += (g_height[i] + 1);
		analyze_basin(i);
	}

	qsort(g_basin, g_basins, sizeof(*g_basin), basin_cmp);

	printf("Solution A: %i\n", risk);
	printf("Solution B: %i (%i %i %i)\n", g_basin[g_basins - 1] * g_basin[g_basins - 2] * g_basin[g_basins - 3], g_basin[g_basins - 1], g_basin[g_basins - 2], g_basin[g_basins - 3]);
	return 0;
}
