#include <stdio.h>
#include <string.h>
#include <math.h>
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

void searchMatches(FILE* in, FILE* out, char* templt) {
	RingBuffer* ringBuffer = ringBufferBuild(strlen(templt));
	RingBufferElement* buf;
	short i;
	long long textPos = 1;
	long templtHash = 0;
	long textHash = 0;

	for (i = 0; i < strlen(templt); i++) {
		templtHash += (templt[i] % 3) * pow(3, i);
		ringBufferRead(in, ringBuffer, 1);
		textHash += (ringBuffer->currElement->chr % 3) * pow(3, i);
	}
	textPos += strlen(templt);
	fprintf(out, "%d ", templtHash);

	while (!ringBuffer->eofFlag) {
		if (templtHash == textHash) {
			i = 0;
			buf = ringBuffer->currElement->next;
			while ((buf->chr == templt[i]) && (i < strlen(templt))) {
				fprintf(out, "%d ", textPos - strlen(templt) + i);
				i++;
				buf = buf->next;
			}
		}

		ringBufferRead(in, ringBuffer, 1);
		textHash /= 3;
		textHash += (ringBuffer->currElement->chr % 3) * pow(3, strlen(templt) - 1);
		textPos++;
	}

	ringBufferDestroy(ringBuffer);
}

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	if ((!in) || (!out)) {
		return;
	}

	char* templt = readTemplate(in);
	searchMatches(in, out, templt);

	free(templt);
	fclose(in);
	fclose(out);
}