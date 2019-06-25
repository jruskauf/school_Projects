#include <stdio.h>
#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// displayf() - display the list in a specified orientation, also
//			  with or without positional values (as indicated
//			  by the mode parameter).
//
//	   modes: 0 display the list forward, no positional values
//			  1 display the list forward, with positional values
//	 
//		note: positional values are indexed starting from 0
//	 
//	behavior: on a NULL list, output "NULL"
//			  if list is UNDEFINED, output "UNDEFINED"
//			  on an EMPTY list, output "-> NULL"
//			  on error (invalid mode): MOD by 2 and do the result
//				 (or the logical equivalent)
//
//	  format: output is to be on a single line, with node values
//			  space-padded. and separated by "->" sequences, flush
//			  against the left margin, of the forms:
//
// for forward:   val0 -> val1 -> val2 -> ... -> valN-1 -> valN -> NULL
//
//			  or, if being displayed with node positions:
//
// for forward: [0] val0 -> [1] val1 -> ... -> [N-1] valN-1 -> [N] valN -> NULL
//
//		note: ALL output ends with a newline character
//
void displayf(List *myList, int mode)

{
	//we set up tmp as a node to iterate through the list, and set count as
	//0 to represent the start of the list.
	Node *tmp  = NULL;
	int count = 0;
	
	//If the list is NULL, print out NULL, if its undefined, print out
	//undefined.  This is basic error checking so we don't end up seg
	//faulting all over the place.  Otherwise, if the mode is even, 
	//we print out the list without node positions, or if the mode is odd
	//we print out the list with node positions.
	if (myList == NULL){
		fprintf(stdout, "NULL\n");
	}else if(myList == UNDEFINED){
		fprintf(stdout, "UNDEFINED\n");
	}else if(mode%2 == 0){
		//We set tmp equal to the start of the list, and then check if
		//tmp is equal to NULL.  If no, we iterate through the list
		//displaying each value.  If yes, we print out a pointer null
		//to represent that the list is empty, as lead will be pointing
		//to tmp in an empty list.
		tmp = setpos(myList, count);
		if (tmp != NULL){
			while (tmp != NULL){
				fprintf(stdout, "%d -> ", tmp -> info);
				count++;
				tmp = setpos(myList, count);
			}
			fprintf(stdout, "NULL\n");
		} else {
			fprintf(stdout, "-> NULL\n");
		}
		
	}else if(mode%2 == 1){
		//This is the same as with mode 0, except we also print out the
		//node positions as well as the value contained within.
		tmp = setpos(myList, count);
		if (tmp != NULL){
			while (tmp != NULL){
				fprintf(stdout, "[%d] ", getpos(myList, tmp));
				fprintf(stdout, "%d -> ", tmp -> info);
				count++;
				tmp = setpos(myList, count);
			}
			fprintf(stdout, "NULL\n");
		} else {
			fprintf(stdout, "-> NULL\n");
		}

	}
}
