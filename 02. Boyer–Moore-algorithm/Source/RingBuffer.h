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
	char eofFlag;
}RingBuffer;

RingBuffer* ringBufferBuild(short length);

void ringBufferDestroy(RingBuffer* ringBuffer);

/* Reads 'bytes' bytes from 'in' file, inserting them to 'ringBuffer'.*/
void ringBufferRead(FILE* in, RingBuffer* ringBuffer, short bytes);

#endif