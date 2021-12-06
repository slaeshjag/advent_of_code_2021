#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int main(int argc, char **argv) {
	uint64_t fish[9] = { 0 }, total;
	int i, n;

	while (fscanf(stdin, "%i,", &i) == 1)
		fish[i]++;
	for (n = atoi(argv[1]), i = 0; i < n; i++) {
		uint64_t today;

		today = fish[0];
		memmove(fish, fish + 1, sizeof(*fish) * 8);
		fish[6] += today;
		fish[8] = today;
	}

	for (i = 0, total = 0; i < 9; i++)
		total += fish[i];
	printf("Total fishes after %i days: %lu\n", n, total);
	return 0;
}
