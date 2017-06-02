#include <stdio.h>
#include <stdlib.h>
#include "BitReader.h"

BitReader* bitReaderCreate(FILE* inputFile) {
	BitReader* bitReader = (BitReader*)malloc(sizeof(BitReader));
	bitReader->bits = 0;
	bitReader->bitsN = 0;
	bitReader->eofFlag = 0;
	bitReader->inputFile = inputFile;

	return bitReader;
}

void bitReaderDestroy(BitReader* bitReader) {
	free(bitReader);
}

static unsigned short masks[8] = {1, 3, 7, 15, 31, 63, 127, 255}; /* For erasing first bits on dequeue with AND operation. */

unsigned short bitReaderDequeue(BitReader* bitReader, unsigned char bitsN) {
	if (bitReader->eofFlag) {
		return 0;
	}
	short chr;
	unsigned short result;
	if (bitReader->bitsN < bitsN) {
		chr = fgetc(bitReader->inputFile);
		if (chr == EOF) {
			bitReader->eofFlag = 1;
			chr = 0;
			return bitReader->bits;
		}
		else {
			bitReader->bitsN += 8;
			bitReader->bits = (bitReader->bits << 8) | chr;
		}
	}

	result = bitReader->bits >> (bitReader->bitsN - bitsN); /* Get first 'bitsN' bits. */
	bitReader->bitsN -= bitsN;
	bitReader->bits = bitReader->bits & masks[bitReader->bitsN - 1]; /* Erase first 'bitsN' bits. */

	return result;
}