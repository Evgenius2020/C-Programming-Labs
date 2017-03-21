#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

void printHelp() {
	printf("base64.exe -e sourceFileName outputFileName - encoding.\n");
	printf("base64.exe -e -f{linesize} sourceFileName outputFileName - encoding with fixed line size.\n");
	printf("base64.exe -d sourceFileName outputFileName - decoding.\n");
	printf("base64.exe -d -i sourceFileName outputFileName - encoding with ignoring unknown symbols.\n");
}

int checkFormatFlag(char* flag) {
	if (flag[0] == '-') {
		if (flag[1] == 'f') {
			for (int i = 2; i < strlen(flag); i++) {
				if ((flag[i] < '0') || (flag[i] > '9')) {
					return 0;
				}
			}
			return 1;
		}
	}
	return 0;
}

void main(int argc, char* argv[]) {
	if (argc >= 4) {
		if (!strcmp(argv[1], "-e")) {
			if (argc == 4) {
				if (encode(argv[2], argv[3], 0) == SUCCESS) {
					printf("Completely encoded!");
				}
				else {
					printf("Encoding failure!");
				}
				return;
			}
			if (argc == 5) {
				if (checkFormatFlag(argv[2])) {
					if (encode(argv[3], argv[4], atoi(argv[2] + 2)) == SUCCESS) {
						printf("Completely encoded!");
					}
					else {
						printf("Encoding failure!");
					}
					return;
				}
			}
		}
		if (!strcmp(argv[1], "-d")) {
			if (argc == 4) {
				if (decode(argv[2], argv[3], NORMAL_DECODE_MODE) == SUCCESS) {
					printf("Completely decoded!");
				}
				else {
					printf("Failure! Decoding has been stoped!");
				}
				return;
			}
			if (argc == 5) {
				if (!strcmp(argv[2], "-i")) {
					if (decode(argv[2], argv[3], IGNORE_DECODE_MODE) == SUCCESS) {
						printf("Completely decoded!");
					}
					else {
						printf("Failure! Decoding has been stoped!");
					}
					return;
				}
			}
		}
	}

	printHelp();
}