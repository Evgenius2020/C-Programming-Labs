#include <stdlib.h>
#include <stdio.h>
#include "RingBuffer.h"

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

void ringBufferDestroy(RingBufferElement* element) {
	RingBufferElement* buf = element;
	while (buf != element) {
		buf = buf->next;
		free(buf->prev);
	}
	free(element);
}

RingBufferElement* ringBufferRead(FILE* in, RingBufferElement* curr, short bytes) {
	short i;
	unsigned char* buf = malloc(sizeof(char)*bytes);
	if (bytes == fread(buf, sizeof(char), bytes, in)) {
		for (i = 0; i < bytes; i++) {
			curr = curr->next;
			curr->chr = buf[i];
			if (curr->chr == EOF) {
				break;
			}
		}
	}
	else {
		curr->chr = EOF;
	}

	free(buf);
	return curr;
}