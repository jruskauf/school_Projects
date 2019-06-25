#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int main (int argc, char *argv[]){
    
    //seeding the random function using the current time
    srand(time(NULL));
    //setting up string variables for letter functionality later on
    char *c_divisor  = NULL;
    char *c_dividend = NULL;
    char *c_quotient = NULL;
    char *c_remainder = NULL;
    //setting up the math variables that we will use to calculate
    //subtraction, division, etc.
    int divisor   = 0;
    int dividend  = 0;
    int quotient  = 0;
    int remainder = 0;
    int count     = 0;

    //mallocing out memory for the strings
    c_dividend  = (char*)malloc(sizeof(char));
    c_divisor   = (char*)malloc(sizeof(char));
    c_quotient  = (char*)malloc(sizeof(char));
    c_remainder = (char*)malloc(sizeof(char));
    
    //This handles the random number generation, the generation of the quotient,
    // and the generation of the remainder.
    while (strlen(c_quotient) < 3){
        while(strlen(c_dividend) > 9 || strlen(c_dividend) < 7){ 
	    sprintf(c_dividend, "%d", rand());
        }
        while(strlen(c_divisor) > 5 || strlen(c_divisor) < 2){ 
            sprintf(c_divisor, "%d", rand());
        }

        divisor = atoi(c_divisor);
        dividend = atoi(c_dividend);
	quotient = dividend/divisor;
	remainder = dividend%divisor;
	printf("%d\n", remainder);

	sprintf  (c_quotient, "%d", quotient);
	sprintf(c_remainder, "%d", remainder);
    }

    /*=====================================================================*/
    //This handles the static layout, accounting for the different sized numbers
    //with buffers.
    printf("        ");
    for(count = 0; count < strlen(c_dividend)-strlen(c_quotient); count++){
	printf(" ");
    }
    printf("%s\n", c_quotient);

    printf("      +-");
    for(count = 0; count < strlen(c_dividend); count++){
	printf("-");
    }
    printf("\n");
    printf("%5s | %-9s\n", c_divisor, c_dividend);
    
    /*=====================================================================*/
    //This giant mess handles the variable layout.  It takes the length of the
    //divisor and uses it to pull however many numbers from the dividend into
    //its own number.  Then, divides that by the divisor, multiplies it by the 
    //divisor (This gives us the greatest number that can go into subnum), then
    //subtracts it from subnum.  Then, to account for the "addition" of the next
    //dividend's value, it multiplies by ten and then adds the next character in
    //the dividend.  This is done until we reach the last character of the 
    //dividend, which when subnum is subtracted from leaves us with the 
    //remainder.  Layout is kind of messy, as i wasn't able to get the hang
    //of the spacing, but the math checks out in the end.
    int space     = 7;
    int sublength = 0;
    int subnum    = 0;
    char *subray  = NULL;
    subray = (char*)malloc(sizeof(char));

    for(count = 0; count < strlen(c_divisor); count++){
	subray[count] = c_dividend[count];
    }
    subnum = atoi(subray);

    int iter = count;
    int tally = strlen(c_divisor);
    printf(" ");

    while(tally <= strlen(c_dividend)){
	for(count = 0; count < space-1; count++){
	    printf(" ");
	}
	printf("-");
	printf("%5d\n", (subnum/divisor) * divisor);

	for(count = 0; count < space; count++){
	    printf(" ");
	}

	for(count = 0; count < strlen(c_divisor); count++){
	   printf("=");
	}

	printf("\n");
	subnum = ((subnum - ((subnum/divisor) * divisor)) * 10) + (c_dividend[iter] - 48);

	for(count = 0; count < space; count++){
	    printf(" ");
	}

	if(tally != strlen(c_dividend)){
	    printf(" %d\n", (subnum));
	} else {
	    printf(" %d\n", (subnum/10)+5);
	}

        iter++;
	space++;
	tally++;

    }

    return(0);

}
