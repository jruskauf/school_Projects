#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t parent = getpid();
	pid_t child;

	fprintf(stdout, "Parent PID is: %u\n", parent);
	child = fork();
	fprintf(stdout, "child is: %u\n", child);

	sleep(30);

	return(0);
}
