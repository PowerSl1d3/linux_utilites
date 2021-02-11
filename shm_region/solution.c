#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int first_region = shmget(atoll(argv[1]), 1000, IPC_CREAT | 0600 );
	int* sh_first = (int*)shmat(first_region, NULL, SHM_RDONLY );

	int second_region = shmget(atoll(argv[2]), 1000, IPC_CREAT | 0600 );
	int* sh_second =  (int*)shmat(second_region, NULL, SHM_RDONLY );

	key_t key = ftok(argv[0], 0);
	int my_region = shmget(key, 1000, IPC_CREAT | 0660 );
	int* shared_memory = (int*)shmat(my_region, NULL, 0 );

	int i = 0;
	while(i < 1000) {

		shared_memory[i] = sh_first[i] + sh_second[i];
		++i;
	}

	printf("%d\n", key);
	
	shmdt(sh_first);
	shmdt(sh_second);
	shmdt(shared_memory);

	return 0;

}
