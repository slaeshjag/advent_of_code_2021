#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define	MAX_POS			2048

int g_crabs[MAX_POS];

int main(int argc, char **argv) {
	int crab;
	long long int i, j, k, acc, a, best = -1, best_tot = LLONG_MAX, tot;
	
	while (fscanf(stdin, "%i,", &crab) == 1)
		g_crabs[crab]++;
	for (i = 0; i < MAX_POS; i++) {
		for (j = 0, tot = 0; j < MAX_POS; j++) {
			a = labs(i - j);
			for (k = 0, acc = 0; k < a; k++)
				acc += (k + 1);
			tot += acc * g_crabs[j];
		}

		if (tot < best_tot)
			best_tot = tot, best = i;
	}
	
	printf("Best total amount of fuel: %lli to pos %lli\n", best_tot, best);
	return 0;
}
