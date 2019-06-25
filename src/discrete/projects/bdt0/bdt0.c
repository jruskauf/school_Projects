#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
///////////////////////////////////////////////////////////////////////////////
//This struct would handle the address given to the program through extra
//command line arguments.  I wasn't able to implement the color highlights
//before the deadline for the day after, but i'll send you a copy of the 
//completed code if you wish so you can review it.
struct color {

	//address and number of values after said address to be highlighted
	int address;
	int amount;	
};

int main(int argc, char **argv)
{
	//Variable used to read the information from the file we wish to access
	FILE *input;
	//Array used to store 16 variables at a time, which is the most we have
	//printed out per line of data.
	int content[16];
	//These two handle the terminal size variables to be later used in
	//checks for correct terminal size.
	struct winsize terminal;
   	ioctl  (0, TIOCGWINSZ, &terminal);
	//This sets a count to be used in order to keep track of what array
	//element we want to access
	int count = 0;
	//a global count that is used to keep track of what number iteration
	//the entire program is on, or in short what byte of data we should be
	//accessing from the file
	int gcount = 0;
	//This is equal to the current value stored in the element of the array
	//we currently wish to access, such as *(content+2) as an example.
	int current;
	//This is the current value to be printed out with the newline hex value
	int line = 0;
	//This is to keep track of how many bytes we have printed out so far,
	//and to handle the spaces in between each pair of printed bytes
	int space = 0;
	//The line cap that can be specified on the command line
	int lcap = 0;
	//How many lines have been printed out thus far.
	int lcount = 0;

 	//A check to see if the terminal height is within acceptable bounds
	if (terminal.ws_row < 20){

		printf("Error: Terminal height is less than 20 lines!\n");

		return(0);

	}
	//a check to see if the terminal width is within acceptable bounds
	if (terminal.ws_col < 80){

		printf("Error: Terminal width is less than 80 columns!\n");

		return(1);

	}

	
	//This checks if there are too few arguments given
	if (argc == 1){

		printf("Error: Invalid number of arguments!\n");
	} 
        //inserts a linecap value if it is given to the command line
	if (argc == 3){
		lcap = atoi(*(argv+2));
	}
	//If a filename has been provided and can be opened, it will start the
	//production of the hex value table.
	if (input = fopen(*(argv+1), "r")){
		
		//This handles the initial setting of current, which is equal
		//to the value in the current array element, which is fetched
		//from the file we want to use as input		
		current = *(content+count) = fgetc(input);
		
		//While current does not equal the end of file statement, 
		//or while lcap is equal to 0 or lcount has not exceeded 
		//the set lcap
		while ( current != EOF && (lcount <= lcap || lcap == 0)){
		
			//This handles the very first line header, and then
			//incriments line and line count accordingly.	
			if (count == 0 && line == 0){
				printf("00000000: ");
				line = line + 16;
				lcount++;
			} 
			
			//This prints out the current value being accessed in
			//its hex value.
			printf("%02x", current);
			
			//incriments count, gcount, and space accordingly.
			count++;
			gcount++;
			space++;
			
			//Handles the spacing in between the hex values, so they
			//are printed out in pairs
			if (space == 2){
				printf(" ");
				space = 0;
			}

			//This handles the printing of the ascii characters.
			//If the count is equal to 16 and the value of line is
			//not zero, this statement will print out all values
			//stored in the array in their ASCII form, except for
			//any newlines, tabs, or characters outside of the 
			//printable ASCII character value range.  This will
			//also print out the newline header, which becomes
			//a problem with the files that end with a count of
			//16, but do not have any values after that.  This is
			//due to how i set up the setting of current, which
			//has to have a count of 0 to incriment properly after
			//the next line of values is to be printed.
			if (count == 16  && line != 0){
				
				printf(" ");
				for (count=0; count < 16; count++){
					
					current = *(content+count);
					

					if ( current > 126 || current < 32) {
						printf(".");
					}else if (current != '\t' 
							&& current != '\n'){
						printf("%c", current);
					} else {
						printf(".");
					}
				}
				
				count = 0;

				if ((count == 0 && line != 0) && (lcount < lcap
								|| lcap == 0)){
					
					printf("\n%08x: ", line);
					line = line + 16;
				}

				lcount++;
			} 

			current = *(content+count) = fgetc(input);		
			
		}
		//This handles the last line of values to be printed, regardless
		//of whether they are a full set of 16, or none at all.
		if (count != 0)
		{
			printf(" ");	
			while (gcount < line){
		
				printf("  ");
				space++;
				gcount++;
		
				if (space == 2){
					printf(" ");
					space = 0;
				}
			}


			int tick = 0;
			while(tick < count){
				
				current = *(content+tick);
				if ( current > 126 || current < 32) {
					printf(".");
					tick++;
				}else if (current == '\n' || current == '\t'){
					printf(".");
					tick++;
				} else {	
					printf("%c", current);
					tick++;
				}

			}
		}
		//a newline to have the command line not stuck on the end of the
		//output	
		printf("\n");
		
		//closing the input so nothing weird happens
		fclose(input);	

	//if the file cannot be read, this will produce an error message
	} else {
		printf("Error: File does not exist!\n");
		return(2);
	}
	
	
  	return (0);
}
