#include "list.h"

//////////////////////////////////////////////////////////////////////
//
//   append() - add a new node to the given list after the node
//              at the indicated place. append() needs to manage
//              the necessary connections (pointers) to maintain list
//              integrity, along with ensuring the first and last
//              indicators of the list remain relevant and up-to-date.
//
//    behavior: do NOT create a list if NULL
//
// status code: this function can generate the following status codes
//                DLN_NULL:    newNode is NULL
//                DLN_ERROR:   place or newNode NULL (list not EMPTY)
//                DLL_SUCCESS: normal operation (success!)
//                DLL_NULL:    list is NULL
//                DLL_EMPTY:   list ends up EMPTY
//                DLL_ERROR:   error encountered
//                DLL_INVALID: invalid condition (place not in list)
//
//              as with the other functions, you may use no more
//              than one return() statement per function.
//
//              do not count; navigate by comparison
//
code_t append(List **myList, Node *place, Node *newNode)
{
    code_t status = DLL_ERROR;

    //checking if the list address is null, or if the list is null, or if
    //the list is empty.  If any of these, spit out the appropriate error,
    //or append to the list in the case of an empty list.
    if (myList != NULL){
	if(*myList != NULL){
	    if((*myList) -> lead != NULL){
		//if the place or new node is either null, spit out an error
		if(place != NULL && newNode != NULL){	
		    Node *tmp = NULL;
		    Node *tmp2 = NULL;
		    //if place equals the last place in the list, we assign
		    //the newNode after the last node in the list, and then
		    //reconnect it to keep list integrity.
		    if (place == (*myList) -> last){
			newNode -> left = (*myList) -> last;
			tmp = (*myList) -> last;
			(*myList) -> last = newNode;
			(*myList) -> last -> left = tmp;
			tmp -> right = (*myList) -> last;
			status = DLL_SUCCESS;
		    //If the node is elsewhere in the list, we find the place
		    //node and then append the newnode after it, connecting
		    //the list correctly to keep list integrity. Else if the
		    //newNode is null, or if place is not in the list, spit
		    //out an error.
		    } else if (place != (*myList) -> last){
			int tmpcount;
			tmpcount = find(*myList, place -> VALUE, &tmp);
			if (tmpcount == DLN_SUCCESS){
		    	    tmp2 = tmp -> right;
		   	    tmp -> right = newNode;
		   	    newNode -> left = tmp;
			    newNode -> right = tmp2;
			    tmp2 -> left = newNode;
			    status = DLL_SUCCESS;
			} else if(newNode == NULL){
			    status = status | DLN_NULL;
			} else if(place != NULL){
			    status = DLL_INVALID | DLN_ERROR;
			}	    
		    }
		} else {
		    if(newNode != NULL){
			status = DLL_INVALID | status | DLN_ERROR | DLN_NULL;
		    } else {
		        status = status | DLN_NULL;
		    }
		}
	    //If the list is in an empty state, append to it.  If the lead node
	    //is null, spit out an error, otherwise it succesfully appended.
	    } else if (place == (*myList) -> lead){			
		(*myList) -> lead = newNode;
		(*myList) -> last = newNode;
		if (newNode != NULL){
		    status = DLL_SUCCESS;
		} else {
		    status = DLL_EMPTY | status | DLN_NULL;
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
