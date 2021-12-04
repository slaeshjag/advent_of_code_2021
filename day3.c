#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAX_BITS 32

int g_pop[MAX_BITS];
int g_len;
unsigned int *g_code;


void process_code(char *str) {
	int i, len, bit;

	g_code = realloc(g_code, sizeof(*g_code) * (g_len + 1));
	g_code[g_len] = 0;
	len = strlen(str);
	for (i = 0; i < len; i++) {
		bit = (str[len - i - 1] == '1');
		g_pop[i] += bit;
		g_code[g_len] |= bit << i;
	}

	g_len++;

}


unsigned int make_gamma() {
	unsigned int i, gamma = 0;

	for (i = 0; i < MAX_BITS; i++)
		if (g_pop[i] > (g_len >> 1))
			gamma |= (1 << i);
	return gamma;
}


unsigned int make_epsilon() {
	unsigned int i, epsilon = 0;

	for (i = 0; i < MAX_BITS && g_pop[i]; i++)
		if (g_pop[i] <= (g_len >> 1))
			epsilon |= (1 << i);
	return epsilon;
}


unsigned int make_rating(int bit, unsigned int *code, int length, int co2) {
	int i, pop = 0, new_len;
	unsigned int target, mask;

	if (length == 1)
		return code[0];
	mask = (1 << bit);
	for (i = 0; i < length; i++)
		if (code[i] & mask)
			pop++;
	if (!co2) {
		target = pop*2 >= (length) ? mask : 0;
	} else {
		target = pop*2 < (length) ? mask : 0;
	}
	
	new_len = target ? pop : length - pop;
	if (!new_len)
		return make_rating(bit - 1, code, length, co2);

	/* New subset */ {
		unsigned int new_code[new_len];
		int j;
		for (i = j = 0; i < length; i++)
			if ((code[i] & mask) == target)
				new_code[j++] = code[i];
		return make_rating(bit - 1, new_code, new_len, co2);

	}
}


int main(int argc, char **argv) {
	char tmp[256];
	unsigned int gamma, epsilon, ox, co2;
	FILE *fp = fopen(argv[1], "r");


	while (fscanf(fp, "%[01]\n", tmp) == 1)
		process_code(tmp);
	gamma = make_gamma();
	epsilon = make_epsilon();
	printf("Power consumption: %u\n", gamma * epsilon);
	printf("Oxygen generator rating: %u\n", ox = make_rating(11, g_code, g_len, 0));
	printf("CO2 scrubber rating: %u\n", co2 = make_rating(11, g_code, g_len, 1));
	printf("Life support rating: %u\n", ox*co2);

	return 0;
}
