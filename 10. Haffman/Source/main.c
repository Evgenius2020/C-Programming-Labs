#include <stdio.h>
#include <string.h>
#include "Encoding.h"
#include "Decoding.h"

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	
	char buf[5];
	fgets(&buf, 5, in);
	char cmd = buf[0];
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