#include <stdio.h>
#include "list.h"

//////////////////////////////////////////////////////////////////////
//
//  display() - display the list in a specified orientation, also
//              with or without positional values (as indicated
//              by the mode parameter).
//
//       modes: DISPLAY_FORWARD:   display the list forward
//              DISPLAY_NOPOSVALS: display with no positional values
//              DISPLAY_POSVALS:   display with positional values
//              DISPLAY_BACKWARD:  display the list backward
//     
//        note: positional values are indexed from 0
//     
// status code: this function can generate the following status codes
//                DLL_SUCCESS:     normal (not NULL, EMPTY, ERROR)
//                DLL_NULL:        list is NULL
//                DLL_EMPTY:       list is EMPTY
//                DLL_ERROR:       non-populated list
//
//    behavior: on a NULL list,    output: "(NULL)"
//              on an EMPTY list,  output: "-> NULL"
//              invalid mode:      MOD by # of modes and do result
//
//      format: output is to be on a single line, with node values
//              space-padded. and separated by "->" sequences, flush
//              against the left margin, of the forms:
//
// for forward: 0 -> 1 -> 2 -> ... -> N-1 -> N -> NULL
//
//   backwards: N -> N-1 -> ... -> 2 -> 1 -> 0 -> NULL
//
//              or, if being displayed with node positions:
//
// for forward: [0] 0 -> [1] 1 -> ... -> [N-1] N-1 -> [N] N -> NULL
//
//   backwards: [N] N -> [N-1] N-1 -> ... -> [1] 1 -> [0] 0 -> NULL
//
//        note: ALL output ends with a newline character
//
//        note: backwards output differs from that of singly-linked list
//              displayb(); with dll0, all display() output is universal
//              regardless of orientation.
//
//              if a mode of DISPLAY_POSVALS | DISPLAY_BACKWARD, you
//              WILL need to count up the number of nodes in the list;
//              this is expected, and shouldn't happen anywhere else.
//
code_t display(List *myList, int mode)
{
    code_t status = DLL_ERROR;
    //Checking if list is either null or empty, and spitting out the
    //appropriate error.
    if (myList != NULL){
	if (myList -> lead != NULL){
	    Node *tmp = NULL;
	    int pos = 0;
	    //if the mode is greater than 3, we mod by 3 and do the remainder.
	    if (mode > 3){
		mode = mode%3;
	    }
	    //If the list is to be displayed forward, we iterate through the
	    //list displaying the value of each node.
	    if (mode == DISPLAY_FORWARD){
		tmp = myList -> lead;
		while (tmp != NULL){
		   fprintf(stdout,"%d -> ", tmp -> VALUE);
		   tmp = tmp -> right;
		}
		fprintf(stdout, "NULL\n");
	    //If the list is to be displayed backwards, we iterate through the
	    //list (by left instead of right) displaying the value of each node
	    } else if (mode == DISPLAY_BACKWARD){
	        tmp = myList -> last;
		while (tmp != NULL){
		   fprintf(stdout,"%d -> ", tmp -> VALUE);
		   tmp = tmp -> left;
		}
		fprintf(stdout, "NULL\n");
	    //If the list is to be displayed forward with pos values, we display
	    //a count first, and then the value of the node.
    	    } else if (mode == (DISPLAY_POSVALS | DISPLAY_FORWARD)){ 
		tmp = myList -> lead;
		while (tmp != NULL){
		   fprintf(stdout,"[%d] %d -> ", pos, tmp -> VALUE);
		   tmp = tmp -> right;
		   pos++;
		}
		fprintf(stdout, "NULL\n");
	    //If the list is to be displayed backwards with pos values, we first
	    //count up the nodes in the list, and then display a count iterating
	    //down as well as the value of the node.
   	    } else if (mode == (DISPLAY_POSVALS | DISPLAY_BACKWARD)){
	        tmp = myList -> last;
		while (tmp -> left != NULL){
		    tmp = tmp -> left;
		    pos++;
		}
		tmp = myList -> last;
		while (tmp != NULL){
		   fprintf(stdout,"[%d] %d -> ", pos, tmp -> VALUE);
		   tmp = tmp -> left;
		   pos--;
		}
		fprintf(stdout, "NULL\n");

   	    }
	    //reporting a succesful display
	    if(tmp == NULL && tmp == myList -> last -> right){
	    	status = DLL_SUCCESS;
	    }
	} else {
	    fprintf(stdout, "-> NULL\n");
	    status = DLL_EMPTY;
	}
    } else {
	fprintf(stdout, "NULL\n");
	status = DLL_NULL;
    }
    return(status);
}
