#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

#define MAX_STRLEN 1024
#define isNumber(val) (('0' <= val) && (val <= '9'))
#define isSign(val) ((val == '(') || (val == ')') || (val =='+') || (val == '-') || (val == '*') || (val == '/'))

typedef struct ExecutionResult {
	char statusCode;
	int result;
}ExecutionResult;

char checkValidation(char* expression) {
	short i;
	char curr;
	short brackets = 0; /* (1 + 3)) */
	char emptyBracketsFlag = 0; /* 1 + 3() */
	char leftOperandFlag = 0;
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
				return 0;
			}
			if (!leftOperandFlag) {
				return 0;
			}
			leftOperandFlag = 0;
			continue;
		}

		if (isNumber(curr)) {
			leftOperandFlag = 1;
			emptyBracketsFlag = 0;
			continue;
		}

		return 0; /* Wrong symbol */
	}

	if (brackets) {
		return 0;
	}
	if (!leftOperandFlag) {
		return 0;
	}

	return 1;
}

char getPrior(char chr) {
	if ((chr == '+') || (chr == '-')) {
		return 2;
	}
	if ((chr == '*') || (chr == '/')) {
		return 3;
	}
	if (chr == '(') {
		return 1;
	}
	if ((chr == ')')) {
		return 1;
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

char* normalizeString(char* str) {
	if (str[strlen(str) - 1] == '\n') {
		str[strlen(str) - 1] = '\0';
	}

	return str;
}

ExecutionResult execute(char* expression) {
	ExecutionResult result;
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
			if (curr == '(') {
				stackPush(signs, '(');
				continue;
			}
			while ((!stackIsEmpty(signs)) && (getPrior(curr) <= getPrior(stackPeek(signs)))) {
				if (stackPeek(signs) == '(') {
					stackPop(signs);
					break;
				}
				right = stackPop(numbers);
				left = stackPop(numbers);
				if ((right == 0) && (stackPeek(signs) == '/')) {
					result.statusCode = 0;
					return result;
				}
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
		if ((right == 0) && (stackPeek(signs) == '/')) {
			result.statusCode = 0;
			return result;
		}
		stackPush(numbers, calculate(left, stackPeek(signs), right));
		stackPop(signs);
	}

	result.result = stackPop(numbers);
	result.statusCode = 1;
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
	fgets(expression, MAX_STRLEN, in);
	expression = normalizeString(expression);
	ExecutionResult result;
	if (checkValidation(expression)) {
		result = execute(expression);
		if (result.statusCode) {
			fprintf(out, "%d\n", result.result);
		}
		else {
			fprintf(out, "division by zero\n");
		}
	}
	else {
		fprintf(out, "syntax error\n");
	}
	free(expression);
	fclose(in);
	fclose(out);
	return;
}