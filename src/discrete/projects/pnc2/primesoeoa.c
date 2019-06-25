#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
	//////////////////////////////////////////////////////////////////
	//
	// Declare variables
	//
	FILE           *primelist  = stdout;  // file pointer for prime number display
	FILE           *timing     = stderr;  // file pointer for timing data display
	struct timeval  ts;                   // time start
	struct timeval  te;                   // time elapsed

	//////////////////////////////////////////////////////////////////
	//
	// Argument processing
	//
	if (argc <  3)
	{
		fprintf (stderr, "%s: insufficient number of arguments\n", argv[0]);
		exit (1);
	}

	//////////////////////////////////////////////////////////////////
	//
	// Start our timing
	//
	gettimeofday (&ts, 0);
	
	//////////////////////////////////////////////////////////////////
	//
	// Initialize important variables
	//

	//////////////////////////////////////////////////////////////////
	//
	// Your prime calculation algorithm
	//

	//////////////////////////////////////////////////////////////////
	//
	// Stop our timing
	//
	gettimeofday (&te, 0);

	//////////////////////////////////////////////////////////////////
	//
	// Display timing information
	//
	fprintf (timing, "%8.4lf\n",
			te.tv_sec - ts.tv_sec + ((te.tv_usec - ts.tv_usec) / 1000000.0));

	return (0);
}
