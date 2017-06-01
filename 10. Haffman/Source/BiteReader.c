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
static unsigned short masks[8] = {1, 3, 7, 15, 31, 63, 127, 255};

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

	result = reader->bites >> (reader->bitesN - bitesN);
	reader->bitesN -= bitesN;
	reader->bites = reader->bites & masks[reader->bitesN - 1]; /*Keep last 'bitesN' bites;*/

	return result;
}