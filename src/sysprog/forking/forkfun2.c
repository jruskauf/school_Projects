/*
 * forkfun2.c: the forkening
 *
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	pid_t parent     = getpid();
	pid_t *child     = NULL;
	int rank         = 1;
	int start        = 0;
	int end          = 0;
	int numchilds    = 4;
	int sizeoflist   = 1000;

	if (argc        >= 2)
	{
		sizeoflist   = atoi(argv[1]);
	}

	if (argc        >= 3)
	{
		numchilds    = atoi(argv[2]);
	}

	if ((sizeoflist == 0) ||
		(numchilds  == 0))
	{
		fprintf (stderr, "ERROR: Invalid parameters specified\n");
		exit (1);
	}

	child            = (pid_t *) malloc (sizeof (pid_t) * (numchilds + 1));
	child[0]         = parent;

	if (numchilds   >  sizeoflist)
		numchilds    = sizeoflist;

	for (rank = 1; rank <= numchilds; rank++)
	{
		// divvy up the work, yo
		start = (sizeoflist  / numchilds) * (rank - 1);
		end   = ((sizeoflist / numchilds) * rank) - 1;

		if ( rank == numchilds)
		{
			end = end + (sizeoflist % numchilds);
		}

		child[rank]         = fork();
		if (child[rank] == 0)
		{
			fprintf (stdout, "rank %2d, start: %4d, end: %4d\n", rank, start, end);
			break;
		}
	}
	if (getpid() == parent)
	{
		for (rank = 1; rank <= numchilds; rank++)
			wait (NULL);
		sleep (0.5);
	}
/*
	if (child[start] == 0)
	{
		fprintf (stdout, "I am child #%u\n", rank);
		for (start = 0; start < 12; start++)
		{
			fprintf (stdout, "[child#%u] %u\n", rank, start*start*rank);
			sleep (2);
		}
		fprintf (stdout, "child #%u is done\n", rank);
	}
	else
	{
		for (start = 0; start < 10; start++)
		{
			fprintf (stdout, "[parent] *slave-driving*\n");
			sleep (3);
		}
	}
	*/

	return (0);
}
