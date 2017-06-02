#ifndef BIT_READER
#define BIT_READER

#include <stdio.h>

/* Helps to read file in bits. */
typedef struct BitReader {
	unsigned short bits; /* Current value of contained bits. */
	unsigned char bitsN; /* Current number of contained bits.*/
	unsigned char eofFlag; /* <==> feof(inputFile) */
	FILE* inputFile;
} BitReader;

BitReader* bitReaderCreate(FILE* inputFile);

void bitReaderDestroy(BitReader* bitReader);

unsigned short bitReaderDequeue(BitReader* bitReader, unsigned char bitsN);

#endif