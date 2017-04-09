#ifndef ENCODING
#define ENCODING

/*
 Output format:
	Encoded chars mask (256 bits) 
	Codes:
		Code length (byte) - Code (n bits)
		Code length (byte) - Code (n bits)
		...
	Number of fakes (3 bits 0-7)
	Fake bits
	Encoded text
*/
void encode(FILE* in, FILE* out);

#endif