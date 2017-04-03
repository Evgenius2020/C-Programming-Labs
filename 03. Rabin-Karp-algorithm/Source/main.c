#include <stdio.h>

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");



	fclose(in);
	fclose(out);
}