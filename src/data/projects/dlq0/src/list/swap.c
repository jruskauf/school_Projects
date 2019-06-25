#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// swapnode() - swap the position of two given nodes in a list, being
//              sure to appropriately adjust any and all pertinent
//              pointers to ensure list integrity following the
//              operation (including potential changes to the list's
//              own first and last pointers, along with connectivity
//              between the nodes from the start to end of the list).
//
//              be sure to utilize existing list and node library
//              functions to facilitate your implementation. Do NOT
//              reinvent the wheel.
//
//        note: you are NOT to just adjust node info values. You must
//              disconnect the identified nodes from the list and 
//              reconnect them- the node is our unit of transaction,
//              NOT the data it contains.
//
// status code: this function can generate the following status codes
//                DLN_NULL:    node is NULL
//                DLL_SUCCESS: normal operation
//                DLL_NULL:    list is NULL
//                DLL_EMPTY:   list is empty
//                DLL_ERROR:   something is NULL or EMPTY, or other
//                             error state encountered.
//                DLL_INVALID: invalid list state
//
//              as with the other functions, you may use no more
//              than one return() statement per function.
//
//              do not count; navigate by comparison
//
code_t  swapnode(List **myList, Node *posA, Node *posB)
{
    code_t status = DLL_ERROR;

    //If the list is not in a desired state, we print out an error.  otherwise
    //we continue on with the swapping.
    if(myList != NULL){
	if((*myList) != NULL){
	    if((*myList) -> lead != NULL){
		if (posA != posB){
		    
		    //copying the nodes we want to swap to temporary nodes.
		    Node *tmp1 = NULL;
		    Node *tmp2 = NULL;
		    Node *tmpPosA = NULL;
		    Node *tmpPosB = NULL;
		    cpnode(posA, &tmpPosA);
		    cpnode(posB, &tmpPosB);

		    //setting tmp1 to the lead, and then iterating through the
		    //list to the first position, and do the same for another
		    //node and the second position.
		    tmp1 = (*myList) -> lead;
		    while(tmp1 != posA && tmp1 != NULL){
			tmp1 = tmp1 -> right;
		    }
			
		    tmp2 = (*myList) -> lead;
		    while(tmp2 != posB && tmp2 != NULL){
			tmp2 = tmp2 -> right;
		    }
		    
		    //inserting the copied node of posB before or after posA,
		    //and then removing posA from the list.
		    if(tmp1 != (*myList) -> lead){
			insert(myList, tmp1, tmpPosB);
			obtain(myList, &tmp1);
		    } else {
			insert(myList, tmp1, tmpPosB);
			obtain(myList, &tmp1);
		    }				
		    //inserting the copied node of posA before or after posB,
		    //and then removing posB from the list.
		    if(tmp2 != (*myList) -> lead){
			insert(myList, tmp2, tmpPosA);
			obtain(myList, &tmp2);
		    } else {
			insert(myList, tmp2, tmpPosA);
			obtain(myList, &tmp2);
		    }
		    
		    status = DLL_SUCCESS;

		} else {
		    status = DLL_ERROR;
		}
	    } else {
		if (posA == NULL || posB == NULL){
		    status = DLL_EMPTY | status | DLN_NULL;
		} else {
		    status = DLL_EMPTY | status;
		}
	    }	
	} else {
	    status = status | DLL_NULL;
	}
    } else {
	status = DLL_INVALID | status;
    }
    return(status);
}
