#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t parent  = getpid();
	pid_t child[8];
	int rank   = 1;
	int index  = 0;

	fprintf (stdout, "Parent PID is: %u\n", parent);
	for (index = 0; index < 4; index++)
	{
		child[index]         = fork();
		if (child[index] != 0)
		{
			fprintf (stdout, "[parent] child #%u is: %u\n", rank, child[index]);
			rank             = rank + 1;
		}
		else
			break;
	}

	if (child[index] == 0)
	{
		fprintf (stdout, "I am child #%u\n", rank);
		for (index = 0; index < 12; index++)
		{
			fprintf (stdout, "[child#%u] %u\n", rank, index*index*rank);
			sleep (2);
		}
		fprintf (stdout, "child #%u is done\n", rank);
	}
	else
	{
		for (index = 0; index < 10; index++)
		{
			fprintf (stdout, "[parent] *slave-driving*\n");
			sleep (3);
		}
	}

	return (0);
}
