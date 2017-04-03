#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RingBuffer.h"

unsigned char* readTemplate(FILE* in) {
	unsigned char* result = (unsigned char*)malloc(sizeof(char) * 18);
	if (fgets(result, 18, in) == NULL) {
		return;
	}
	if (result[strlen(result) - 1] == '\n') {
		result[strlen(result) - 1] = '\0';
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
	short i;
	unsigned long long textPos;
	unsigned char* templt = readTemplate(in);
	RingBufferElement* curr = ringBufferBuild(strlen(templt));
	RingBufferElement* buf;
	ringBufferRead(in, curr, strlen(templt));
	textPos = strlen(templt);

	for (i = 0; i < 256; i++) {
		shifts[i] = strlen(templt);
	}
	for (i = 0; i < strlen(templt) - 1; i++) {
		shifts[(unsigned char)templt[i]] = strlen(templt) - i - 1;
	}

	i = strlen(templt);
	buf = curr;
	while (curr->chr != 255) {
		if (i > 0) {
			fprintf(out, "%d ", textPos - (strlen(templt) - i));
			if (buf->chr == templt[i - 1]) {
				i--;
				buf = buf->prev;
				continue;
			}
		}

		textPos += shifts[curr->chr];
		curr = ringBufferRead(in, curr, shifts[curr->chr]);
		buf = curr;
		i = strlen(templt);
	}

	ringBufferDestroy(curr);
	fclose(in);
	fclose(out); 
}