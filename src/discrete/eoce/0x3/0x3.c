#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[]){

    //setting up the useful variables for quantity, factor pairs, low bound,
    //high bound, and mode.
    int qty   = 0;
    int Nary = 0;
    int start  = 1;
    int end  = 0;
    int mode  = 0;
    //Error checking of arguments so we have the things we want if they're
    //present.
    if(argc < 3){
	fprintf(stderr, "ERROR! Invalid number of arguments!\n");
	exit (1);
    }

    if (atoi(argv[1]) > 0 || argc > 4){
	qty = atoi(argv[1]);
    } else {
	fprintf(stderr, "ERROR! Invalid qty!\n");
	exit (2);
    }

    if (atoi(argv[2]) < 1){
	fprintf(stderr, "ERROR! Invalid N-ary!\n");
	exit(3);
    } else {
	Nary = atoi(argv[2]);
    }
    
 
    if (argc > 4){
        if(atoi(argv[3]) > atoi(argv[4]) && atoi(argv[4]) != 0){
 	    fprintf(stderr, "ERROR! Invalid Lower Bound!\n");
            exit(4);
        } else {
	   start = atoi(argv[3]);
	   end   = atoi(argv[4]);
           if(argc == 6){
   	       if(atoi(argv[5]) > 0){
	           mode = 1;
    	       }
	   }
	}
    }    
 
    //This loop handles the factor pair creation, checking, and display.  
    //We start at 1 by default unless specified, and work towards a QTY if
    //present.  if qty is not present, and a high bound is, we end at the 
    //high bound, or if qty is present as well whatever comes first.
    //we set the number to test to for the factor pairs using the square root
    //function.  This is done so we do not have to check ALL numbers within
    //a number's factors, only the first possible number in the pair.  Keeping
    //track of each "hit" with a counter, we can then compare it to Nary to see
    //if it has the correct amount of factors.  If so, we print it out according
    //to the mode that has been set.  By default, it is mode 0, but anything
    //above 0 will set it to 1.  For displaying with mode 1, we print out the
    //factors we have recorded, and then divide the number being tested by the
    //first factor number in order to get the counterpart.  This way, we don't
    //need to store all the factors, just half of them.
    int count = 0;
    int fcount = 1; 
    int factors[255];
    int element = 0;
    int checkto = sqrt(start);
    while((count != qty || qty == 0) && (start <= end || end == 0)){
        checkto = sqrt(start);
	element = 0;
	fcount = 1;
	while(fcount <= checkto){
	    if(start%fcount == 0 && element != 255){
		factors[element] = fcount;

		element++;
	    }
	    fcount++;
	}

	if(element == Nary){
	    count++;
	    printf("%d ", start);
  	    if(mode == 1){
	        fcount = 0;
	        printf("= { ");
	        while(fcount < element){
	  	    printf("%d, ", factors[fcount]);
		    fcount++;
	        }
		while(fcount > 1){
		   printf("%d, ", (start/fcount));
		   fcount--;
		}
	        printf("%d }\n", (start/fcount));
	    }
	}
 
	start++;

    } 
    if(mode == 0)
	printf("\n");
    return(0);
}
