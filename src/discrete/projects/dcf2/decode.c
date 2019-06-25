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
    int        iter =  0;
    char     letter =  0;
    char header[12] = {0x64,0x63,0x66,0x58,0x20,0x52,0x4c,0x45,0x00,0x01,0x01};
    char       test =  0;
    int       count =  0;
    int      gtally =  0;
    float  outcount =  0;
    int     RLEspec =  1;
    int     stride  =  1;
    float    gcount =  1;
    float  comprate =  0;

    //////////////////////////////////////////////////////////////////
    //
    // Command-line argument checking; if insufficient arguments, error out

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

	//checking to see fi the files are able to be opened, if not, spit out
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
    // Your dcfX RLE v1 decoding implementation here
    //
 
    //iterate through the first eleven bytes of the header and check them
    //against what we should expect to be there.  if its different, spit out
    //an error.
    while(count <= 10){
	if(fgetc(in) != header[count]){
	    if (count == 9){
		printf("version mismatch!");
	        exit(3);
	    }
	    printf("invalid data format detected! aborting process...\n");
	    exit(2);
	}
	gcount++;
	count++;
    }

    //setting iteration equal to the length of the filename stored in the 
    //encoded file, and resetting to the beginning of the array
    iter = fgetc(in); 
    count = 0;

    //for the length of the file, assign one character to each array element
    for(iter; iter > 0; iter--){	
	header[count] = fgetc(in);
	count++;
	gcount++;
    }

    //if there is no data after the header, display error and exit
    if(feof(in)){
	printf("empty data segment\n");
	exit(4);
    }

    //if the string stored in header does not equal the filename provided, set
    //the filename to the header so we make sure the output is going back to the
    //right file
    if (header != filename){
	filename = header;
    }

    //decompressing the data while end of file has not been reached
    while(!feof(in)){
	
	//setting variables iter and letter, iter is the number of times that
	//letter will be printed out, as each fetches one part of the 2 byte
	//pairings.
	iter = fgetc(in);
        if(!feof(in)){
	    gcount++;
	}

    	letter = fgetc(in);
	if(!feof(in)){
	    gcount++;
	}

	//while iter is greater than zero, print out letter into the output file
	for (iter; iter > 0; iter--){
	    fprintf(out, "%c", letter);
	    outcount++;
	}
    }
 
    //printing out of the file information, which has been tracked throughout
    //the code
    basename = argv[1];
    fprintf(stdout, " input name length: %d bytes\n", strlen(basename));
    fprintf(stdout, "    input filename: %s\n", basename);
    fprintf(stdout, "output name length: %d bytes\n", strlen(filename));
    fprintf(stdout, "   output filename: %s\n", filename);
    fprintf(stdout, "       header text: dcfX RLE v1\n");
    fprintf(stdout, "      stride value: 1 byte\n");
    fprintf(stdout, "           read in: %.0f bytes\n", gcount);
    fprintf(stdout, "         wrote out: %.0f bytes\n", outcount);
    if (gcount >= outcount){
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

// i thought i would leave a little note here explaining why my progress with
// this project has not been the greatest.  I don't feel comfortable talking
// about this out in the open where other people possibly overhear what im going
// through.  I found out my girlfriend got sexually harassed over the weekend
// over at her college up in the Adirondacks, so i've been off kilter since 
// saturday (hence why i turned in sln1 later than i would have liked, i planned
// to have it done saturday).  I also had my room raided by police earlier this
// week due to my roommates doing shit they shouldn't, and i've had to go talk
// to the dean to get this cleared up.  So suffice to say i've been under an
// abnormal amount of mental and emotional stress with no real chance to work
// through it in a healthy manner.  While i know this is probably no excuse for
// yet another late project, i thought it pertinent to provide, in essence, a 
// "status check" on how i am currently fairing outside of class in a space
// where no one but you will see this but you.  I'll try and get this stupid 
// "off by one" error i seem to have hard-coded into myself fixed, so i'm 
// turning in projects on time from now on.
