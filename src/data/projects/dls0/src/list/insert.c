#include "list.h"

//////////////////////////////////////////////////////////////////////
//
//   insert() - add a new node to the given list before the node
//              at the indicated place. insert() needs to manage
//              the necessary connections/pointers) to maintain list
//              integrity, along with ensuring the start and end
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
code_t insert(List **myList, Node *place, Node *newNode)
{
    code_t status = DLL_ERROR;
    //checking if the list address is null, or if the list is null, or if
    //the list is empty.  If any of these, spit out the appropriate error,
    //or insert to the list in the case of an empty list. 
    if (myList != NULL){
	if(*myList != NULL){
	    if((*myList) -> lead != NULL){
		//if the place or new node is either null, spit out an error
		if(place != NULL && newNode != NULL){	
		    Node *tmp = NULL;
		    Node *tmp2 = NULL;
		    //if place equals the first place in the list, we assign
		    //the newNode before the first node in the list, and then
		    //reconnect it to keep list integrity.
		    if (place == (*myList) -> lead){
			newNode -> right = (*myList) -> lead;
			tmp = (*myList) -> lead;
			(*myList) -> lead = newNode;
			(*myList) -> lead -> right = tmp;
			tmp -> left = (*myList) -> lead;
			(*myList) -> qty++;
			status = DLL_SUCCESS;
		    
		    //if the node is elsewhere in the list, we find the place
		    //node and then insert the newNode before it, connecting
		    //the list correctly to keep list integrity.  Else if the
		    //NewNode is null, or if place is not in the list, spit
		    //out an error.
		    } else if (place != (*myList) -> lead){
			int tmpcount;
			tmpcount = find(*myList, place -> VALUE, &tmp);
			if (tmpcount == DLN_SUCCESS){
		    	    tmp2 = tmp -> left;
		   	    tmp -> left = newNode;
		   	    newNode -> right = tmp;
			    newNode -> left = tmp2;
			    tmp2 -> right = newNode;
			    (*myList) -> qty++;
			    status = DLL_SUCCESS;
			} else if(newNode == NULL){
			    status = status | DLN_NULL;
			} else if(place != NULL){
			    status = DLL_INVALID | DLN_ERROR;
			}	    
		    }
		} else {
		    if (newNode != NULL){
			    status = DLL_INVALID | status | DLN_ERROR | DLN_NULL;
		    } else {
			    status = status | DLN_NULL;
		    }
		}
	    //if the list is in an empty state, insert to it.  If the lead node
	    //is null, spit out an error, otherwise it succesfully inserted.
	    } else if (place == (*myList) -> lead){			
		(*myList) -> lead = newNode;
		(*myList) -> last = newNode;
		if (newNode != NULL){
		    status = DLL_SUCCESS;
		    (*myList) -> qty++;
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
