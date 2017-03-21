#include <stdlib.h>
#include "Tree.h"

Node* smallLeftRotation(Node* root) {
	Node* tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;

	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

	return tmp;
}

Node* smallRightRotation(Node* root) {
	Node* tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;

	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

	return tmp;
}

Node* bigLeftRotation(Node* root) {
	root->right = smallRightRotation(root->right);

	return smallLeftRotation(root);
}

Node* bigRightRotation(Node* root) {
	root->left = smallLeftRotation(root->left);

	return smallRightRotation(root);
}