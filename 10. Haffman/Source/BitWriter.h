#ifndef BIT_WRITER
#define BIT_WRITER

#include <stdio.h>

 /* Container for bits. At 8 bits collected, prints them to file (as byte). */
typedef struct BitWriter {
	unsigned short bits; /* Current value of contained bits. */
	unsigned char bitsN; /* Current number of collected bits. */
	FILE* outputFile;
} BitWriter;

 /* Constructor. */
BitWriter* bitWriterCreate(FILE* outputFile);

 /* Destructor ('file' remains opened). */
void bitWriterDestroy(BitWriter* bitWriter);

 /* Adds bites to the queue. If bitWriter collected 8 bits, it's writing byte into the 'file'. */
void bitWriterEnqueue(BitWriter* bitWriter, unsigned char bitsN, unsigned char bits);

#endif