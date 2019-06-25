#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

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
	int        QTY; //Count of how many primes have been generated
	int      count; //How many prime #'s we want
	int       LowB; //Lowest value we start generating from
	int      HighB; //Highest value we generate to
	int     number; //The value that is currently being tested
	int        mod; //The value of which the current number being tested is divided by
	int  minremain; //The remainder of the modulus algorithm for 6a-1
	int plusremain; //The remainder of the modulus algorithm for 6a+1
	int squareroot; 

	//////////////////////////////////////////////////////////////////
	//
	// Argument processing
	//
	/*=============================================================='*
	|* These argument checks make sure there aren't any errors with *|
	|* the provided (or not provided) arguments.  IF there are      *|
	|* errors, then it will promptly scream an error message.  Also *|
	|* responsible for weather HighB is set to 0 or a provided      *|
	|* argument.							*|
	'*==============================================================*/
	//Checks for the required numbe of arguments
	if (argc <=  2)
	{
		fprintf (stderr, "%s: insufficient number of arguments!\n", argv[0]);
		exit (1);
	}
       	
	//checks if argument 1 is an invalid value if the arguments are equal to or
	//less than three
	if(atoi(argv[1]) <= 0 && argc <=4)
	{
		fprintf (stderr, "%s: invalid quantity!\n", argv[0]);
		exit (2);
	}
       
	//This checks if argument 2 is equal to 1, which is what it should be for this
	//project.
	if(atoi(argv[2]) != 1)
	{
		fprintf (stderr, "%s: invalid value!\n", argv[0]);
		exit (3);
	}
       
	//This checks argument 3 to see if it is less than 2 given 4 or more arguments
	if (argc >= 4 && atoi(argv[3]) < 2)
	{
		fprintf (stderr, "%s: invalid lower bound!\n", argv[0]);
		exit (4);
	}
        
	//This checks if argument 4 is both not equal to 0 and less than 3, given there
	//is five arguments present.
	if (argc == 5 && (atoi(argv[4]) < atoi(argv[3]) && atoi(argv[4]) != 0))
	{
		fprintf (stderr, "%s: invalid upper bound!\n", argv[0]);
		exit (5);
	}
	
	//This sets LowB given the number of arguments present
	if (argc <= 3){
		LowB=2;
	}else{
		LowB=atoi(argv[3]);
	}
	
	//This sets HighB given the number of arguments present
	if (argc <= 4)
	{
		HighB=0;
	}else{
		HighB=atoi(argv[4]);
	}
	
	//sets up QTY, number, and initial prime numbers based on LowB	
	if (LowB >= 2 && LowB < 6){
		QTY = 2;
		number = 6;
		fprintf(primelist, "2 3 ");
	}else{
		QTY = 0;
		number = LowB;
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
	count  = atoi(argv[1]);
	//////////////////////////////////////////////////////////////////
	//
	// Your prime calculation algorithm
	//	
	/*==============================================================*'
	|* The calculation algorithm consists of a nested for loop in a *|
	|* while loop.  The while loop keeps track of how many prime    *|
	|* numbers have been generated, while accounting for a possible *|
	|* 0 in argv[1], and whether HighB has a value of 0 or another  *|
	|* valid number.  The for loop handles the actual arithmatic,   *|
	|* taking into account each number's size.  It is also          *|
	|* responsible for printing out the prime numbers as they're    *|
	|* generated.  This program also takes into account that every  *|
	|* number being tested is withing +/-1 of multiples of 6.  This *|
	|* drastically cuts down on processing time, as you are now     *|
	|* processing 2 numbers at a time that we know are possible     *|
	|* prime numbers, instead of covering everything in between as  *|
	|* well.                                                        *|
	'*==============================================================*/ 
	while ((QTY != count || count == 0) && (number <= HighB || HighB == 0)){
		int plustally = 2;
		int minustally = 1;
		int plusnum = number + 1;
		int minnum = number - 1;
		//in this version of mapping, we set the number we are checking
		//by equal to the squareroot of plusnum (the highest number we
		//want to check out of the two) so we get the correct number of
		//values to check.
		squareroot = sqrt(plusnum);
		for (mod = squareroot; mod > 0; mod = mod - 1){
			if (mod <= minnum){
				if (mod == minnum){
					minremain = 1;
				}else {
					minremain = minnum % mod;
				}
				if (minremain != 0){
					minustally = minustally + 1;
				}
			}

			if (mod == plusnum){
				plusremain = 1;
			}else {
				plusremain = plusnum % mod;
			}
			if (plusremain != 0){
				plustally = plustally + 1;
			}
		}
		//We check if minustally is equal to the number of factors we
		//wanted to check, rather than checking against the number (as
		//in this, tally will always be less than the number due to
		//checking less times than said number)
		if ((minustally == squareroot && (QTY < count || count == 0)) && minnum >= LowB){
			fprintf(primelist, "%d ", minnum);
			QTY = QTY + 1;
		}
		
		if ((plustally == squareroot+1 && (QTY < count || count == 0)) && (plusnum <= HighB || HighB == 0)){	
			fprintf(primelist,"%d ", plusnum);
			QTY = QTY + 1;	
		}	
	
		number = number + 6;
	}
	fprintf(primelist,"\n");	
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
