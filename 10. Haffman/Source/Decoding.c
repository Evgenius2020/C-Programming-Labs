#include <stdio.h>
#include <stdlib.h>
#include "Decoding.h"
#include "BiteReader.h"

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
DecodeNode* generateTree(BiteReader* reader, char* mask) {
	DecodeNode* root = createDecodeNode();
	DecodeNode* buf;
	unsigned char codeLength, bite;
	short i;
	for (i = 0; i < 256; i++) {
		if (mask[i]) {
			buf = root;
			codeLength = biteReaderDequeue(reader, 8); /* Code length*/
			while (codeLength--) { /* Code */
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
			buf->chr = i;
		}
	}

	return root;
}

void regainText(BiteReader* reader, DecodeNode* root, FILE* out) {
	DecodeNode* buf = root;
	unsigned char bite;

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

char* readMask(BiteReader* reader) {
	char* mask = calloc(256, sizeof(char));
	short i;
	for (i = 0; i < 256; i++) {
		mask[i] = biteReaderDequeue(reader, 1);
	}

	return mask;
}

void decode(FILE* in, FILE* out) {
	BiteReader* reader = biteReaderCreate(in);

	char* mask = readMask(reader); /* Encoded chars mask */
	DecodeNode* root = generateTree(reader, mask); /* Coding tree */
	biteReaderDequeue(reader, biteReaderDequeue(reader, 3)); /* Skips fakes.*/
	regainText(reader, root, out); /* Encoded text */

	free(mask);
	biteReaderDestroy(reader);
}