#include <stdio.h>
#include <string.h>

int main() {
	FILE *in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	char templt[17];
	fscanf(in, "%s ", templt);

	char shifts[256];
	int i;
	for (i = 0; i < 256; i++) {
		shifts[i] = strlen(templt);
	}
	for (i = 0; i < strlen(templt); i++) {
		shifts[templt[i]] = strlen(templt) - i - 1;
	}

	char text[256];
	i = strlen(templt) - 1;
	int j = 0;
	fgets(text, 256, in);
	while (i < strlen(text)) {
		fprintf(out, "%d ", i - j + 1);
		if (i - j >= 0) {
			if (text[i - j] == templt[strlen(templt) - 1 - j]) {
				j++;
				if (j != strlen(templt)) { 
					continue;
				}
			}
		}
		i += shifts[text[i - j]];
		j = 0;
	}

	fclose(in);
	fclose(out); 
	return 0;
}