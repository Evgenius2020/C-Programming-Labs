#ifndef ENCODING
#define ENCODING

/*
 Output format:
	Coding tree build commands:
		'0' - go to left node
		  or
		'1' + char - name node by 'char'
	Number of fakes (3 bits 0-7)
	Fake bits
	Encoded text
*/
void encode(FILE* in, FILE* out);

#endif