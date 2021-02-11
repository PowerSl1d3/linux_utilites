#include "lib.h"

int stringstat(const char* string, size_t multiplier, int* count) {
	
	size_t size = 0;

	while (*string++)
			size++;
	(*count)++;

	return size * multiplier;

}
