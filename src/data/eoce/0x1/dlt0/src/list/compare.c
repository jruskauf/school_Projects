#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// compare() - a list library utility function to compare two lists,
//             and to return a result indicating equality, or the lack
//             thereof.
//
//       note: if difference is initially NULL, care should be taken
//             not to assign any values to it.
//
//             a difference of 0 indicates a NULL or EMPTY list is
//             our point of difference. Any actual list node
//             positions will start from 1 (be aware of this)
//
//             the condition of both lists should be reflected in
//             the code that is ultimately returned. In the event 
//             of a NULL or EMPTY list, those conditions trump 
//             any greater/less/equality status.
//
//   examples: a few examples for reference.
//
//             list1:        NULL
//             list2:        NULL
//             code:         CMP_L1_NULL  | CMP_L2_NULL
//             difference:   0
//
//             list1:        EMPTY
//             list2:        EMPTY
//             code:         CMP_L1_EMPTY | CMP_L2_EMPTY
//             difference:   0
//
//             list1:        NULL
//             list2:        EMPTY
//             code:         CMP_L1_NULL  | CMP_L2_EMPTY
//             difference:   0
//
//             list1:        EMPTY
//             list2:        NULL
//             code:         CMP_L1_EMPTY | CMP_L2_NULL
//             difference:   0
//
//             list1:        NULL
//             list2:        1 -> 2 -> NULL
//             code:         CMP_L1_NULL
//             difference:   0
//
//             list1:        EMPTY
//             list2:        1 -> 2 -> NULL
//             code:         CMP_L1_EMPTY
//             difference:   0
//
//             list1:        1 -> 2 -> NULL
//             list2:        NULL
//             code:         CMP_L2_NULL
//             difference:   0
//
//             list1:        1 -> 2 -> NULL
//             list2:        EMPTY
//             code:         CMP_L2_EMPTY
//             difference:   0
//
//             list1:        2 -> NULL
//             list2:        1 -> 2 -> NULL
//             code:         CMP_L1_GREATER | CMP_L2_LESS
//             difference:   1
//
//             list1:        1 -> NULL
//             list2:        1 -> 3 -> NULL
//             code:         CMP_L2_GREATER
//             difference:   2
//
//             list1:        1 -> 2 -> NULL
//             list2:        1 -> 3 -> NULL
//             code:         CMP_L1_LESS    | CMP_L2_GREATER
//             difference:   2
//
//             list1:        1 -> 3 -> NULL
//             list2:        1 -> 3 -> NULL
//             code:         CMP_EQUALITY
//             difference:   2
//
//             as with the other functions, you may use no more
//             than one return() statement per function.
//
//             do not count; navigate by comparison
//
code_t  compare(List *myList1, List *myList2, ulli *difference)
{
    code_t status = CMP_L1_NULL;
    ulli count = 0;
    //checking to see if the first list is empty or null, if so, proceed to more
    //errorchecking.  If second list is empty or null, proceed to more error 
    //checking.  If both lists are populated, proceed to comparing the lists.
    if(myList1 != NULL){
	if(myList1 -> lead != NULL){
	    if(myList2 != NULL){
	        if(myList2 -> lead != NULL){
		    //setting nodes to each of the list leads, and setting count
		    //to 1 to represent the place of difference (if any)
	            Node *tmp1 = NULL;
		    Node *tmp2 = NULL;
		    tmp1 = myList1 -> lead;
		    tmp2 = myList2 -> lead;
		    count = 1;
		    
		    //while the nodes equal the same value and are not null, we
		    //iterate through each list and add onto the count.
		    while ((tmp1 != NULL && tmp2 != NULL) && 
			   (tmp1 -> VALUE == tmp2 -> VALUE)){

			tmp1 = tmp1 -> right;
			tmp2 = tmp2 -> right;
			count++;
		    }
		    
		    //If difference is not null, we assign the point of
		    //difference we counted in the previous loop.
		    if(difference != NULL){
			if (tmp1 == NULL && tmp2 == NULL){
			    *difference = count - 1; 
			} else {
			    *difference = count;
			}
		    }
		    
		    //printing out the status codes based on point of difference
		    //and the values in the node's ending spots.
		    if(tmp1 == tmp2 || (tmp1 == NULL && tmp2 == NULL)){
			status = CMP_EQUALITY;
		    } else if(tmp1 > tmp2){
			status = CMP_L1_GREATER;

			if(tmp2 != NULL){
			    status = status | CMP_L2_LESS;
			}

		    } else if(tmp2 > tmp1){
			status = CMP_L2_GREATER;

			if(tmp1 != NULL){
			    status = CMP_L1_LESS | status;
			}
		    }
		} else {
		    status = CMP_L2_EMPTY;
		}
	    } else {
		status = CMP_L2_NULL;
	    }
	} else {
	    //error checking to see if second list is populated, empty, or null
	    status = CMP_L1_EMPTY;
	    if(myList2 != NULL){
    	        if(myList2 -> lead == NULL){
    		    status = status | CMP_L2_EMPTY;
	        }
	    } else {
	        status = status | CMP_L2_NULL;
	    }
	}
    } else {
	//checking to see if second list is populated, empty, or null
        if(myList2 != NULL){
    	    if(myList2 -> lead == NULL){
    		status = status | CMP_L2_EMPTY;
	    }
	} else {
	    status = status | CMP_L2_NULL;
	}
    }
    return(status);
}
