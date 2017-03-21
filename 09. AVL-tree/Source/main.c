#include <stdio.h>
#include <stdlib.h>
#include "Tree.h";

void main() {
	FILE* input = fopen("in.txt", "r");
	FILE* output = fopen("out.txt", "w");

	int nodes;
	fscanf(input, "%d ", &nodes);
	Node* root;
	int newNodeVal, i;

	if (nodes) {
		fscanf(input, "%d ", &newNodeVal);
		root = createNode(newNodeVal);
		for (i = 0; i < nodes - 1; i++) {
			fscanf(input, "%d ", &newNodeVal);
			root = insertNode(root, createNode(newNodeVal));
		}

		fprintf(output, "%d", getHeight(root));

		destroyTree(root);
	}
	else {
		fprintf(output, "0");
	}

	fclose(input);
	fclose(output);
}