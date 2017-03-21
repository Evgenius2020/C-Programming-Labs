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

void decode(FILE* in, FILE* out) {
	BiteReader* reader = biteReaderCreate(in);
	unsigned char encodedChars = biteReaderDequeue(reader, 8);
	int i, j;
	char bite;
	DecodeNode* root = createDecodeNode();
	DecodeNode* buf;

#pragma region Tree generation
	char chr, codeLength;
	for (i = 0; i < encodedChars; i++) {
		buf = root;
		chr = biteReaderDequeue(reader, 8);
		codeLength = biteReaderDequeue(reader, 8);
		for (j = 0; j < codeLength; j++) {
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
#pragma endregion

	biteReaderDequeue(reader, biteReaderDequeue(reader, 3)); /* Skips fakes.*/
	bite = biteReaderDequeue(reader, 1);
	if (reader->eofFlag) {
		exit();
	}
	buf = root;
	while (1) {	
		if (bite) {
			buf = buf->right;
		} else {
			buf = buf->left;
		}
		if (!(buf->left) && !(buf->right)) {
			fputc(buf->chr, out);
			buf = root;
		}
		bite = biteReaderDequeue(reader, 1);
		if (reader->eofFlag) {
			exit();
		}
	}
}