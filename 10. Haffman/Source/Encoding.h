#ifndef ENCODING
#define ENCODING

/*
 Output format:
 Number of encoded chars (byte 1-256)
 Codes:
 Char - Code length (byte) - Code (n bits)
 Char - Code length (byte) - Code (n bits)
 ...
 Number of fakes
 Fake bits
 Encoded text
 EOF
*/
void encode(char* inputFileName, char* outputFileName);

#endif