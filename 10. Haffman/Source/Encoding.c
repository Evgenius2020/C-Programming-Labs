#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CodingTree.h"
#include "BitWriter.h"
#include "Encoding.h"

/* Running a file, inserts their code to outputfile. */
void encodeText(FILE* in, BitWriter* bitWriter, char** codes) {
	short chr, i;
	while ((chr = fgetc(in)) != EOF) {
		for (i = 0; i < strlen(codes[chr]); i++) {
			bitWriterEnqueue(bitWriter, 1, codes[chr][i]);
		}
	}
}

void oneCharAlphabetCase(FILE* in, FILE* out, unsigned char chr, int textLength) {
	BitWriter* bitWriter = bitWriterCreate(out);
	bitWriterEnqueue(bitWriter, 1, 1); /* Coding tree */
	bitWriterEnqueue(bitWriter, 8, chr);
	char codeLength = (1 + 8 + 3 + textLength) % 8;
	bitWriterEnqueue(bitWriter, 3, (8 - codeLength) % 8); /* Number of fakes*/
	bitWriterEnqueue(bitWriter, (8 - codeLength) % 8, 0); /* Fakes*/
	while (textLength--) {
		bitWriterEnqueue(bitWriter, 1, 1); /* Encoded text */
	}
}

void manyCharsAlphabetCase(FILE* in, FILE* out, int* freq) {
	BitWriter* bitWriter = bitWriterCreate(out);
	Node* codingTreeRoot = buildCodingTree(freq);
	char** codes = generateCodes(codingTreeRoot);
	serializeCodingTree(bitWriter, codingTreeRoot); /* Coding tree build commands. 

	/* Fake bits calculation. */
	char codeLength = bitWriter->bitsN; /* (Coding tree code + fakesN + fakes + encoded text) % 8 */
	short i;
	for (i = 0; i < 256; i++) {
        /* Uncomment to show all codes of symbols: */
		/* printf("%s\n", codes[i]); */
		
		if (freq[i]) {
			codeLength += strlen(codes[i]) * freq[i];
			codeLength %= 8;
		}
	}
	codeLength = (codeLength + 3) % 8;

	bitWriterEnqueue(bitWriter, 3, (8 - codeLength) % 8); /* Number of fakes. */
	bitWriterEnqueue(bitWriter, (8 - codeLength) % 8, 0); /* Fakes. */
	encodeText(in, bitWriter, codes); /* Encoded text. */

	destroyTree(codingTreeRoot);
	bitWriterDestroy(bitWriter);
	for (i = 0; i < 256; i++) {
		free(codes[i]);
	}
	free(codes);
}

void encode(FILE* in, FILE* out) {
	int fileStart = ftell(in);
	short alphabetSize = 0; /* Number of unique chars in the text. */
	int* freq = calloc(256, sizeof(int));
	short chr; /* EOF-handling. */

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
		manyCharsAlphabetCase(in, out, freq);
	}

	free(freq);
}
