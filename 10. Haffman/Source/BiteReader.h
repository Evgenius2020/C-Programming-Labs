#ifndef BITE_READER
#define BITE_READER

typedef struct BiteReader {
	unsigned char bitesN; /* Current number of contained bites.*/
	unsigned short bites;
	unsigned char eofFlag;
	FILE* file;
} BiteReader;

BiteReader* biteReaderCreate(FILE* file);

void biteReaderDestroy(BiteReader* reader);

unsigned short biteReaderDequeue(BiteReader* reader, unsigned char bitesN);

#endif