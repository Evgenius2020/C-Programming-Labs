#include <string.h>
#include "Row.h"

#define NUMCMP(left, right, fieldname) return (left->##fieldname == right->##fieldname) ? 0 : ((left->##fieldname < right->##fieldname) ? -1 : 1)

int ageCmp(Row* left, Row* right) {
	NUMCMP(left, right, age);
}
int markCmp(Row* left, Row* right) {
	NUMCMP(left, right, mark);
}
int groupCmp(Row* left, Row* right) {
	NUMCMP(left, right, groupId);
}

int nameCmp(Row* left, Row* right) {
	return strcmp(left->name, right->name);
}