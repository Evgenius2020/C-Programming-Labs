#include <stdio.h>
#include <string.h>

int main() {
	FILE *in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	if ((!in) || (!out)) {
		return;
	}

	char templt[18];
	char shifts[256];
	char text[256];
	short i, j;

	if (fgets(templt, 18, in) == NULL) {
		return;
	}
	if (templt[strlen(templt) - 1] == '\n') {
		templt[strlen(templt) - 1] = '\0';
	}
	if (fgets(text, 256, in) == NULL) {
		return;
	}

	for (i = 0; i < 256; i++) {
		shifts[i] = strlen(templt);
	}
	for (i = 0; i < strlen(templt) - 1; i++) {
		shifts[(unsigned char)templt[i]] = strlen(templt) - i - 1;
	}

	i = strlen(templt) - 1;
	while (i < strlen(text)) {
		for (j = 0; j < strlen(templt); j++) {
			fprintf(out, "%d ", i - j + 1);
			if (templt[strlen(templt) - 1 - j] != text[i - j]) {
				break;
			}
		}
		i += shifts[(unsigned char)text[i]];
	}

	fclose(in);
	fclose(out); 
	return 0;
}