#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BingoNumber {
	int			number;
	int			flag;
};

struct BingoTable {
	int skip;
	struct BingoNumber	num[25];
};


struct BingoTable *g_bingo_table;
int g_bingo_tables;


int bingo_read(FILE *fp) {
	int q, i, j;

	q = g_bingo_tables++;
	g_bingo_table = realloc(g_bingo_table, sizeof(*g_bingo_table) * g_bingo_tables);
	memset(&g_bingo_table[q], 0, sizeof(g_bingo_table[q]));

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++)
			fscanf(fp, " %i", &g_bingo_table[q].num[i*5 + j].number);
		while (fgetc(fp) != '\n');
	}

	return (fgetc(fp) == '\n');
}


void bingo_number(int num) {
	int i, j;

	for (i = 0; i < g_bingo_tables; i++)
		for (j = 0; j < 25; j++)
			if (g_bingo_table[i].num[j].number == num)
				g_bingo_table[i].num[j].flag = 1;
}


void bingo(int table, int winning_number) {
	int i, sum;

	for (i = sum = 0; i < 25; i++)
		if (!g_bingo_table[table].num[i].flag)
			sum += g_bingo_table[table].num[i].number;
	printf("Final score: %i (board %i, number %i)\n", sum * winning_number, table, winning_number);
	g_bingo_table[table].skip = 1;
}


void bingo_check(int number) {
	int i, j, k;

	for (i = 0; i < g_bingo_tables; i++) {
		if (g_bingo_table[i].skip)
			continue;
		// Check rows
		for (j = 0; j < 5; j++) {
			for (k = 0; k < 5; k++)
				if (!g_bingo_table[i].num[j*5 + k].flag)
					break;
			if (k == 5)
				bingo(i, number);
		}

		// Check rows
		for (j = 0; j < 5; j++) {
			for (k = 0; k < 5; k++)
				if (!g_bingo_table[i].num[j + k*5].flag)
					break;
			if (k == 5)
				bingo(i, number);
		}
	}
}


int bingo_run(FILE *fp) {
	int num;

	if (fscanf(fp, "%i,", &num) != 1)
		fprintf(stderr, "Nobody wins\n"), exit(1);
	bingo_number(num);
	bingo_check(num);
	return 0;
}


int main(int argc, char **argv) {
	FILE *fp;
	int i;

	for (i = 0, fp = fopen(argv[1], "r"); fgetc(fp) != '\n'; i++);
	fgetc(fp); // separating newline
	
	while (bingo_read(fp));
	rewind(fp);
	while (!bingo_run(fp));
}
