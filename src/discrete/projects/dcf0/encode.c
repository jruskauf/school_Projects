#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv)
{
    //////////////////////////////////////////////////////////////////
    //
    // Variable declarations
    //
    
    FILE *in                         = NULL;
    FILE *out                        = NULL;
    char *filename                   = NULL;
    char *basename		     = NULL;
    char *reserved		     = NULL;
    char     array[10]; 
    char     input =  0;
    char      test =  0;
    int      count =  0;
    int      tally =  1;
    int     gtally =  0;
    float outcount = 12;
    int    RLEspec =  1;
    int    stride  =  1;
    float   gcount =  0;
    float comprate =  0;
   

    //////////////////////////////////////////////////////////////////
    //
    // Command-line argument checking; if insufficient arguments, error out
    //
    if (argc < 3)
    {
        fprintf(stderr, "Error, insufficient arguments\n");
	exit(0);
    }

    //////////////////////////////////////////////////////////////////
    //
    // otherwise, argument is file name to encode
    //
    else
    {
	//assigning arguments to variables and opening of files for reading
	//and writing
	basename = argv[1];
	in  =  fopen(basename, "r");
	filename = argv[2];
	out = fopen(filename, "w+");
	
	//checking to see if the files are able to be opened, if not, spit out
	//an error
        if (in == NULL)
        {
            fprintf(stderr, "Error opening '%s' for reading.\n", basename);
            exit (1);
        }

	if (out == NULL){
	   fprintf(stderr, "Error opening '%s' for writing.\n", filename);
	}
    }

  
    //////////////////////////////////////////////////////////////////
    //
    // Your dcfX RLE v1 encoding implementation here
    //

    //printing out the information of the header that we want
    fprintf(out, "dcfX RLE%c%c%c", reserved, RLEspec, stride); 
    
    fprintf(out, "%c", strlen(basename));
    
    //iterating through the input filename to print it into the header    
    while (*basename){
	fprintf(out, "%c", (unsigned int) *basename++);
	outcount++;
    }
    
    //initializing input and test to use in the next while loop
    input = array[count] = fgetc(in);
    test = input;
    
    //This handles the generation of the byte pairs while the file has not
    //reached its end.
    while(!feof(in)){
	
	//resets the count so the array doesn't overflow its number of elements
	if (count >= 10){
	    count = 0;
	}
	
	//iterates the input before checking against test.  If they are not
	//then the byte pair will be printed out.  First the number of times
	//the same letter was encountered in sequence before the letter is then
	//printed out. If the tally is equal to 255, the biggest value that can
	//be held in a single byte in this case, then print it out and restart
	//the tally.
	count++;
	input = array[count] = fgetc(in);
	if (test != input && !feof(in)){
	    gtally = gtally + tally;
	    fprintf(out, "%c%c", tally, test);
	    count=0;
	    tally = 0;
	    test = input;
	    outcount = outcount + 2;
	}
	
	if (tally == 255){
	    fprintf(out, "%c%c", tally, test);
	    gtally = gtally + tally;
	    tally = 0;	
	    outcount = outcount + 2;
	}

	if (feof(in)){
	    gtally = gtally + tally;
	    fprintf(out,"%c%c", tally, test);
	    outcount = outcount + 2;
	}
	gcount++;
        tally++;	
    }

    //printing out of the file information, which has been tracked throughout
    //the code.
    basename = argv[1];
    fprintf(stdout, " input name length: %d bytes\n", strlen(basename));
    fprintf(stdout, "    input filename: %s\n", basename);
    fprintf(stdout, "output name length: %d bytes\n", strlen(filename));
    fprintf(stdout, "   output filename: %s\n", filename);
    fprintf(stdout, "      stride value: 1 byte\n");
    fprintf(stdout, "           read in: %.0f bytes\n", gcount);
    fprintf(stdout, "         wrote out: %.0f bytes\n", outcount);
    if (gcount > outcount){
	comprate = 100*(1 - (outcount / gcount));
        fprintf(stdout, "  compression rate: %.2f %\n", comprate);
    } else {
	comprate = 100*(1 - (gcount / outcount));
	fprintf(stdout, "    inflation rate: %.2f %\n", comprate);
    }

    //////////////////////////////////////////////////////////////////
    //
    // close open file pointers
    //
    fclose(in);
    fclose(out);

    return(0);
}
