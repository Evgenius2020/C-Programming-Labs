#include <stdlib.h>
#include <stdio.h>
#include "RingBuffer.h"

RingBuffer* ringBufferBuild(short length) {
	if (!length) {
		return NULL;
	}

	RingBufferElement* begin = (RingBufferElement*)malloc(sizeof(RingBufferElement));
	RingBufferElement* prev = begin;
	RingBufferElement* curr = begin;

	RingBuffer* result = (RingBuffer*)malloc(sizeof(RingBuffer));
	result->eofFlag = 0;
	result->currElement = begin;
	result->strBuf = malloc(sizeof(char) * length);

	for (length--; length > 0; length--) {
		curr = (RingBufferElement*)malloc(sizeof(RingBufferElement));
		curr->prev = prev;
		prev->next = curr;
		prev = curr;
	}
	curr->next = begin;
	begin->prev = curr;

	return result;
}

void ringBufferDestroy(RingBuffer* ringBuffer) {
	RingBufferElement* buf = ringBuffer->currElement->next;
	while (buf != ringBuffer->currElement) {
		buf = buf->next;
		free(buf->prev);
	}
	free(ringBuffer->currElement);
	free(ringBuffer->strBuf);
	free(ringBuffer);
}

void ringBufferRead(FILE* in, RingBuffer* ringBuffer, short bytes) {
	short i;
	char readed = fread(ringBuffer->strBuf, sizeof(char), bytes, in);
	if (readed == bytes) {
		for (i = 0; i < bytes; i++) {
			ringBuffer->currElement = ringBuffer->currElement->next;
			ringBuffer->currElement->chr = ringBuffer->strBuf[i];
		}
	}
	else {
		ringBuffer->eofFlag = 1;
	}
}