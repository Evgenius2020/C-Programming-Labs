#include <stdio.h>
#include <string.h>
#include "Encoding.h"
#include "Decoding.h"

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	
	char cmd;
	fscanf(in, "%c ", &cmd);
	if (cmd == 'd') {
		decode(in, out);
	}
	if (cmd == 'c') {
		encode(in, out);
	}

	fclose(in);
	fclose(out);
	return 0;
}