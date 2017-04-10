#include <stdlib.h>
#include <string.h>
#include "BiteWriter.h"
#include "CodingTree.h"
#include "PriorityQueue.h"

#define NO_NAME 0

Node* createNode(unsigned char name) {
	Node* node = malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	node->name = name;

	return node;
}

void destroyTree(Node* node) {
	if (node) {
		destroyTree(node->left);
		destroyTree(node->right);
		free(node);
	}
}

Node* buildCodingTree(int* freq) {
	short i;
	PriorQueue* priorQueue = priorQueueCreate(256);

	for (i = 0; i < 256; i++) {
		if (freq[i]) {
			priorQueueInsert(priorQueue, createNode(i), freq[i], NULL);
		}
	}

	Node *newNode, *left, *right;
	short newKey;
	while (1) {
		newKey = priorQueueGetMinKey(priorQueue);
		left = priorQueueExtractMin(priorQueue);
		newKey += priorQueueGetMinKey(priorQueue);
		right = priorQueueExtractMin(priorQueue);
		if (!left) {
			return NULL;
		}
		if (!right) {
			return left;
		}
		newNode = createNode(NO_NAME);
		newNode->left = left;
		newNode->right = right;
		priorQueueInsert(priorQueue, newNode, newKey, NULL);
	}
}

/* Searches codes in tree */
void searchCodes(Node* root, char** codes, char* currCode, short currPos) {
	if (!(root->left) && !(root->right)) {
		currCode[currPos] = '\0';
		codes[root->name] = malloc(sizeof(char) * strlen(currCode));
		strcpy(codes[root->name], currCode);
		return;
	}
	currCode[currPos] = '0';
	searchCodes(root->left, codes, currCode, currPos + 1);
	currCode[currPos] = '1';
	searchCodes(root->right, codes, currCode, currPos + 1);
}

/* Generates table of codes */
char** generateCodes(Node* root) {
	char** codes = calloc(256, sizeof(char*));
	char* codeBuf = malloc(sizeof(char) * 256);
	searchCodes(root, codes, codeBuf, 0);
	free(codeBuf);
	return codes;
}

void serializeCodingTree(BiteWriter* writer, Node* root) {
	if (!(root->left) && !(root->right)) {
		biteWriterEnqueue(writer, 1, 1);
		biteWriterEnqueue(writer, 8, root->name);
		return;
	}
	biteWriterEnqueue(writer, 1, 0);
	serializeCodingTree(writer, root->left);
	serializeCodingTree(writer, root->right);
}