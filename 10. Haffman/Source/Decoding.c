#include <stdio.h>
#include <stdlib.h>
#include "CodingTree.h"
#include "Decoding.h"
#include "BitReader.h"

void regainText(BitReader* bitReader, Node* root, FILE* out) {
	Node* buf = root;
	unsigned char bite;

	while (1) {
		bite = bitReaderDequeue(bitReader, 1);
		if (bitReader->eofFlag) {
			break;
		}
		if ((bite) && (buf->right)) {
			buf = buf->right;
		}
		if ((!bite) && (buf->left)) {
			buf = buf->left;
		}
		if (!(buf->left) && !(buf->right)) { /* Readed full code word */
			fputc(buf->name, out);
			buf = root;
		}
	}
}

void decode(FILE* in, FILE* out) {
	BitReader* bitReader = bitReaderCreate(in);

	Node* codingTreeRoot = deserializeCodingTree(bitReader); /* Coding tree */
	if (bitReader->eofFlag) { /* 'EOF' on tree deserialization (empty text) */
		return;
	}
	bitReaderDequeue(bitReader, bitReaderDequeue(bitReader, 3)); /* Skips fakes.*/
	regainText(bitReader, codingTreeRoot, out); /* Encoded text */

	destroyTree(codingTreeRoot);
	bitReaderDestroy(bitReader);
}