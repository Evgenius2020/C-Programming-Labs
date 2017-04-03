#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct RingBufferElement {
	struct RingBufferElement* prev;
	struct RingBufferElement* next;
	unsigned char chr;
} RingBufferElement;

RingBufferElement* ringBufferBuild(short length) {
	if (!length) {
		return NULL;
	}

	RingBufferElement* begin = (RingBufferElement*)malloc(sizeof(RingBufferElement));
	RingBufferElement* prev = begin;
	RingBufferElement* curr = begin;
	for (length--; length > 0; length--) {
		curr = (RingBufferElement*)malloc(sizeof(RingBufferElement));
		curr->prev = prev;
		prev->next = curr;
		prev = curr;
	}
	curr->next = begin;
	begin->prev = curr;

	return begin;
}

void RingBufferDestroy(RingBufferElement* element) {
	/*while (element->next) {
		free(element->prev);
		element->prev = NULL;
		element = element->next;
	}
	free(element);*/
}

RingBufferElement* ringBufferRead(FILE* in, RingBufferElement* curr, short bytes) {
	while (bytes) {
		curr = curr->next;
		curr->chr = fgetc(in);
		if (curr->chr == EOF) {
			break;
		}
		bytes--;
	}
	return curr;
}

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

	RingBufferDestroy(curr);
	fclose(in);
	fclose(out); 
}