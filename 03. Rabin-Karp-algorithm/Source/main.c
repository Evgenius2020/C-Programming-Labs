#include <stdio.h>
#include <string.h>
#include <math.h>

void action(FILE* in, FILE* out) {
	char templt[17];
	char text[256];
	long templtHash = 0;
	long textHash = 0;
	short i;
	long long textPos = 1;

	fgets(templt, 17, in);
	if ((templt[strlen(templt) - 1]) == '\n') {
		templt[strlen(templt) - 1] = '\0';
	}
	if (!fgets(text, 256, in)) {
		text[0] = '\0';
	}
	if (strlen(templt) > strlen(text)) {
		return;
	}
	for (i = 0; i < strlen(templt); i++) {
		templtHash += (templt[i] % 3) * pow(3, i);
		textHash += (text[i] % 3) * pow(3, i);
	}
	textPos += strlen(templt);
	fprintf(out, "%d ", templtHash);

	while (1) {
		if (templtHash == textHash) {
			for (i = 0; i < strlen(templt); i++) {
				if (text[textPos - strlen(templt) + i] == templt[i]) {
					fprintf(out, "%d ", textPos - strlen(templt) + i + 1);
				}
				else {
					break;
				}
			}
		}
		if (textPos >= strlen(text)) {
			break;
		}
		textHash /= 3;
		textHash += (text[textPos++] % 3) * pow(3, strlen(templt) - 1);
	}
}

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	if ((!in) || (!out)) {
		return;
	}

	action(in, out);

	fclose(in);
	fclose(out);
}