#include <stdio.h>
#include <stdlib.h>
#include "../../Common/PriorityQueue/Source/PriorityQueue.c"
#include "../../Common/Stacks/Stack-void/Source/Stack.c"
#include "BiteWriter.h"
#include "Encoding.h"

#define exit free(freq); free(leaves); biteWriterDestroy(writer); return

typedef struct Node {
	struct Node* parent;
	char sgn; /* 0 - if left leaf, 1 - if right leaf*/
}Node;

Node* createEncodeNode() {
	Node* node = (Node*)malloc(sizeof(Node));
	node->parent = NULL;

	return node;
}

void encode(FILE* in, FILE* out) {
	int fileStart = ftell(in);
	unsigned char alphabetSize = 0; /* Number of encoded chars (1-256).*/
	unsigned char codeLength = 0; /* Number of bites in encoded text.*/
	BiteWriter* writer = biteWriterCreate(out);
	int i, j;

	int* freq = calloc(256, sizeof(int));
	while (!feof(in)) {
		freq[(unsigned char)fgetc(in)]++;
	}
	freq[255] = 0;  /*EOF*/

	Node** leaves = (Node**)calloc(256, sizeof(Node*)); /* char-ended leaves for navigation.*/
	PriorQueue* queue = priorQueueCreate(256);
	for (i = 0; i < 256; i++) {
		if (freq[i]) {
			alphabetSize++;
			leaves[i] = createEncodeNode();
			priorQueueInsert(queue, leaves[i], freq[i]);
		}
	}
	if (alphabetSize == 0) {
		exit;
	}
	if (alphabetSize == 1) {
		biteWriterEnqueue(writer, 8, 1); /* AlphabetSize*/
		for (i = 0; i < 256; i++) {
			if (freq[i] != 0) {
				break;
			}
		}
		biteWriterEnqueue(writer, 8, i); /* Char*/
		biteWriterEnqueue(writer, 8, 1); /* Code length*/
		biteWriterEnqueue(writer, 1, 1); /* Code*/
		codeLength = (8 + 8 + 8 + 1 + 3 + freq[i]) % 8;
		biteWriterEnqueue(writer, 3, (8 - codeLength) % 8); /* Number of fakes*/
		biteWriterEnqueue(writer, (8 - codeLength) % 8, 0); /* Fakes*/
		for (j = 0; j < freq[i]; j++) {
			biteWriterEnqueue(writer, 1, 1);
		}
		exit;
	}
#pragma region Coding tree building
	Node* newNode;
	Node* left;
	Node* right;
	int newKey;

	while (!priorQueueIsEmpty(queue)) {
		newKey = 0;
		newKey += priorQueueGetMinKey(queue);
		left = priorQueueExtractMin(queue);
		newKey += priorQueueGetMinKey(queue);
		right = priorQueueExtractMin(queue);
		if (right) {
			newNode = createEncodeNode();
			left->parent = newNode;
			left->sgn = 0;
			right->parent = newNode;
			right->sgn = 1;
			priorQueueInsert(queue, newNode, newKey);
		}
	}
	priorQueueDestroy(queue);
#pragma endregion

#pragma region Coding tree serialization
	Node* buf;
	biteWriterEnqueue(writer, 8, alphabetSize); /* Number of encoded chars (byte 1-256)*/
	int length;
	Stack* stack = stackCreate();
	for (i = 0; i < 256; i++) {
		if (freq[i] != 0) {
			length = 0;
			buf = leaves[i];
			while (buf->parent) {
				stackPush(stack, buf);
				buf = buf->parent;
				length++;
			}
			codeLength = (codeLength + (length * freq[i]) % 8) % 8;
			biteWriterEnqueue(writer, 8, i); /* Char*/
			biteWriterEnqueue(writer, 8, length); /* Code length*/
			while (!stackIsEmpty(stack)) {
				buf = (Node*)stackPop(stack);
				biteWriterEnqueue(writer, 1, buf->sgn); /* Code*/
			}
		}
	}
#pragma endregion
	codeLength = (codeLength + 3 + writer->bitesN) % 8;
	biteWriterEnqueue(writer, 3, (8 - codeLength) % 8); /* Number of fakes*/
	biteWriterEnqueue(writer, (8 - codeLength) % 8, 0); /* Fakes*/

#pragma region Encoded text
	fseek(in, fileStart, SEEK_SET);
	Stack* bites = stackCreate();
	Node* biteGenerator;
	unsigned char fileChr;
	unsigned char generatedChr;
	char bitesN = 0; /* Counter of bites in stack;*/
	short digit; /* For generating char;*/
	while (1) {
		fileChr = fgetc(in);
		if (255 == fileChr) { /*EOF*/
			break;
		}
		buf = leaves[fileChr];
		while (buf->parent) {
			stackPush(stack, buf);
			buf = buf->parent;
		}
		while (!stackIsEmpty(stack)) {
			buf = (Node*)stackPop(stack);
			biteWriterEnqueue(writer, 1, buf->sgn);
		}
	}
#pragma endregion

	exit;
}