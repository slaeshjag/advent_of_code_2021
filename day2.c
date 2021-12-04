#include <stdio.h>
#include <string.h>

struct Vec2 {
	int		x;
	int		y;
};


static struct Vec2 _vec_word(char *buff) {
	if (!strcmp(buff, "forward"))
		return (struct Vec2){1, 0};
	if (!strcmp(buff, "up"))
		return (struct Vec2){0, -1};
	if (!strcmp(buff, "down"))
		return (struct Vec2){0, 1};
	return (struct Vec2){ 0 };
}


static struct Vec2 _vec_mult_scalar(struct Vec2 vec, int scalar) {
	return (struct Vec2){vec.x * scalar, vec.y * scalar};
}


static struct Vec2 _vec_add(struct Vec2 vec1, struct Vec2 vec2) {
	return (struct Vec2){vec1.x + vec2.x, vec1.y + vec2.y};
}


static int _vec_product(struct Vec2 vec) {
	return vec.x * vec.y;
}


static struct Vec2 _parse_instruction(FILE *fp, struct Vec2 vec) {
	char buff[64];
	int off;

	if (fscanf(fp, "%s %i\n", buff, &off) < 2)
		return vec;
	return _parse_instruction(fp, _vec_add(_vec_mult_scalar(_vec_word(buff), off), vec));
}


int main(int argc, char **argv) {
	printf("Product: %i\n", _vec_product(_parse_instruction(stdin, (struct Vec2){ 0 })));
	return 0;
}
