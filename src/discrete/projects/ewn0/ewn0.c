#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    //Here we are checking if there are enough arguments, and if the arguments
    //are within a valid range for the program.  This hopefully weeds out any
    //invalid inputs.
    if(argc < 3){
	if(argc == 2){
	    fprintf(stderr, "missing upper bound\n");
	    exit(0);
	} else {
	    fprintf(stderr, "insufficient data provided\n");
	    exit(1);
	}
    }

    if (atoi(argv[1]) < 2 || atoi(argv[2]) < 2){
	fprintf(stderr, "invalid range specification\n"); 
	exit(2);
    }

    //This holds the number of factors of a number.  I set it high so there is
    //likely no chance of this number being hit.  If it is hit, however, the
    //program will bail.  I did this so i did not have to actively add more
    //memory to the array, as it is unlikely we will hit this cap, as the 
    //runtime to get there is fairly ridiculous. 
    int addnum[255];
    //This sets the starting value as the value integer value of the first arg.
    int start = atoi(argv[1]);
    //This sets the ending value
    int end   = atoi(argv[2]);
    //This handles the iteration through the range of values, accounts for 
    //whether arg[1] is greater or less than arg[2]
    int iter = (start<end) ? 1 : -1;
    //This is the starting value for where we check of the number is a factor
    //or not.
    int count = 1;
    //This handles placing the factors in the array, used to overwrite past
    //values as well
    int element = 0;
    //This handles the sum of all the factors, and is checked against the value
    //we are currently testing.
    int sum;

    //This loop iterates us through the range of numbers we want to test, and
    //by adding iter to the end, we make sure to get the value of end tested
    //as well.
    while (start != end+iter){
	//This prints out the number we are testing.
	printf("[%d] ", start);
	//resetting variables to the desired starting state, as every iteration
	//of the outer loop tests a different number
	element = 0;
	count = 1;
	sum = 0;

	//This loop handles the factors, assigning the factors to their own
	//array element every time a valid factor is detected. It also handles
	//the sum of the factors, adding the factor being tested to the sum when
	//it detects a valid factor.
	while(count != start){
	    if(start%count == 0 && element != 255){
	        addnum[element] = count;
		element++;
		sum = sum + count;
	    }
	    count++;
	}

	//This prints out whether the number being tested is perfect or
	//otherwise, based on the sum of the factors.
	if(sum == start){
	    fprintf(stdout, "  perfect: ");
	} else if (sum > start){
	    fprintf(stdout, " abundant: ");
	} else {
	    fprintf(stdout, "deficient: ");
	}
	
	//This handles printing out the addition of factors by printing out
	//each and every element that's been written to the array, and then
	//displaying the sum at the end of it all.
	if(element == 1){
	    fprintf(stdout, "1");
	} else {
	    count = 0;
	    while(count < element){
	        if(count == element-1){
		    printf("%d", addnum[count]);
		} else {
		    printf("%d+", addnum[count]);
	        }
		count++;
	    }
	}
	printf(" = %d\n", sum);

	//iterates to a new number at the end of the loop.
	start = start + iter;
    }
    return(0);
}

