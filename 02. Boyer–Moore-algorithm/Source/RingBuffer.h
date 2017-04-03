#ifndef RING_BUFFER
#define RING_BUFFER

typedef struct RingBufferElement {
	struct RingBufferElement* prev;
	struct RingBufferElement* next;
	unsigned char chr;
} RingBufferElement;

RingBufferElement* ringBufferBuild(short length);

void ringBufferDestroy(RingBufferElement* element);

RingBufferElement* ringBufferRead(FILE* in, RingBufferElement* curr, short bytes);

#endif