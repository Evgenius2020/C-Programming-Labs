#include <stdio.h>
#include <stdlib.h>
#include "BitWriter.h"

BitWriter* bitWriterCreate(FILE* outputFile) {
	BitWriter* biteWriter = (BitWriter*)malloc(sizeof(BitWriter));
	biteWriter->bits = 0;
	biteWriter->bitsN = 0;
	biteWriter->outputFile = outputFile;

	return biteWriter;
}

void bitWriterDestroy(BitWriter* bitWriter) {
	free(bitWriter);
}

void bitWriterEnqueue(BitWriter* bitWriter, unsigned char bitsN, unsigned char bits) {
	int i;
	for (i = 1; i <= bitsN; i++) {
		bitWriter->bits = (bitWriter->bits << 1) | ((bits >> bitsN - i) & 1);
		bitWriter->bitsN++;
		if (bitWriter->bitsN == 8) {
			fputc(bitWriter->bits, bitWriter->outputFile);
			bitWriter->bitsN = 0;
			bitWriter->bits = 0;
		}
	}
}