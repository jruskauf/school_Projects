#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define  ANSI_RESET             "\x1b[0m"
#define  ANSI_BOLD              "\x1b[1m"
#define  ANSI_FG_BLACK          "\x1b[30m"
#define  ANSI_FG_RED            "\x1b[31m"
#define  ANSI_FG_GREEN          "\x1b[32m"
#define  ANSI_FG_YELLOW         "\x1b[33m"
#define  ANSI_FG_BLUE           "\x1b[34m"
#define  ANSI_FG_MAGENTA        "\x1b[35m"
#define  ANSI_FG_CYAN           "\x1b[36m"
#define  ANSI_FG_WHITE          "\x1b[37m"
#define  ANSI_BG_BLACK          "\x1b[40m"
#define  ANSI_BG_RED            "\x1b[41m"
#define  ANSI_BG_GREEN          "\x1b[42m"
#define  ANSI_BG_YELLOW         "\x1b[43m"
#define  ANSI_BG_BLUE           "\x1b[44m"
#define  ANSI_BG_MAGENTA        "\x1b[45m"
#define  ANSI_BG_CYAN           "\x1b[46m"
#define  ANSI_BG_WHITE          "\x1b[47m"

int equalcheck(char compare1, char compare2);
void display(int *array1, int *array2, int *colorcheck, int gcount);

int main(int argc, char **argv)
{
	//initializing variables and arrays for use in storing values grabbed
	//from files, whether to color a certain array value when printed out,
	//variables to store a single byte grabbed from the file we want, etc.
	FILE *in1;
	FILE *in2;

	int  before1[16];
	int  before2[16];
	
	int forecolor[16];
	int colorcheck[16];

	int current1[16];
	int current2[16];

	int       count;
	int      gcount;
	char   compare1;
	char   compare2;
	char      color;
	int       check;
	int doublecheck;


	//Can use memcpy to copy contents of a whole array to another
	//memcpy(copytoarray, copyfromarray, sizeof(copytoarray));
	
	//Checking to see if we have two possible files present or not, if not
	//we print out an error
	if (argc == 1){
		fprintf(stderr, "ERROR: Only one file provided!\n");
		exit(0);
	}
	
	//Here we check if both files can be opened or not, if no, we print out
	//an error statement.  Otherwise when both files can be opened we begin
	//to process them. 
	if ((in1 = fopen(*(argv+1), "r")) && (in2 = fopen(*(argv+2), "r"))){
		//count is responsible for assigning values to array elements,
		//while gcount is responsible for keeping track of how many
		//bytes of data have been processed, and check will help us skip
		//unneeded processes/have them execute in the right order.
		count = 0;
		gcount = 0;
		check = 0;
		//While both files have not reached their end, we will process
		//them.
		while (!feof(in1) && !feof(in2)){
			//This portion deals with displaying the needed data and
			//copying the current arrays to the arrays used to 
			//print out the previous lines of values if needed.
			//We also check to see if the count is high enough to
			//even need a previous line of data to be printed out.
			//It also handles the checks to be able to correctly
			//print out first and last line differences.
			if ((count == 16 && check == 1) && gcount > 16){
				display(before1, before2, forecolor, gcount-16);
				display(current1, current2, colorcheck, gcount);
				memcpy(forecolor, colorcheck, sizeof(forecolor));
				memcpy(before1, current1, sizeof(before1));
				memcpy(before2, current2, sizeof(before2));
				count= 0;
				if (gcount <= 32){
					check = 3;
				}else {
					check = 2;
				}
			} else if (count == 16 && check == 2){
				display(current1, current2, colorcheck, gcount);
				count = 0;
				check = 0;
			//This is copying the current array into the before
			//array, but no displaying is done here as this handles
			//when no differences have been found.
			} else if (count == 16){
				memcpy(forecolor, colorcheck, sizeof(forecolor));
				memcpy(before1, current1, sizeof(before1));
				memcpy(before2, current2, sizeof(before2));
				count = 0;
			}
			//iteration of the bytes we want as well as checking to
			//see if there is a difference, and if so, indicating it
			//in the color array and then setting check accordingly.
			compare1 = *(current1+count) = fgetc(in1);
			compare2 = *(current2+count) = fgetc(in2);
			color=*(colorcheck+count)=equalcheck(compare1,compare2);
			count++;
			gcount++;
			if (color != 0 && check == 0){
				check = 1;
			}
		} 
		//These handle displaying any edge case displays, such as when
		//the difference occurs in the last line of data in the file.	
		if (check == 1){
			display(before1, before2, forecolor, (gcount)-count);
			gcount--;	
			display(current1, current2, colorcheck, gcount);
		} else if (check == 2){
			gcount--;	
			display(current1, current2, colorcheck, gcount);
		}

	} else {
		fprintf(stderr, "ERROR: One or more files cannot be opened!\n");
	}



	return (0);
}

//This function does a check on whether the values of the bytes are equal or not
//If not, we assign a 1 to the color array element that corresponds with the
//same element in the before/current arrays, so we are able to hilight it
//without checking for it in the display function itself.
int equalcheck (char compare1, char compare2){
	if (compare1 == compare2){
		return(0);
	} else {
		return(1);
	}
}

//This function handles the displaying of a single line of data, being able to
//reference the two arrays of which it will be using for data, and one in which
//it will be referencing what bytes to hilight.
void display(int *array1, int *array2, int *colorcheck, int gcount){
	//initializing local variables to use throughout the function.
	int countto    = 16;
	gcount = gcount - 1;
	int       count = 0;
	int        skip = 0;
	char       compare1;
	char       compare2;
	char          color;

	//This checks to see if gcount is not evenly divisible by 16, which 
	//indicates whether there is less than 16 bytes of data in the line
	//that is being printed.  This is done so we can handle correct
	//spacing in the output.
	while(gcount%16 != 0){
		countto--;
		gcount++;	
	}
	
	//the line header is printed out with the line number represented in 
	//hexidecimal.  Then we print out the first sixteen bytes of info by
	//iterating through the data arrays provided, checking to see if the
	//corresponding element in the color array is a zero or one.  If it is
	//a one, we then color the output green. (encountered a problem in the
	//evaluation file, where the eval file read the extra characters from
	//the ANSI color options, and produced mismatches when otherwise
	//output was correct)
	printf("%08x: ", gcount-16);
	while(count <= countto){
		
		if (*(colorcheck+count) == 0){
			fprintf(stdout, "%02hhx", *(array1+count));
		} else {
			fprintf(stdout, ANSI_FG_GREEN);
			fprintf(stdout, "%02hhx", *(array1+count));
			fprintf(stdout, ANSI_RESET);
		}

		skip++;

		count++;

		//handles the spacing between pairs of bytes.
		if(skip == 2){
			fprintf(stdout," ");
			skip = 0;
		}		
	}
	
	//This handles any extra spaces we need to pad partial output, so the
	//middle divider lines up correctly.
	count = countto;
	while (count < 15){
		fprintf(stdout, "  ");
		if (count%2 == 0){
			fprintf(stdout, " ");
		}
		skip++;
		count++;
	}

	//The divider is printed out before the process is done again for the
	//second array of data.
	fprintf(stdout, "| ");
	skip = 0;
	count = 0;

	while(count <= countto){

		if(skip == 2){
			fprintf(stdout," ");
			skip = 0;
		}		


		if (*(colorcheck+count) == 0){
			fprintf(stdout, "%02hhx", *(array2+count));
		} else {
			fprintf(stdout, ANSI_FG_GREEN);
			fprintf(stdout, "%02hhx", *(array2+count));
			fprintf(stdout, ANSI_RESET);
		}

		skip++;

		count++;

		}
	
	count = countto;
	while (count < 15){
		fprintf(stdout, "  ");
		if (count%2 == 0){
			fprintf(stdout," ");
		}
		skip++;
		count++;
	}	
	fprintf(stdout, "\n");
			
}

