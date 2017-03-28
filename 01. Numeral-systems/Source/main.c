#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define exit fclose(in); fclose(out); return 0
#define isBetween(left, valuable, right) ((left <= valuable) && (valuable <= right))
#define MIN_SN 2
#define MAX_SN 16
#define MAX_STRLEN 60

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
	} while ((intPart) && (i < MAX_STRLEN - 1));
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

char checkValidation(char* str, char base) {
	char strIndex;
	char digitsAtFloat = 0; /* Flags of correct input */
	char digitsAtInt = 0;
	char points = 0;
	for (strIndex = 0; strIndex < strlen(str); strIndex++) {
		if (str[strIndex] == '.') {
			points++;
			continue;
		}
		str[strIndex] = getLowerCase(str[strIndex]);
		if (isBetween(getCode(0), getCode(str[strIndex]), base - 1)) {
			if (!points) {
				digitsAtInt++;
			}
			else {
				digitsAtFloat++;
			}
			continue;
		}
		
		return 0;
	}
	if (points >= 2) {
		return 0;
	}
	if ((!digitsAtInt) || ((points) && (!digitsAtFloat))) {
		return 0;
	}

	return 1;
}

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	if ((!in) || (!out)) {
		return;
	}

	int b1, b2; /* Numeral systems numbers */
	char* b1Val = (char*)malloc(sizeof(char)*MAX_STRLEN);
	char* b2Val;
	fscanf(in, "%d %d ", &b1, &b2);
	if (!(isBetween(MIN_SN, b1, MAX_SN)) || !(isBetween(MIN_SN, b2, MAX_SN))) {
		fprintf(out, "bad input\n");
	}
	else {
		fscanf(in, "%s ", b1Val);
		if (checkValidation(b1Val, b1)) {
			b2Val = decToStr(strToDec(b1Val, b1), b2);
			fprintf(out, "%s", b2Val);
			free(b2Val);
		}
		else {
			fprintf(out, "bad input\n");
		}
	}

	free(b1Val);
	fclose(in);
	fclose(out);
}