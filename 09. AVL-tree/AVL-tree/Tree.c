#include <stdlib.h>
#include <stdio.h>
#include "Tree.h";
#include "Tree_Rotations.h";

Node* createNode(int value) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	node->value = value;
	node->height = 1;
	return node;
}

Node* insertNode(Node* root, Node* node) {
	if (!root) {
		return NULL;
	}

	if (node->value >= root->value) {
		if (!root->right) {
			root->right = node;
		}
		else {
			root->right = insertNode(root->right, node);
		}
	}
	else {
		if (!root->left) {
			root->left = node;
		}
		else {
			root->left = insertNode(root->left, node);
		}
	}

	if (getBalanceFactor(root) <= -2) {
		if (getBalanceFactor(root->right) < 0) {
			root = smallLeftRotation(root);
		}
		else {
			root = bigLeftRotation(root);
		}
	}
	else if (getBalanceFactor(root) >= 2) {
		if (getBalanceFactor(root->left) >= 0 ) {
			root = smallRightRotation(root);
		}
		else {
			root = bigRightRotation(root);
		}
	}

	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	return root;
}

void destroyTree(Node* root) {
	if (!root) {
		return;
	}
	if (root->left) {
		destroyTree(root->left);
		root->left = NULL;
	}
	if (root->right) {
		destroyTree(root->right);
		root->right = NULL;
	}

	free(root);
}

void printTree(Node* root) {
	if (!root) {
		return;
	}
	printf("val:%d h:%d ", root->value, root->height);
	if (root->left) {
		printf("L:%d ", root->left->value);
	}
	if (root->right) {
		printf("R:%d ", root->right->value);
	}
	printf("\n");

	printTree(root->left);
	printTree(root->right);
}