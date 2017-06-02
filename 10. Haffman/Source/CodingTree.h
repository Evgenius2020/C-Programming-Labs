#ifndef CODING_TREE
#define CODING_TREE

#include "BitWriter.h"
#include "BitReader.h"

typedef struct Node {
	struct Node* left;
	struct Node* right;
	unsigned char name;
} Node;

Node* createNode(unsigned char name);

void destroyTree(Node* node);

Node* buildCodingTree(int* freq);

char** generateCodes(Node* root);

void serializeCodingTree(BitWriter* bitWriter, Node* root);

Node* deserializeCodingTree(BitReader* bitReader);

#endif