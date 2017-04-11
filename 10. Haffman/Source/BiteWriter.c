#include <stdio.h>
#include <stdlib.h>
#include "BiteWriter.h"

BiteWriter* biteWriterCreate(FILE* outputFile) {
	BiteWriter* writer = (BiteWriter*)malloc(sizeof(BiteWriter));
	writer->bitesN = 0;
	writer->byte = 0;
	writer->file = outputFile;
}

void biteWriterDestroy(BiteWriter* writer) {
	free(writer);
}

void biteWriterEnqueue(BiteWriter* writer, unsigned char bites, unsigned char value) {
	int i;
	for (i = 1; i <= bites; i++) {
		writer->byte = (writer->byte << 1) | ((value >> bites - i) & 1);
		writer->bitesN++;
		if (writer->bitesN == 8) {
			fputc(writer->byte, writer->file);
			writer->bitesN = 0;
			writer->byte = 0;
		}
	}
}