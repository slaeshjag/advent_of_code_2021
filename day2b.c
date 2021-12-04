#include <stdio.h>
#include <string.h>

struct Vec3 {
	int		x;
	int		y;
	int		z;
};


static struct Vec3 _vec_word(char *buff, struct Vec3 vec) {
	if (!strcmp(buff, "forward"))
		return (struct Vec3){1, vec.z, 0};
	if (!strcmp(buff, "up"))
		return (struct Vec3){0, 0, -1};
	if (!strcmp(buff, "down"))
		return (struct Vec3){0, 0, 1};
	return (struct Vec3){ 0 };
}


static struct Vec3 _vec_mult_scalar(struct Vec3 vec, int scalar) {
	return (struct Vec3){vec.x * scalar, vec.y * scalar, vec.z * scalar};
}


static struct Vec3 _vec_add(struct Vec3 vec1, struct Vec3 vec2) {
	return (struct Vec3){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z};
}


static int _vec_product(struct Vec3 vec) {
	return vec.x * vec.y;
}


static struct Vec3 _parse_instruction(FILE *fp, struct Vec3 vec) {
	char buff[64];
	int off;

	if (fscanf(fp, "%s %i\n", buff, &off) < 2)
		return vec;
	return _parse_instruction(fp, _vec_add(_vec_mult_scalar(_vec_word(buff, vec), off), vec));
}


int main(int argc, char **argv) {
	printf("Product: %i\n", _vec_product(_parse_instruction(stdin, (struct Vec3){ 0 })));
	return 0;
}
