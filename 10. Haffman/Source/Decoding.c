#include <stdio.h>
#include <stdlib.h>
#include "Decoding.h"
#include "BiteReader.h"

#define exit() return

typedef struct DecodeNode {
	struct DecodeNode* left;
	struct DecodeNode* right;
	char chr;
} DecodeNode;

DecodeNode* createDecodeNode() {
	DecodeNode* node = (DecodeNode*)malloc(sizeof(DecodeNode));
	node->chr = 0;
	node->left = NULL;
	node->right = NULL;

	return node;
}

/* Reading code of tree from the file, generates coding tree */
DecodeNode* generateTree(BiteReader* reader, unsigned char encodedChars) {
	DecodeNode* root = createDecodeNode();
	DecodeNode* buf;
	unsigned char chr, codeLength, bite;
	while(encodedChars--) {
		buf = root;
		chr = biteReaderDequeue(reader, 8);
		codeLength = biteReaderDequeue(reader, 8);
		while (codeLength--) {
			bite = biteReaderDequeue(reader, 1);
			if (bite) {
				if (!buf->right) {
					buf->right = createDecodeNode();
				}
				buf = buf->right;
			}
			else {
				if (!buf->left) {
					buf->left = createDecodeNode();
				}
				buf = buf->left;
			}
		}
		buf->chr = chr;
	}

	return root;
}

void regainText(BiteReader* reader, DecodeNode* root, FILE* out) {
	DecodeNode* buf = root;
	char bite;

	while (1) {
		bite = biteReaderDequeue(reader, 1);
		if (reader->eofFlag) {
			break;
		}
		if (bite) {
			buf = buf->right;
		}
		else {
			buf = buf->left;
		}
		if (!(buf->left) && !(buf->right)) { /* Readed full code word */
			fputc(buf->chr, out);
			buf = root;
		}
	}
}

void decode(FILE* in, FILE* out) {
	BiteReader* reader = biteReaderCreate(in);

	unsigned char encodedChars = biteReaderDequeue(reader, 8); /* Alphabet size */
	DecodeNode* root = generateTree(reader, encodedChars); /* Coding tree */
	biteReaderDequeue(reader, biteReaderDequeue(reader, 3)); /* Skips fakes.*/
	regainText(reader, root, out); /* Encoded text */
}