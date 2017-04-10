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

	char alphabetSize = biteReaderDequeue(reader, 8); /* Alphabet size */
	if (reader->eofFlag) { /* Empty text */
		biteReaderDestroy(reader);
		return;
	}
	Node* codingTreeRoot = deserializeCodingTree(reader); /* Coding tree */
	biteReaderDequeue(reader, biteReaderDequeue(reader, 3)); /* Skips fakes.*/
	regainText(reader, codingTreeRoot, out); /* Encoded text */

	destroyTree(codingTreeRoot);
	biteReaderDestroy(reader);
}