#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Common/Stacks/Stack-int/Source/Stack.c"

#define MAX_STRLEN 1024
#define isNumber(val) (('0' <= val) && (val <= '9'))
#define isSign(val) ((val == '(') || (val == ')') || (val =='+') || (val == '-') || (val == '*') || (val == '/'))

#define VALIDATION_RIGHT 1
#define VALIDATION_SYNTAX_ERROR 2
#define VALIDATION_DIVISION_BY_ZERO 3

char checkValidation(char* expression) {
	short i;
	char curr;
	short brackets = 0; /* (1 + 3)) */
	char emptyBracketsFlag = 0; /* 1 + 3() */
	char divisionFlag = 0;
	for (i = 0; i < strlen(expression); i++) {
		curr = expression[i];
		if (isSign(curr)) {
			if (curr == '(') {
				brackets++;
				emptyBracketsFlag = 1;
				continue;
			}
			if (curr == ')') {
				if ((brackets) && (!emptyBracketsFlag)) {
					brackets--;
					continue;
				}
				return VALIDATION_SYNTAX_ERROR;
			}
			if (curr == '/') {
				divisionFlag = 1;
			}
			continue;
		}

		if (isNumber(curr)) {
			if ((divisionFlag) && (curr == '0')) {
				return VALIDATION_DIVISION_BY_ZERO;
			}
			emptyBracketsFlag = 0;
			divisionFlag = 0;
			continue;
		}

		return VALIDATION_SYNTAX_ERROR; /* Wrong symbol */
	}

	if (brackets) {
		return VALIDATION_SYNTAX_ERROR;
	}

	return VALIDATION_RIGHT;
}

char getPrior(char chr) {
	if ((chr == '+') || (chr == '-')) {
		return 2;
	}
	if ((chr == '*') || (chr == '/')) {
		return 3;
	}
	if ((chr == '(') || (chr == ')')) {
		return 1;
	}
	if ((-1 == chr) || (chr == '\n')) {
		return 0;
	}

	return -1;
}

int calculate(int left, char sign, int right) {
	switch (sign) {
	case '+': {
		return left + right;
	}
	case '-': {
		return left - right;
	}
	case '*': {
		return left * right;
	}
	case '/': {
		if (right != 0) {
			return left / right;
		}
	}
	}
	return 0;
}

int execute(char* expression) {
	Stack* signs = stackCreate();
	Stack* numbers = stackCreate();

	int numberCollector = 0;
	char numberCollectingFlag = 0;
	short i;
	char curr;
	int left, right;
	for (i = 0; i < strlen(expression); i++) {
		curr = expression[i];
		if (isNumber(curr)) {
			if (!numberCollectingFlag) {
				numberCollectingFlag = 1;
			}
			numberCollector *= 10;
			numberCollector += curr - '0';
			continue;
		}
		if (isSign(curr)) {
			if (numberCollectingFlag) {
				stackPush(numbers, numberCollector);
				numberCollector = 0;
				numberCollectingFlag = 0;
			}
			while ((!stackIsEmpty(signs)) && (getPrior(stackPeek(signs)) >= getPrior(curr))) {
				if (stackPeek(signs) == '(') {
					stackPop(signs);
					break;
				}
				right = stackPop(numbers);
				left = stackPop(numbers);
				stackPush(numbers, calculate(left, stackPeek(signs), right));
				stackPop(signs);
			}
			if (curr != ')') {
				stackPush(signs, curr);
			}
		}
	}

	if (numberCollectingFlag) {
		stackPush(numbers, numberCollector);
	}
	while (!stackIsEmpty(signs)) {
		right = stackPop(numbers);
		left = stackPop(numbers);
		stackPush(numbers, calculate(left, stackPeek(signs), right));
		stackPop(signs);
	}
	
	int result = stackPeek(numbers);
	stackDestroy(signs);
	stackDestroy(numbers);
	return result;
}

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	if ((!in) || (!out)) {
		return;
	}

	char* expression = (char*)malloc(MAX_STRLEN * sizeof(char));
	fscanf(in, "%s ", expression);
	switch (checkValidation(expression)) {
	case VALIDATION_RIGHT: {
		fprintf(out, "%d\n", execute(expression));
		break;
	}
	case VALIDATION_SYNTAX_ERROR: {
		fprintf(out, "syntax error\n");
		break;
	}
	case VALIDATION_DIVISION_BY_ZERO: {
		fprintf(out, "division by zero\n");
		break;
	}
	}

	free(expression);
	fclose(in);
	fclose(out);
	return;
}