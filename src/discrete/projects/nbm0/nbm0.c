#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]){

	//Here we set up the static array with all the symbols we need to 
	//represent bases 2-36
	char baseray[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	//setting up a variable sized array by making a char * varble
	char *checkray;
	//static sized arrays that are the largest possible value we will be 
	//having to process
	int sumray[64];
	int outray[64];
	//various varbles that do many things
	int check     = 1;
	int inbase    = 0;
	int outbase   = 0;
	int basecount = 0;
	int count     = 0;
	unsigned long long int sum       = 0;

	//Here we check if the arguments have been provided.  
	//If not, we exit after an error message
	if(argc <= 3){
		fprintf(stderr, "Error!  Invalid number of arguments!\n");
		exit(1);
	}
	
	inbase  = atoi(argv[1]);

	//checking to see if the base input is a valid base
	if(inbase < 2 || inbase > 36){
		fprintf(stderr, "Error!  Invalid input base!\n");
		exit(2);
	}
	
	outbase = atoi(argv[3]);
	
	//checking to see if the base output is a valid base
	if(outbase < 2 || outbase > 36){
		fprintf(stderr, "Error!  Invalid output base!\n");
		exit(3);
	}
	
	//here we malloc the memory to hold the length of the string.
	//Then we copy argv[2] into the array, and itterate through
	//it to check that the given string of symbols are within the
	//given input base.  Otherwhise, we return an error message.
	//we also convert the given string of characters to its numerical
	//value
	checkray = (char *)malloc(sizeof(char) * strlen(argv[2]));
	checkray = strcpy(checkray, argv[2]);
	int tmpcount = 0;

	for (count = strlen(checkray) - 1; count >= 0; count--){
		check = 1;
		basecount = 0;
		while (basecount < inbase && check != 0){
			if (checkray[count] == baseray[basecount]){
				sumray[tmpcount] = basecount;
				tmpcount++;
				check = 0;
			}
		basecount++;
		}
		if (check == 1){
			fprintf(stderr, "ERROR!  Number base is different than input!\n");
			exit(4);
		}

	}

	//We take the given string of values and convert it into a sum of
	//base 10, so we can then convert from base 10 to any base
	basecount=0;
	for (count = strlen(checkray) - 1; count >= 0; count--){
		sum = sum + (sumray[basecount] * pow(inbase, basecount));
		basecount++;
	}
		
	//Converting from base ten to the specified output base
	count = 0;
	while (sum > 0){
		outray[count] = sum%outbase;
		sum = sum/outbase;
		count++;
	}

	//iterating back one in the count as to not print ouf the escape
	//character.  Afterwords, we print out the values of the array
	count --;
	check = 0;
	while (count >= 0){
		if (outray[count] != 0 || check == 1){
			fprintf(stdout, "%c", baseray[outray[count]]);
			check = 1;
		}
		count--;
	}
	fprintf(stdout, "\n");
	
	return(0);
}
