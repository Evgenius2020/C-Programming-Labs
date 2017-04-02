#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readTemplate(FILE* in) {
	char* result = (char*)malloc(sizeof(char) * 18);
	if (fgets(result, 18, in) == NULL) {
		return;
	}
	if (result[strlen(result) - 1] == '\n') {
		result[strlen(result) - 1] = '\0';
	}
	return result;
}

char* readText(FILE* in) {
	char* result = (char*)malloc(sizeof(char) * 256);
	result[0] = '\0';
	char newString[256];
	while (fgets(newString, 256, in)) {
		strcat(result, newString);
	}
	return result;
}

int main() {
	FILE *in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	if ((!in) || (!out)) {
		return;
	}

	char shifts[256];
	short i, j;
	char* templt = readTemplate(in);
	char* text = readText(in);
	if (!strlen(text)) {
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