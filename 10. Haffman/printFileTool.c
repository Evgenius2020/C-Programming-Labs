#include<stdio.h>

/* Prints file in ASCII-codes */
void main(int argc, char* argv[]) {
	FILE*  in = fopen(argv[1], "rb");
	int curr;
	while(1) {
		curr = fgetc(in);
		if (curr == -1) {
			break;
		}
		printf("%d ", curr);
	}

	fclose(in);
}
