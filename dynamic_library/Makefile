build: lib lib.h main.c
	gcc main.c -o solution -L. -fPIC -lsolution
lib: lib.h lib.c
	gcc lib.c -o libsolution.so -shared -fPIC
clear:
	-rm solution
