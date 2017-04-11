#ifndef BITE_WRITER
#define BITE_WRITER

#include <stdio.h>

 /*Container for bites. On 8 bites collected, prints them to file (as byte).*/
typedef struct BiteWriter {
	unsigned short byte;
	unsigned char bitesN;
	FILE* file;
} BiteWriter;

 /*Constructor.*/
BiteWriter* biteWriterCreate(FILE* outputFile);

 /*Destructor ('file' remains opened).*/
void biteWriterDestroy(BiteWriter* writer);

 /*Adds bites to the queue. If writer collected 8 bites, it's writing byte into the 'file'.*/
void biteWriterEnqueue(BiteWriter* writer, unsigned char bites, unsigned char value);

#endif