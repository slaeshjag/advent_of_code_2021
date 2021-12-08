#include <stdio.h>
#include <stdint.h>

int count[10] = { 0 };
int total;

uint8_t read_segment(FILE *fp) {
	char buff[32] = { 0 };
	uint8_t segment = 0;
	int i;

	if (fscanf(fp, " %s", buff) < 1)
		return 0xFF;
	
	for (i = 0; buff[i]; i++)
		segment |= 1 << (buff[i] - 'a');
	return segment;
}


int lookup_segment(uint8_t seg, uint8_t *list) {
	int i;

	for (i = 0; i < 10; i++)
		if (seg == list[i])
			return i;
	return 0;
}


int count_bits(uint8_t byte) {
	int i, n;

	for (i = n = 0; i < 8; i++)
		if (byte & (1 << i))
			n++;
	return n;
}


void solve_segments(uint8_t *input_segments) {
	uint8_t tmp_segments[10] = { 0 };
	int i, j;

	for (i = j = 0; i < 10; i++) {
		if (count_bits(input_segments[i]) == 2)
			tmp_segments[1] = input_segments[i];
		else if (count_bits(input_segments[i]) == 3)
			tmp_segments[7] = input_segments[i];
		else if (count_bits(input_segments[i]) == 4)
			tmp_segments[4] = input_segments[i];
		else if (count_bits(input_segments[i]) == 7)
			tmp_segments[8] = input_segments[i];
	}
	for (i = 0; i < 10; i++)
		if (count_bits(input_segments[i]) == 5)
			if ((input_segments[i] | tmp_segments[1]) == input_segments[i])
				tmp_segments[3] = input_segments[i]; // Found number 3
	for (i = 0; i < 10; i++)
		if (count_bits(input_segments[i]) == 6) {
			if ((input_segments[i] | tmp_segments[3]) == input_segments[i])
				tmp_segments[9] = input_segments[i]; // Found number 9
			else if ((input_segments[i] | tmp_segments[1]) == 0x7F)
				tmp_segments[6] = input_segments[i]; // found number 6
			else
				tmp_segments[0] = input_segments[i]; // found number 0
		}
	
	for (i = 0; i < 10; i++)
		if (count_bits(input_segments[i]) == 5 && (input_segments[i] | tmp_segments[1]) != input_segments[i]) {
			if ((input_segments[i] | tmp_segments[1]) == tmp_segments[9])
				tmp_segments[5] = input_segments[i];
			else
				tmp_segments[2] = input_segments[i];
		}
	
	for (i = 0; i < 10; i++)
		input_segments[i] = tmp_segments[i];
}


int process_line(FILE *fp) {
	int i, j;
	uint8_t segments[10];
	
	for (i = 0; i < 10; i++)
		if ((segments[i] = read_segment(fp)) == 0xFF)
			return 0;
	solve_segments(segments);
	fscanf(fp, " |");
	int seg[4], num;
	for (j = 0; j < 4; j++)
		count[(seg[j] = lookup_segment(read_segment(fp), segments))]++;
	num = seg[0] * 1000 + seg[1] * 100 + seg[2] * 10 + seg[3];
	total += num;
	return 1;
}


int main(int argc, char **argv) {
	while (process_line(stdin));
	printf("Result A: %i\n", count[1] + count[4] + count[7] + count[8]);
	printf("Result B: %i\n", total);

	return 0;
}
