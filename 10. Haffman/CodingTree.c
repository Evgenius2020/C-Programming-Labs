#include <stdlib.h>

#define NO_NAME 0;

typedef struct Node {
	struct Node* left;
	struct Node* right;
	unsigned char name;
} Node;

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

Node* buildCodeTree(int* freq) {
	Node* root;
	short i;
	Prior

	for (i = 0; i < 256; i++) {
		if (freq[i]) {
			priorQueueInsert(queue, createNode(i), freq[i]);
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
	return root;
}