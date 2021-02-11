#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void read_and_report(int fd, int* sum, fd_set* set)
{
  char buf[BUFSIZ];
  //printf("FD %d is ready to read\n", fd);
  int bytes = read(fd, buf, BUFSIZ - 1);
  buf[bytes] = 0;
  if (!bytes) {
	  FD_CLR(fd, set);
	  close(fd);
	  return;
  }
  //printf("Get %d bytes from %d : %s\n", bytes, fd, buf);
  *sum += atoi(buf);
}

int main(int argc, char* argv[])
{

  int f1 = open("./in1", O_NONBLOCK | O_RDONLY);
  int f2 = open("./in2", O_NONBLOCK | O_RDONLY);

  int sum = 0;

  if (!(f1 && f2) ) 
  {
    printf ("Error with opening pipes\n");
    return 0;
  }

  //printf("Descriptors: %d %d\n", f1, f2);

  fd_set read_set, tmp_set;
  FD_ZERO(&read_set);
  FD_SET(f1, &read_set);
  FD_SET(f2, &read_set);

  while( FD_ISSET(f1, &read_set) || FD_ISSET(f2, &read_set) )
  {
    tmp_set = read_set;
    int result = select(10, &tmp_set, NULL, NULL, NULL);
   
    if(result)
    {
	//printf("Select returned: %d\n", result);
      	if( FD_ISSET(f1, &tmp_set) )
        	read_and_report(f1, &sum, &read_set);
      	if( FD_ISSET(f2, &tmp_set) )
        	read_and_report(f2, &sum, &read_set);
    }
  }

  printf("%d\n", sum);

  close(f1);
  close(f2);

  return 0;
}
