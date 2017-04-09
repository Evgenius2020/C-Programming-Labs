#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PriorityQueue.h"
#include "BiteWriter.h"
#include "Encoding.h"

typedef struct Node {
	struct Node* parent;
	char sgn; /* 0 - if left leaf, 1 - if right leaf*/
	short freq;
}Node;

Node* createEncodeNode(short freq) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->parent = NULL;
	node->freq = freq;

	return node;
}

/* Running a file, inserts their code to outputfile */
void encodeText(FILE* in, BiteWriter* writer, char** codes) {
	short chr, i;
	while ((chr = fgetc(in)) != EOF) {
		for (i = 0; i < strlen(codes[chr]); i++) {
			biteWriterEnqueue(writer, 1, codes[chr][i]); // TODO: whole code must be inserted into queue
		}
	}
}

/* Generates codes for each char to encode */
char** generateCodes(int* freq) {
	PriorQueue* queue = priorQueueCreate(256);
	Node** leaves = (Node**)calloc(256, sizeof(Node*)); /* char-ended leaves for navigation.*/
	char** codes = (char**)calloc(sizeof(char*), 256);
	short i;
	for (i = 0; i < 256; i++) {
		if (freq[i]) {
			leaves[i] = createEncodeNode(freq[i]);
			codes[i] = (char*)malloc(sizeof(char) * 256);
			priorQueueInsert(queue, leaves[i], freq[i]);
		}
	}

	Node *newNode, *left, *right;
	/* Coding tree building */
	while (!priorQueueIsEmpty(queue)) {
		left = priorQueueExtractMin(queue);
		right = priorQueueExtractMin(queue);
		if (right) {
			newNode = createEncodeNode(left->freq + right->freq);
			left->parent = newNode;
			left->sgn = 0;
			right->parent = newNode;
			right->sgn = 1;
			priorQueueInsert(queue, newNode, newNode->freq);
		}
	}

	Node* buf;
	int strIndex;
	for (i = 0; i < 256; i++) {
		if (freq[i]) {
			strIndex = 0;
			buf = leaves[i];
			while (buf->parent) {
				codes[i][strIndex++] = buf->sgn + '0';
				buf = buf->parent;
			}
			codes[i][strIndex] = '\0';
			codes[i] = strrev(codes[i]);
		}
	}

	Node* parent;
	for (i = 0; i < 256; i++) {
		buf = leaves[i];
		if (buf) {
			parent = buf->parent;
			free(buf);
			buf = parent;
		}
	}

	priorQueueDestroy(queue);
	free(leaves);
	return codes;
}

void serializeCodes(char** codes, BiteWriter* writer) {
	short i, j;
	for (i = 0; i < 256; i++) {
		if (codes[i]) {
			biteWriterEnqueue(writer, 8, strlen(codes[i]));
			for (j = 0; j < strlen(codes[i]); j++) {
				biteWriterEnqueue(writer, 1, codes[i][j]); // TODO: NO WAY MAN!
			}
		}
	}
}

void oneCharAlphabetCase(FILE* in, FILE* out, unsigned char chr, int textLength) {
	BiteWriter* writer = biteWriterCreate(out);
	short i;

	for (i = 0; i < 256; i++) {
		biteWriterEnqueue(writer, 1, (i == chr) ? 1 : 0); /* Encoded chars mask */
	}
	biteWriterEnqueue(writer, 8, 1); /* Code length*/
	biteWriterEnqueue(writer, 1, 1); /* Code*/
	char codeLength = (256 + 8 + 1 + 3 + textLength) % 8;
	biteWriterEnqueue(writer, 3, (8 - codeLength) % 8); /* Number of fakes*/
	biteWriterEnqueue(writer, (8 - codeLength) % 8, 0); /* Fakes*/
	while(textLength--) {
		biteWriterEnqueue(writer, 1, 1); /* Encoded text */
	}
}

void printMask(int* freq, BiteWriter* writer) {
	int i;
	for (i = 0; i < 256; i++) {
		biteWriterEnqueue(writer, 1, freq[i] ? 1 : 0);
	}
}

void manyCharsAlphabetCase(FILE* in, FILE* out, int* freq, char alphabetSize) {
	BiteWriter* writer = biteWriterCreate(out);
	printMask(freq, writer); /* Encoded chars mask */
	char** codes = generateCodes(freq);
	serializeCodes(codes, writer); /* Codes */
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

	biteWriterDestroy(writer);
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
		manyCharsAlphabetCase(in, out , freq, alphabetSize);
	}

	free(freq);
}