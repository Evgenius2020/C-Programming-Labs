#include <stdio.h>
#include <stdlib.h>
#include "BiteReader.h"

BiteReader* biteReaderCreate(FILE* file) {
	BiteReader* reader = (BiteReader*)malloc(sizeof(BiteReader));
	reader->bites = 0;
	reader->bitesN = 0;
	reader->eofFlag = 0;
	reader->file = file;

	return reader;
}

void biteReaderDestroy(BiteReader* reader) {
	free(reader);
}
unsigned short createMask(unsigned char length) {
	if (length > 1) {
		return (createMask(length - 1) << 1) | 1;
	}
	return length;
}

unsigned short biteReaderDequeue(BiteReader* reader, unsigned char bitesN) {
	if (reader->eofFlag) {
		return 0;
	}
	short chr;
	unsigned short result;
	if (reader->bitesN < bitesN) {
		chr = fgetc(reader->file);
		if (chr == EOF) {
			reader->eofFlag = 1;
			chr = 0;
			return reader->bites;
		}
		else {
			reader->bitesN += 8;
			reader->bites = (reader->bites << 8) | chr;
		}
	}

	result = reader->bites >> (reader->bitesN - bitesN); /*1100110 0|1101100 , 11 001001|01*/
	reader->bitesN -= bitesN;
	reader->bites = reader->bites & createMask(reader->bitesN); /*Keep last 'bitesN' bites;*/

	return result;
}