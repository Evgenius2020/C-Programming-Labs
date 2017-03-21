#ifndef TREE
#define TREE

#define getHeight(n) ((n == NULL) ? 0 : n->height)
#define getBalanceFactor(root) ((getHeight(root->left) - getHeight(root->right)))

typedef struct Node {
	int value;
	unsigned char height;
	struct Node* left;
	struct Node* right;
} Node;

// New node constructor.
Node* createNode(int val);

// Inserts node, balances up-level roots and sets heights for them.
Node* insertNode(Node* root, Node* node);

// Recursive destroying all nodes of tree.
void destroyTree(Node* root);

// Prints nodes in format value-height-leftValue-rightValue.
void printTree(Node* root);	
#endif