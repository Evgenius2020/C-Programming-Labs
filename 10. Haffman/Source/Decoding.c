#include <stdio.h>
#include <stdlib.h>
#include "CodingTree.h"
#include "Decoding.h"
#include "BiteReader.h"

void regainText(BiteReader* reader, Node* root, FILE* out) {
	Node* buf = root;
	unsigned char bite;

	while (1) {
		bite = biteReaderDequeue(reader, 1);
		if (reader->eofFlag) {
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
	BiteReader* reader = biteReaderCreate(in);

	Node* codingTreeRoot = deserializeCodingTree(reader); /* Coding tree */
	if (reader->eofFlag) { /* 'EOF' on tree deserialization (empty text) */
		return;
	}
	biteReaderDequeue(reader, biteReaderDequeue(reader, 3)); /* Skips fakes.*/
	regainText(reader, codingTreeRoot, out); /* Encoded text */

	destroyTree(codingTreeRoot);
	biteReaderDestroy(reader);
}