#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <dlfcn.h>
#include <stdlib.h>

int (*f)(int);

bool init_library(const char* lib, const char* func) {

	void* handle = dlopen(lib, RTLD_LAZY);

	if ( NULL == handle ) {
		printf("Cant link library %s\n", lib);
		return false;
	}

	f = (int (*)(int))dlsym(handle, func);

	if ( NULL == f ) {
		printf("Cant get function %s\n", func);
		return false;
	}

	return true;

}

int main(int argc, char* argv[]) {

	if (init_library(argv[1], argv[2])) {

		printf("%d\n", f(atoi(argv[3])));

	} else {
		printf("Library was not connected\n");
	}

	return 0;

}
