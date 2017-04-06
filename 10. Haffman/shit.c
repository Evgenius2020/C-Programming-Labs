#include<stdio.h>

void main(int argc, char* argv[]) {
	FILE*  in = fopen(argv[1], "r");
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
