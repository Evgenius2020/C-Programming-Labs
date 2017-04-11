#ifndef CODING_TREE
#define CODING_TREE

#include "BiteWriter.h"
#include "BiteReader.h"

typedef struct Node {
	struct Node* left;
	struct Node* right;
	unsigned char name;
} Node;

Node* createNode(unsigned char name);

void destroyTree(Node* node);

Node* buildCodingTree(int* freq);

char** generateCodes(Node* root);

void serializeCodingTree(BiteWriter* writer, Node* root);

Node* deserializeCodingTree(BiteReader* reader);

#endif