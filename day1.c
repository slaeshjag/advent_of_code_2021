#include <stdio.h>

int main(int argc, char **argv) {
	int last, new, i, larger;
	int window[3] = { }, last_sum = 0, new_sum = 0, sum_larger = 0;

	for (i = last = larger = 0; !feof(stdin); i++) {
		if (fscanf(stdin, "%i\n", &new) < 0)
			break;
		if (new > last && i)
			larger++;
		last = new;

		last_sum = window[2] + window[1] + window[0];
		window[2] = window[1];
		window[1] = window[0];
		window[0] = new;
		new_sum = window[2] + window[1] + window[0];
		
		if (last_sum < new_sum && i > 2)
			sum_larger++;
	}

	printf("%i sums larger\n", sum_larger);
	printf("%i larger\n", larger);
	return 0;
}
