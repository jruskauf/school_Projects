#include <stdio.h>
#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// displayb() - display the list in a reversed orientation, also
//              with or without positional values (as indicated
//              by the mode parameter).
//
//       modes: 0 display the list backward, no positional values
//              1 display the list backward, with positional values
//     
//        note: positional values are indexed starting from 0
//     
//    behavior: on a NULL list, output "NULL"
//              if list is UNDEFINED, output "UNDEFINED"
//              on an EMPTY list, output "NULL <-"
//              on error (invalid mode): MOD by 2 and do the result
//                 (or the logical equivalent)
//
//      format: output is to be on a single line, with node values
//              space-padded. and separated by "<-" sequences, flush
//              against the left margin, of the forms:
//
//   backwards:   NULL <- 9 <- 7 <- 6 <- 4
//
//              or, if being displayed with node positions:
//
//   backwards:   NULL <- [3] 9 <- [2] 7 <- [1] 6 <- [0] 4
//
//        note: ALL output ends with a newline character
//
void displayb(List *myList, int mode)
{
	//Setting up tmp to iterate through the list, and set count initially at
	//0.
	Node *tmp = NULL;
	int count = 0;
	
	//Checking if the list is NULL or UNDEFINED, and reporting if either is
	//true.  Then we check the mode, modding by 2 if we aren't given 0 or 1.
	if (myList == NULL){
		fprintf(stdout, "NULL\n");
	}else if(myList == UNDEFINED){
		fprintf(stdout, "UNDEFINED\n");
	}else if (mode%2 == 0){
		//Count is set to represent the end of the list, and then tmp
		//is set to the last node in the list.  Then if tmp does not
		//point to NULL, we iterate from the last node of the list to
		//the first, printing out values.  If tmp does point to NULL,
		//indicating an empty list, we print out only NULL <-
		count = getpos(myList, myList -> last);
		tmp = setpos(myList, count);
		if (tmp != NULL){
			fprintf(stdout, "NULL");
			while (count >= 0){
				fprintf(stdout, " <- %d", tmp -> info);
				count--;
				tmp = setpos(myList, count);
			}
			fprintf(stdout, "\n");
		} else {
			fprintf(stdout, "NULL <-\n");
		}
	} else if(mode%2 == 1){
		count = getpos(myList, myList -> last);
		tmp = setpos(myList, count);
		//Only difference here is we print out a positional value in
		//front of the value of the contents of the node
		if (tmp != NULL){
			fprintf(stdout, "NULL");
			while (count >= 0){
				fprintf(stdout, " <- [%d]", getpos(myList, tmp));
				fprintf(stdout, " %d", tmp -> info);
				count--;
				tmp = setpos(myList, count);
			}
			fprintf(stdout, "\n");
		} else {
			fprintf(stdout, "NULL <-\n");
		}
	}	
}
