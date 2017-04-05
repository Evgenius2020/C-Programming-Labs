#include <stdlib.h>
#include <stdio.h>
#include "RingBuffer.h"

RingBuffer* ringBufferBuild(short length) {
	if (!length) {
		return NULL;
	}

	RingBuffer* result = (RingBuffer*)malloc(sizeof(RingBuffer));
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

	result->buffer = (unsigned char*)calloc(length, sizeof(char));
	result->currElement = begin;
	return result;
}

void ringBufferDestroy(RingBuffer* ringBuffer) {
	RingBufferElement* buf = ringBuffer->currElement->next;
	while (buf != ringBuffer->currElement) {
		buf = buf->next;
		free(buf->prev);
	}
	free(ringBuffer->currElement);
	free(ringBuffer->buffer);
	free(ringBuffer);
}

void ringBufferRead(FILE* in, RingBuffer* ringBuffer, short bytes) {
	short i;
	if (bytes == fread(ringBuffer->buffer, sizeof(unsigned char), bytes, in)) {
		for (i = 0; i < bytes; i++) {
			ringBuffer->currElement = ringBuffer->currElement->next;
			ringBuffer->currElement->chr = ringBuffer->buffer[i];
			if (ringBuffer->currElement->chr == EOF) {
				break;
			}
		}
	}
	else {
		ringBuffer->currElement->chr = EOF;
	}
}