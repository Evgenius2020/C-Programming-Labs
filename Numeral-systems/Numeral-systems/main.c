#include <stdio.h>
#include <stdlib.h>

#define exit fclose(in); fclose(out); return 0
#define isBetween(left, valuable, right) ((left <= valuable) && (valuable <= right))
#define MIN_SN 2
#define MAX_SN 16
#define MAX_STRLEN 16

int getCode(char chr) {
	return (chr >= 'a') ? (chr - 'a' + 10) : (chr - '0');
}

char getChar(int val) {
	return (val >= 10) ? ('a' + val - 10) : ('0' + val);
}

char getLowerCase(char chr) {
	if (isBetween(0, chr - 'A', 9)) {
		return 'a' + chr - 'A';
	}
	return chr;
}

double strToDec(char* str, char ns) {
	char i = 0;
	double result = 0;
	double mul = 1;
	while (str[i] != '\0') {
		result *= ns;
		result += getCode(str[i++]);
		if (str[i] == '.') {
			i++;
			while (str[i] != '\0') {
				mul /= ns;
				result += getCode(str[i++]) * mul;
			}
		}
	}

	return result;
}

char* decToStr(double dec, char ns) {
	char* result = (char*)malloc(sizeof(char) * MAX_STRLEN);
	char i = 0;
	long long intPart = dec;
	do {
		result[i++] = getChar(intPart % ns);
		intPart /= ns;
	} while (intPart);
	char j;
	for (j = 0; j < i / 2; j++) {
		result[j] += result[i - j - 1];
		result[i - j - 1] = result[j] - result[i - j - 1];
		result[j] -= result[i - j - 1];
	}

	double floatPart = dec - (long long)dec;
	if (floatPart) {
		result[i++] = '.';
	}
	while ((floatPart) && (i < MAX_STRLEN - 1)) {
		floatPart = floatPart* ns;
		result[i++] = getChar(floatPart);
		floatPart -= (long long)floatPart;
	}

	result[i] = '\0';

	return result;
}

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	int b1, b2; /* Numeral systems numbers */
	fscanf(in, "%d %d ", &b1, &b2);
	if ((!isBetween(MIN_SN, b1, MAX_SN)) || (!isBetween(MIN_SN, b2, MAX_SN))) {
		fprintf(out, "bad input\n");
		exit;
	}

	char chr;
	char b1Val[MAX_STRLEN];
	char i = 0;
	char digitsAtFloat = -1; /* Flags of correct input */
	char digitsAtInt = 0;
	while (1) {
		if ((-1 == fscanf(in, "%c", &chr)) || (chr == '\n')) {
			break;
		}
		chr = getLowerCase(chr);
		if ((!(chr == '.')) && (!isBetween(0, getCode(chr), b1 - 1))) {
			fprintf(out, "bad input\n");
			exit;
		}
		if ((digitsAtFloat == 0) && (chr != '.')) {
			digitsAtFloat = 1;
		}
		if (chr == '.') {
			if ((digitsAtInt == 0) || (digitsAtFloat == 0)) {
				break;
			}
			digitsAtFloat = 0;
		}
		else {
			digitsAtInt = 1;
		}
		b1Val[i++] = chr;
	}
	b1Val[i] = '\0';
	if ((digitsAtFloat == 0) || (digitsAtInt == 0)) {
		fprintf(out, "bad input\n");
		exit;
	}

	fprintf(out, "%s", decToStr(strToDec(b1Val, b1), b2));

	exit;
}