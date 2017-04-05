#ifndef RING_BUFFER
#define RING_BUFFER

typedef struct RingBufferElement {
	struct RingBufferElement* prev;
	struct RingBufferElement* next;
	unsigned char chr;
} RingBufferElement;

typedef struct RingBuffer {
	unsigned char* buffer;
	RingBufferElement* currElement;
}RingBuffer;

RingBuffer* ringBufferBuild(short length);

void ringBufferDestroy(RingBuffer* ringBuffer);

void ringBufferRead(FILE* in, RingBuffer* ringBuffer, short bytes);

#endif