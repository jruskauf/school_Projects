#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//function prototypes and definitions
char *num2name_if(unsigned char);
char *num2name_tern(unsigned char);
char *num2name_algo(unsigned char);
unsigned char name2num_if(char *);
unsigned char name2num_tern(char *);
unsigned char name2num_algo(char *);
void checkname(char *);

//static arrays to access values for card numbers, and to return a card name
char *suit[4] = {"C", "D", "H", "S"};
	
char *card[13] ={"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

int main (int argc, char *argv[]){
	//Variables for usefullness
	int choice;
	int cnum;
	char cname[3];
	char *cout = NULL;
	unsigned char nout;
	
	//Displaying menu and then asking for user input
	fprintf(stdout, "===Card Processor===\n");
	fprintf(stdout, "1: num2name(if)\n");
	fprintf(stdout, "2: num2name(tern)\n");
	fprintf(stdout, "3: num2name(algo)\n");
	fprintf(stdout, "4: name2num(if)\n");
	fprintf(stdout, "5: name2num(tern)\n");
	fprintf(stdout, "6: name2num(algo)\n");
	fprintf(stdout, "7: EXIT\n");
	fprintf(stdout, "Enter the number of the program you wish to use: ");
	fscanf(stdin, "%d", &choice);
	
	//Based on initial user selection, use the specificed algorithm.
	if (choice == 1){

		//Prompting the user for input, and then checking if the input
		//is valid.  If the input is not valid, we spit out an error
		//and exit, otherwise we use the specified program and 
		//spit out the results.  This is identical for choices 1-3.
		fprintf(stdout, "Please enter a number between 1-52: ");
		fscanf(stdin, "%d", &cnum);

		if (cnum > 0 && cnum <= 52){	
			cout = num2name_if(cnum);
			fprintf(stdout, "Your card is: %s\n", cout);
		} else {
			fprintf(stderr, "ERROR! Number is out of bounds \n");
			exit(1);
		}
	
	} else if (choice == 2){

		printf("Please enter a number between 1-52: ");
		fscanf(stdin, "%d", &cnum);

		if (cnum > 0 && cnum <= 52){	
			cout = num2name_tern(cnum);
			printf("Your card is: %s\n", cout);
		} else {
			fprintf(stderr, "ERROR! Number is out of bounds \n");
			exit(2);
		}

	} else if (choice == 3){

		printf("Please enter a number between 1-52: ");
		fscanf(stdin, "%d", &cnum);

		if (cnum > 0 && cnum <= 52){	
			cout = num2name_algo(cnum);
			printf("Your card is: %s\n", cout);
		} else {
			fprintf(stderr, "ERROR! Number is out of bounds \n");
			exit(3);
		}
	
	} else if (choice == 4){
		//Prompting user for input, and then passing said input to an
		//errorchecking function which will make sure the input is
		//valid, if not spit out an error and exit.  Otherwise, use
		//the requested program and print out the result.
		printf("Please enter a card name: ");
		fscanf(stdin, "%s", cname);
		checkname(cname);
		nout = name2num_if(cname);
		printf("nout is %d\n", nout);

	} else if (choice == 5){
		
		printf("Please enter a card name: ");
		fscanf(stdin, "%s", cname);
		checkname(cname);
		nout = name2num_tern(cname);
		printf("nout is %d\n", nout);	
	
	} else if (choice == 6){
		fprintf(stderr, "NOT IMPLEMENTED!\n");
		exit(6);
	} else if (choice == 7){
		printf("EXIT\n");
		exit (7);
	} else {
		fprintf(stderr, "ERROR! INVALID CHOICE!\n");
		exit(1);
	}
	return(0);
}

//Functions
char *num2name_if(unsigned char cnum){
	//creating and mallocing out the return statement to be built.
	char *sendback = NULL;
	sendback = (char *)calloc(10, sizeof(char));

	//Depending on the value of the number, we build the statement by first
	//first copying the card's number/face to the output statement from its
	//array, and then adding the suit character after that.  This is done
	//through the selection structure.
	if (cnum <= 13){
		strcpy(sendback, card[cnum-1]);
        	strcat(sendback, suit[0]);
	}else if (cnum > 13 && cnum <= 26){
		strcpy(sendback, card[cnum-14]);
        	strcat(sendback, suit[1]);
	} else if (cnum > 26 && cnum <= 39){
		strcpy(sendback, card[cnum-26]);
        	strcat(sendback, suit[2]);
	} else if (cnum > 39 && cnum <= 52){
		strcpy(sendback, card[cnum-40]);
        	strcat(sendback, suit[3]);
	}

	return(sendback);
}

char *num2name_tern(unsigned char innum){
	//Creatinga and mallocing out the return statement to be built.
	char *sendback = NULL;
	sendback = (char *)calloc(10, sizeof(char));
	int snum = 0;
	int cnum = innum;
	//Using ternary statements in a gradual selection structure, we
	//subtract or don't subtract values as the input is passed through
	//it.  At the end, we end up with two numbers, which access the
	//array elements that build the statement at the end.
	snum = (innum >= 39) ? snum + 1  : snum;
	cnum = (innum >= 39) ? cnum - 13 : cnum;
	snum = (innum >= 26) ? snum + 1  : snum;
	cnum = (innum >= 26) ? cnum - 13 : cnum;
	snum = (innum >= 14) ? snum + 1  : snum;
	cnum = (innum >= 14) ? cnum - 13 : cnum;
	cnum = (innum >= 1)  ? cnum - 1  : cnum;

	strcpy(sendback, card[cnum]);
        strcat(sendback, suit[snum]);

	return(sendback);
}

char *num2name_algo(unsigned char cnum){
	//Creatinga and mallocing out the return statement to be built.
	char *sendback = NULL;
	sendback = (char *)calloc(10, sizeof(char));
	int fnum = 0;
	int snum = 0;
	
	//By first dividing the input by 14, the remainder is returned to snum,
	//which corresponds with the array number for the suit.  Then by 
	//subtracting the remainder times the suit number from the input, we get
	//the element for the card face we want to access.
	snum = cnum/14;
	fnum = cnum - (snum * 13);

	strcpy(sendback, card[fnum-1]);
        strcat(sendback, suit[snum]);

	return(sendback);
}

void checkname(char *cname){
	//This checks if there are any immediately repeated characters, as no
	//combination should have repeated characters.
	if (cname[1] == cname[0]){
		fprintf(stderr, "ERROR! Repeated characters![1][2]\n");
		exit(41);
	}else if (cname[0] == cname[2]){
		fprintf(stderr, "ERROR! Repeated characters![1][3]\n");
		exit(42);
	} else if (cname[1] == cname[2] && cname[2] != 0){
		fprintf(stderr, "ERROR! Repeated characters![2][3]\n");
		exit(43);
	}

	//This checks each individual element to see if it is correctly inputed
	//in context to the other elements.  Therefore, if cname[2] is null, 
	//there's no need to check its value, and if cname[1] is 0, then there's
	//no need to check it's value
	if (cname[0] <= 48 || cname[0] > 57){
		if (cname[0] != 65 && cname[0] != 74 && 
		    cname[0] != 75 && cname[0] != 81   )
		{
			fprintf(stderr, "ERROR! Invalid character![1]\n");
			exit(44);
		}
	}
	if (cname[1] != 48 || cname[1] > 57){
		if (cname[1] != 67 && cname[1] != 68 &&
		    cname[1] != 72 && cname[1] != 83   )
		{
			fprintf(stderr, "ERROR! Invalid/missing character![2]\n");
			exit(45);
		}
	}
			
	if (cname[2] != 0){
		if(cname[2] != 67 && cname[2] != 68 &&
	    	   cname[2] != 72 && cname[2] != 83   )
		{
			fprintf(stderr, "ERROR! Invalid character![3]\n");
			exit(45);
		}
	} 
}

unsigned char name2num_if(char *cname){
	//a count for loops and then the return number
	int count = 0;
	int cardnum = 0;
	//checking how many elements we need to account for.
	if (cname[2] == 0){
		count = 1;
	} else {
		count = 2;
	}
	//For every element of the input, we check it against the suit array
	//and the card array to see if it matches any of the values.  Then,
	//we add to cardnum the tmpcount for the while loops which is then
	//modified to either account for a suit value or a face value.
	for(count = count; count >= 0; count--){
		int tmpcount = 0;
		while (tmpcount <= 3){
			if (cname[count] == *suit[tmpcount]){
				cardnum = cardnum + (tmpcount * 13);
			}
			tmpcount++;
		}
		tmpcount = 0;
		while (tmpcount <= 12){
			if (cname[count] == *card[tmpcount]){
				cardnum = cardnum + (tmpcount + 1);
			}
			tmpcount++;
		}
	}
	return(cardnum);
}

unsigned char name2num_tern(char *cname){
	int cardnum = 0;
	int count = 0;
	//Again, for every element of the input, we check it against the arrays
	//using a ternary statement in this instance, and modifying cardnum to
	//reflect the value of the card.
	for (count = count; count < 3; count++){
		int tmpcount = 0;
		while (tmpcount <= 3){
			cardnum =(cname[count]==*suit[tmpcount])
				                ?cardnum+(tmpcount*13):cardnum;
			tmpcount++;
		}
		tmpcount = 0;
		while (tmpcount <= 12){
			cardnum =(cname[count]==*card[tmpcount])
						?cardnum+(tmpcount+1):cardnum;
			tmpcount++;
		}
	}
	return(cardnum);
}

unsigned char name2num_algo(char *cname){
	int cardnum = 0;
	//I didn't get around to this in time before the end of being one day
	//late, but i imagine there is likely a pattern in either the total
	//of the entire input, or in how the information is layered.  I know
	//for instance that the values 0-9 in ASCII need to have their decimal
	//value subtracted by 48 to get their int value represented properly,
	//but the characters don't see to have the same pattern, as some letters
	//come before others, but are layered differently in the arrays.  I'll
	//still attempt to work through this, but at this time it's not worth
	//another 25% to the grade.	
	return(cardnum);
}
