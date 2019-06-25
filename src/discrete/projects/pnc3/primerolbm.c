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
	int       QTY; //Count of how many primes have been generated
	int     count; //How many prime #'s we want
	int      LowB; //Lowest value we start generating from
	int     HighB; //Highest value we generate to
	int    number; //The value that is currently being tested
	int       mod; //The value of which the current number being tested is divided by
	int remainder; //The remainder of the modulus algorithm
	int chkcount = 0;
	int check = 0;

	//////////////////////////////////////////////////////////////////
	//
	// Argument processing
	//
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
	QTY    =             0;
	number =          LowB;
	mod    = 	     2;
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
	|* generated.                                                   *|
	'*==============================================================*/ 
	while ((QTY != count || count == 0) && (number <= HighB || HighB == 0)){
		remainder = number%mod;
		
		if(remainder == 0 && mod != number){
			if(number != 2 && number != 3){	
				number = (chkcount == 0) ? number + 2 : number + 4;
			} else if(number == 2){
				number++;
			} else if(number == 3){
				number = number + 2;
			}
			mod = 2;
			check = 0;
		}

		if((mod == (number) && check == 0) || number == 2){
			fprintf(primelist, "%d ", number);
			QTY++;
			if(number != 2 && number != 3){	
				number = (chkcount == 0) ? number + 2 : number + 4;
			} else if(number == 2){
				number++;
			} else if(number == 3){
				number = number + 2;
			}

			mod = 2;
		} else {
			mod++;
		}
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
