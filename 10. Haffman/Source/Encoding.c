#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CodingTree.h"
#include "BiteWriter.h"
#include "Encoding.h"

/* Running a file, inserts their code to outputfile */
void encodeText(FILE* in, BiteWriter* writer, char** codes) {
	short chr, i;
	while ((chr = fgetc(in)) != EOF) {
		for (i = 0; i < strlen(codes[chr]); i++) {
			biteWriterEnqueue(writer, 1, codes[chr][i]); // TODO: whole code must be inserted into queue
		}
	}
}

void oneCharAlphabetCase(FILE* in, FILE* out, unsigned char chr, int textLength) {
	BiteWriter* writer = biteWriterCreate(out);
	short i;

	biteWriterEnqueue(writer, 8, 1); /* Alphabet size */
	biteWriterEnqueue(writer, 1, 1); /* Coding tree */
	biteWriterEnqueue(writer, 8, chr);
	char codeLength = (8 + 1 + 8 + 3 + textLength) % 8;
	biteWriterEnqueue(writer, 3, (8 - codeLength) % 8); /* Number of fakes*/
	biteWriterEnqueue(writer, (8 - codeLength) % 8, 0); /* Fakes*/
	while (textLength--) {
		biteWriterEnqueue(writer, 1, 1); /* Encoded text */
	}
}

void manyCharsAlphabetCase(FILE* in, FILE* out, int* freq, char alphabetSize) {
	BiteWriter* writer = biteWriterCreate(out);
	biteWriterEnqueue(writer, 8, alphabetSize); /* Alphabet size */
	Node* codingTreeRoot = buildCodingTree(freq);
	char** codes = generateCodes(codingTreeRoot);
	serializeCodingTree(writer, codingTreeRoot); /* Coding tree build comands */
	short freeBites = writer->bitesN;
	short i;
	for (i = 0; i < 256; i++) {
		if (freq[i]) {
			freeBites += strlen(codes[i]) * freq[i];
			freeBites %= 8;
		}
	}
	freeBites = (freeBites + 3) % 8;
	biteWriterEnqueue(writer, 3, (8 - freeBites) % 8); /* Number of fakes*/
	biteWriterEnqueue(writer, (8 - freeBites) % 8, 0); /* Fakes*/
	encodeText(in, writer, codes); /* Encoded text */

	destroyTree(codingTreeRoot);
	biteWriterDestroy(writer);
	for (i = 0; i < 256; i++) {
		free(codes[i]);
	}
	free(codes);
}

void encode(FILE* in, FILE* out) {
	int fileStart = ftell(in);
	unsigned char alphabetSize = 0; /* Number of unique chars in the text */
	int* freq = calloc(256, sizeof(int));
	short chr; /* EOF-handling */

	while ((chr = fgetc(in)) != EOF) {
		if (!freq[chr]) {
			alphabetSize++;
		}
		freq[chr]++;
	}
	fseek(in, fileStart, SEEK_SET);

	if (alphabetSize == 1) {
		for (chr = 0; chr < 256, !freq[chr]; chr++);
		oneCharAlphabetCase(in, out, chr, freq[chr]);
	}
	if (alphabetSize > 1) {
		manyCharsAlphabetCase(in, out, freq, alphabetSize);
	}

	free(freq);
}