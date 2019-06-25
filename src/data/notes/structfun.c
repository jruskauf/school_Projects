#include <stdio.h>
#include <stdlib.h>

// Defining unsigned char as "uc" to help save space
typedef unsigned char uc;

///////////////////////////////////////////////////////////////////////////////
// When setting up a struct, you must set up the template globally, and must
// always terminate with a ";".  This is not unlike declaring a function 
// prototype.
//
struct box
{
	uc *sides;
	uc  numsides;
	int perimeter;;
};

///////////////////////////////////////////////////////////////////////////////
// By using typedef, you can assign "struct box" to a shorter name, which
// can help with code neatness as well as code size, given a large enough
// name such as "unsigned char" (see above).
//
typedef struct box Box;
//typedef struct box box_t;

int main()
{
	// Local variable in main is an instance of struct box
	struct box square;
	// or...
	// Box square;
	unsigned char input;	
	int index;

	// Basic grabbing of input using fscanf, and a basic error checking
	// statement.	
	fprintf (stdout, "How many sides do you choose? ");
	fscanf (stdin, "%hhu", &input);
	if (input <= 2)
	{
		fprintf (stdout, "You chose... poorly\n");
		exit (1);
	}
	
	// assigning the variable of input to square.numsides, or the variable
	// mumsides contained withing struct box
	square.numsides = input;

	// This is grabbing the value of the memory to be used, which is 
	// dependent on the type of data (Unsigned Char being 1 byte in size)
	// and how many times you call it (value of square.numsides)
	square.sides  = (uc *) malloc (sizeof (uc) * square.numsides);
	
	square.perimeter = 0;

	///////////////////////////////////////////////////////////////////////
	// This loop runs for how many sides you chose, and assigns the input
	// to input, which is then processed into the perimeter stored in
	// square.perimeter
	//
	// A point about good coding, and taking into account how things can
	// be optimized.  In this loop index is initiliazed at 1, so in the
	// fprintf statement contained within it index didn't have to have a 
	// "+1" to satisfy 
	//
	for (index = 1; index <= square.numsides; index+=1)
	{
		fprintf (stdout, "How many long is side #%d? ", index);
		fscanf (stdin, "%hhu", &input);
		if (input <= 0)
		{
			fprintf (stdout, "You chose... poorly\n");
			exit (index + 1);
		}
		*(square.sides + (index - 1)) = input;
		square.perimeter       += *(square.sides + (index - 1));
	}

	// Prints the calculated perimeter and number of sides you chose,
	// along with the side number and its length
	fprintf (stdout, "Perimeter is: %d\n", square.perimeter);
	fprintf (stdout, "with sides of: \n");
	
	
	for (index = 0; index < square.numsides; index++)
	{
		fprintf (stdout, "\tside #%d is: %hhu\n", (index + 1), 
							 *(square.sides + index));
	}
	fprintf (stdout, "\n");
	

	// Don't forget to free the memory you alocated, so you do not have
	// memory being eaten up by the demons.
	free (square.sides);


	return(0);
}
