#include <stdio.h>
#include "list.h"

//////////////////////////////////////////////////////////////////////
//
//  display() - display the list according to mode(s).
//
//       modes: DISPLAY_FORWARD:   display the list forward
//              DISPLAY_NOPOSVALS: display with no positional values
//              DISPLAY_NOASCII:   display numeric values
//              DISPLAY_SEPS:      display separators between values
//              DISPLAY_POSVALS:   display with positional values
//              DISPLAY_BACKWARD:  display the list backward
//              DISPLAY_ASCII:     display ASCII characters
//              DISPLAY_NOSEPS:    do not display separators
//     
//        note: positional values are indexed from 0
//     
// status code: this function can generate the following status codes
//                DLL_SUCCESS:     normal (not NULL, EMPTY, ERROR)
//                DLL_NULL:        list is NULL
//                DLL_EMPTY:       list is EMPTY
//                DLL_ERROR:       non-populated list
//
//    behavior: on a NULL list,    output "(NULL)"
//              on an EMPTY list,  output "-> NULL" or "(EMPTY)" if
//                                 in ASCII mode
//              invalid mode:      MOD by 16 and do the result
//
//      format: output is to be against the left margin, on a single
//              line, ending with a newline character
//
//              DISPLAY_NOSEPS being set will remove all separators
//              and spaces from output, and positional values being
//              displayed change from "[#] " to "#:"
//
//              With DISPLAY_ASCII, separators are commas ', ', but
//              omitting the trailing comma at the end (there is no
//              terminating "NULL" displayed either)
//
//              Please see unit test output for examples. Note that
//              some mode combinations are nonsensical.
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
	    if (mode > 15){
		mode = mode%16;
	    }
	    //If the list is to be displayed forward, we iterate through the
	    //list displaying the value of each node.
	    if (mode == 0){
		tmp = myList -> lead;
		while (tmp != NULL){
		   fprintf(stdout,"%d -> ", tmp -> VALUE);
		   tmp = tmp -> right;
		}
		fprintf(stdout, "NULL\n");
	    //If the list is to be displayed backwards, we iterate through the
	    //list (by left instead of right) displaying the value of each node
	    } else if (mode == 2){
	        tmp = myList -> last;
		while (tmp != NULL){
		   fprintf(stdout,"%d -> ", tmp -> VALUE);
		   tmp = tmp -> left;
		}
		fprintf(stdout, "NULL\n");
	    //If the list is to be displayed forward with pos values, we display
	    //a count first, and then the value of the node.
    	    } else if (mode == 1){ 
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
   	    } else if (mode == 3){
	        pos = myList -> qty - 1;
		tmp = myList -> last;
		while (tmp != NULL){
		   fprintf(stdout,"[%d] %d -> ", pos, tmp -> VALUE);
		   tmp = tmp -> left;
		   pos--;
		}
		fprintf(stdout, "NULL\n");
	    //Displaying the list forward with ASCII characters
   	    } else if (mode == 4){
		tmp = myList -> lead;
		while (tmp -> right != NULL){
		   fprintf(stdout,"'%c', ", tmp -> VALUE);
		   tmp = tmp -> right;
		}
		fprintf(stdout,"'%c'\n", tmp -> VALUE);
	    //Displaying the list forward with ASCII characters and pos values
	    } else if (mode == 5){
		pos = 0;
		tmp = myList -> lead;
		while (tmp -> right != NULL){
		   fprintf(stdout,"[%d] '%c', ", pos, tmp -> VALUE);
		   tmp = tmp -> right;
		   pos++;
		}
		fprintf(stdout,"[%d] '%c'\n", pos, tmp -> VALUE);
	    //Displaying backward with ASCII characters
	    } else if (mode == 6){
		tmp = myList -> last;
		while (tmp -> left != NULL){
		   fprintf(stdout,"'%c', ", tmp -> VALUE);
		   tmp = tmp -> left;
		}
		fprintf(stdout,"'%c'\n", tmp -> VALUE);
	    //Displaying backwards with ASCII characters and pos values
	    } else if (mode == 7){
		pos = myList -> qty -1;
		tmp = myList -> last;
		while (tmp -> left != NULL){
		   fprintf(stdout,"[%d] '%c', ", pos, tmp -> VALUE);
		   tmp = tmp -> left;
		   pos--;
		}
		fprintf(stdout,"[%d] '%c'\n", pos, tmp -> VALUE);
	    //Displaying forward without seperators
	    } else if (mode == 8){
		tmp = myList -> lead;
		while (tmp != NULL){
		   fprintf(stdout,"%d", tmp -> VALUE);
		   tmp = tmp -> right;
		}
		fprintf(stdout, "NULL\n");
	    //Displaying forward without seperators and with pos values
	    } else if (mode == 9){
		pos = 0;
		tmp = myList -> lead;
		while (tmp != NULL){
		   fprintf(stdout,"%d:%d", pos, tmp -> VALUE);
		   tmp = tmp -> right;
		   pos++;
		}
		fprintf(stdout, "NULL\n");
	    //Displaying backwards without seperators
	    } else if (mode == 10){
		tmp = myList -> last;
		while (tmp != NULL){
		   fprintf(stdout,"%d", tmp -> VALUE);
		   tmp = tmp -> left;
		}
		fprintf(stdout, "NULL\n");
	    //displaying backwards without seperators and with pos values
	    } else if (mode == 11){
		pos = myList -> qty -1;
		tmp = myList -> last;
		while (tmp != NULL){
		   fprintf(stdout,"%d:%d", pos, tmp -> VALUE);
		   tmp = tmp -> left;
		   pos--;
		}
		fprintf(stdout, "NULL\n");
	    //Display forward with no seps and ASCII acharacters
	    } else if (mode == 12){
		tmp = myList -> lead;
		while (tmp -> right != NULL){
		   fprintf(stdout,"%c", tmp -> VALUE);
		   tmp = tmp -> right;
		}
		fprintf(stdout,"%c\n", tmp -> VALUE);
	    //Display forwaard with no seps and ASCII characters w/ pos values
	    } else if (mode == 13){
		pos = 0;
		tmp = myList -> lead;
		while (tmp -> right != NULL){
		   fprintf(stdout,"%d:%c", pos, tmp -> VALUE);
		   tmp = tmp -> right;
		   pos++;
		}
		fprintf(stdout,"%d:%c\n", pos, tmp -> VALUE);
	    //Displaying backwards with no seps and ascii characters
	    } else if (mode == 14){
		tmp = myList -> last;
		while (tmp -> left != NULL){
		   fprintf(stdout,"%c", tmp -> VALUE);
		   tmp = tmp -> left;
		}
		fprintf(stdout,"%c\n", tmp -> VALUE);
	    //Displaying backwards with no seps and ascii characters w/ pos val
	    } else if (mode == 15){
		pos = myList -> qty -1;
		tmp = myList -> last;
		while (tmp -> left != NULL){
		   fprintf(stdout,"%d:%c", pos, tmp -> VALUE);
		   tmp = tmp -> left;
		   pos--;
		}
		fprintf(stdout,"%d:%c\n", pos, tmp -> VALUE);
	    }

	    status = DLL_SUCCESS;
	} else {
	    if (mode == 8 || mode == 10){
		fprintf(stdout, "NULL\n");
	    } else if (mode >= 12 && mode <= 15){
		fprintf(stdout, "\n");
	    } else if ((mode < 4 || mode > 7) && mode < 15){
		fprintf(stdout, "-> NULL\n");
	    } else {
		fprintf(stdout, "(EMPTY)\n");
	    }
	    status = DLL_EMPTY;
	}
    } else {
	fprintf(stdout, "(NULL)\n");
	status = DLL_NULL;
    }
    return(status);
}
