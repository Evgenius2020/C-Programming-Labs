#include <stdio.h>
#include "../../Common/Stacks/Stack-int/Source/Stack.c"

#define exit fclose(in); fclose(out); return 0

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

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	Stack* numbers = stackCreate();
	Stack* signs = stackCreate();

	char curr;
	int numCollector = -1;
	int left, right;
	char braskets = 0;
	char emptyBrasketsFlag = 1;
	while (!feof(in)) {
		curr = fgetc(in);

		if (curr != ')') {
			if (emptyBrasketsFlag) {
				emptyBrasketsFlag = 0;
			}
		}

#pragma region numbers
		if ((curr >= '0') && (curr <= '9')) {
			if (numCollector == -1) {
				numCollector = curr - '0';
			}
			else {
				numCollector = numCollector * 10 + curr - '0';
			}
			continue;
		}
		if (getPrior(curr) == -1) {
			fprintf(out, "syntax error\n");
			exit;
		}
		if (numCollector != -1) {
			stackPush(numbers, numCollector);
			numCollector = -1;
		}
#pragma endregion

		if (curr == '(') {
			braskets++;
			emptyBrasketsFlag = 1;
			stackPush(signs, '(');
			continue;
		}

		if (curr == ')') {
			if (braskets == 0) {
				fprintf(out, "syntax error\n");
				exit;
			}
			if (emptyBrasketsFlag) {
				fprintf(out, "syntax error\n");
				exit;
			}
		}

		while (!stackIsEmpty(signs) && (getPrior(curr) <= getPrior(stackPeek(signs)))) {
			if (stackPeek(signs) == '(') {
				braskets--;
				stackPop(signs);
				break;
			}
			if (stackIsEmpty(numbers)) {
				fprintf(out, "syntax error\n");
				exit;
			}
			right = stackPop(numbers);
			if (stackIsEmpty(numbers)) {
				fprintf(out, "syntax error\n");
				exit;
			}
			left = stackPop(numbers);
			switch (stackPeek(signs)) {
			case '-': {
				stackPush(numbers, left - right);
				break;
			}
			case '+': {
				stackPush(numbers, left + right);
				break;
			}
			case '*': {
				stackPush(numbers, left * right);
				break;
			}
			case '/': {
				if (right == 0) {
					fprintf(out, "division by zero\n");
					exit;
				}
				stackPush(numbers, left / right);
				break;
			}
			}
			stackPop(signs);
		}
		if ((curr != ')') && (curr != EOF) && (curr != '\n')) {
			stackPush(signs, curr);
		}
	}

	if (braskets != 0) {
		fprintf(out, "syntax error\n");
		exit;
	}

	if (!stackIsEmpty(signs)) {
		fprintf(out, "syntax error\n");
	}
	else {
		if (stackIsEmpty(numbers)) {
			fprintf(out, "syntax error\n");
		}
		else {
			fprintf(out, "%d", stackPop(numbers));
		}
	}
	exit;
}