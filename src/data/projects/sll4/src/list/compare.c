#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// compare() - a list library utility function to compare two lists,
//             and to return a result indicating equality (or the lack
//             thereof), as well as the position of difference.
//
//       note: if pos is initially NULL, care should be taken not to
//             assign any values to it.
//
//             a pos of 0 indicates a NULL or EMPTY list is our 
//             point of difference. Any actual list node positions
//             will start from 1 (be aware of this difference from
//             setpos()/getpos()).
//
//             the condition of both lists should be reflected in
//             the code that is ultimately returned. In the event 
//             of a NULL or EMPTY list, those conditions trump 
//             any greater/less/equality status.
//
//             if a list is UNDEFINED, use that specific code
//
//   examples: a few examples for reference.
//
//             list1: NULL
//             list2: NULL
//             code:  CMP_L1_NULL  | CMP_L2_NULL
//             pos:   0
//
//             list1: EMPTY
//             list2: EMPTY
//             code:  CMP_L1_EMPTY | CMP_L2_EMPTY
//             pos:   0
//
//             list1: NULL
//             list2: EMPTY
//             code:  CMP_L1_NULL  | CMP_L2_EMPTY
//             pos:   0
//
//             list1: EMPTY
//             list2: NULL
//             code:  CMP_L1_EMPTY | CMP_L2_NULL
//             pos:   0
//
//             list1: NULL
//             list2: 1 -> 2 -> NULL
//             code:  CMP_L1_NULL
//             pos:   0
//
//             list1: EMPTY
//             list2: 1 -> 2 -> NULL
//             code:  CMP_L1_EMPTY
//             pos:   0
//
//             list1: 1 -> 2 -> NULL
//             list2: NULL
//             code:  CMP_L2_NULL
//             pos:   0
//
//             list1: 1 -> 2 -> NULL
//             list2: EMPTY
//             code:  CMP_L2_EMPTY
//             pos:   0
//
//             list1: 2 -> NULL
//             list2: 1 -> 2 -> NULL
//             code:  CMP_L1_GREATER | CMP_L2_LESS
//             pos:   1
//
//             list1: 1 -> NULL
//             list2: 1 -> 2 -> NULL
//             code:  CMP_L2_GREATER
//             pos:   2
//
//             list1: 1 -> 2 -> NULL
//             list2: 1 -> 3 -> NULL
//             code:  CMP_L1_LESS    | CMP_L2_GREATER
//             pos:   2
//
//             list1: 1 -> 3 -> NULL
//             list2: 1 -> 3 -> NULL
//             code:  CMP_EQUALITY
//             pos:   2
//
//             you are to have only ONE return statement for this
//             entire function. Change the existing one as needed.
//
uc compare(List *myList1, List *myList2, ulli *pos)
{
	//Setting nodes to be able to access the two lists, return variables
	//to build the finaly return statement with, and then a checking
	//variable to skip unneeded processes/break out of loops, and a position
	//variable to set *pos equal to at the end.
	Node *tmp1 = NULL;
	Node *tmp2 = NULL;
	char return1 = 0;
	char return2 = 0;
	char return3 = 0;
	int check = 0;
	int position = 0;
	
	//Here we check if the two lists are NULL, UNDEFINED, and EMPTY.  If
	//any of these are true, we set check to 1 to skip trying to compare
	//the list, and the position as zero to indicate a NULL/UNDEFINED/EMPTY
	//list is our point of difference.
	if (myList1 == NULL){
		return1 = CMP_L1_NULL;
		check = 1;
		position = 0;	
	} else if (myList1 == UNDEFINED){
		return1 = CMP_L1_UNDEFINED;
		check = 1;
		position = 0;
	} else if (myList1 -> lead == NULL){
		return1 = CMP_L1_EMPTY;
		check = 1;
		position = 0;
	} 	

	if (myList2 == NULL){
		return2 = CMP_L2_NULL;
		check = 1;
		position = 0;
	} else if (myList2 == UNDEFINED){
		return2 = CMP_L2_UNDEFINED;
		check = 1;
		position = 0;
	} else if (myList2 -> lead == NULL){
		return2 = CMP_L2_EMPTY;
		check = 1;
		position = 0;
	} 

	//This checks if we are to return a value of *pos or not, as if *pos is
	//NULL we shouldn't assign values to it.  It also checks if the lists
	//are valid lists to compare.
	if (check == 0 && pos != NULL){
		//We set the nodes to the start of each list.  Then, we use a 
		//while loop that constantly checks to see if tmp1 or tmp2 hits
		//null, or check does not equal zero.  That will kick it out of
		//the loop and then continue onto other checks.
		tmp1 = myList1 -> lead;
		tmp2 = myList2 -> lead;
		while ((tmp1 != NULL && tmp2 != NULL) && check == 0){
			//These check to see if the lists are equal or not,
			//setting return variables as to build the final return
			//statement.  If one list is greater or less than the 
			//other, we kick out of the loop as we report the 
			//position is at in the list.  Otherwise we move onto
			//the next pair of nodes.
			if (tmp1 -> info == tmp2 -> info){
				return3 = CMP_EQUALITY;
			} else if (tmp1 -> info > tmp2 -> info){
				return1 = CMP_L1_GREATER;
				return2 = CMP_L2_LESS;
				check = 1;
			} else if (tmp1 -> info < tmp2 -> info){
				return1 = CMP_L1_LESS;
				return2 = CMP_L2_GREATER;
				check = 1;
			}
			position = position + 1;
			tmp1 = tmp1 -> right;
			tmp2 = tmp2 -> right;
		}
		*pos = position;
	} else if (check == 0){
		//Does the same as above if *pos is equal to null, but doesn't
		//return a positional value to *pos.
		tmp1 = myList1 -> lead;
		tmp2 = myList2 -> lead;
		while ((tmp1 != NULL && tmp2 != NULL) && check == 0){
			if (tmp1 -> info == tmp2 -> info){
				return3 = CMP_EQUALITY;
			} else if (tmp1 -> info > tmp2 -> info){
				return1 = CMP_L1_GREATER;
				return2 = CMP_L2_LESS;
				check = 1;
			} else if (tmp1 -> info < tmp2 -> info){
				return1 = CMP_L1_LESS;
				return2 = CMP_L2_GREATER;
				check = 1;
			}
			tmp1 = tmp1 -> right;
			tmp2 = tmp2 -> right;
		}
	}
	
	//If pos does not equal zero, we check if the nodes we stopped on are
	//null or not.  If one list is null, we report the other as being 
	//greater if it has a valid value present, setting a return statement
	//that overrides what we previously were building.  Otherwise, we use
	//the statement we build in the While loop.  We also add one to *pos to
	//account for the extra check, unless pos was initially equal to NULL.
	//Then we just compare without returning a position to *pos.
	if (pos != NULL){
		if (tmp1 != NULL && tmp2 == NULL){
			return3 = CMP_L1_GREATER;
			*pos = position + 1;
		} else if (tmp1 == NULL && tmp2 != NULL){
			return3 = CMP_L2_GREATER;
			*pos = position + 1;
		} else {
			return3 = return1|return2;
		}
	} else {
		if (tmp1 != NULL && tmp2 == NULL){
			return3 = CMP_L1_GREATER;
		} else if (tmp1 == NULL && tmp2 != NULL){
			return3 = CMP_L2_GREATER;
		} else {
			return3 = return1|return2;
		}
	}
	return(return3);
}
