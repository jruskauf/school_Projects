#include "list.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
//
//   obtain() - take and isolate indicated node out of list, through
//              a careful adjustment of necessary pointers. obtain()
//              needs to maintain list integrity.
//              
//error states: NULL or EMPTY initial list, NULL thatNode. In such a
//              case, do not modify the list.
//
// status code: this function can generate the following status codes
//                  DLN_NULL:    *thatNode is NULL
//                  DLN_INVALID: thatNode is NULL
//                  DLN_ERROR:   *thatNode not in list
//                  DLL_SUCCESS: normal operation
//                  DLL_NULL:    list is NULL
//                  DLL_ERROR:   error encountered (any error)
//                  DLL_INVALID: cannot proceed (myList is NULL)
//                  DLL_EMPTY:   list is EMPTY (not directly an
//                               error, although likely is associated
//                               with error condition)
//
//              as with the other functions, you may use no more
//              than one return() statement per function.
//
//              do not count; navigate by comparison
//
code_t  obtain(List **myList, Node **thatNode)
{
    
    code_t status = DLL_ERROR;
    code_t node   = DLN_ERROR;
    //checking if list and node are in proper status to commence operations.
    //If not, then we print out an error status, and set thatNode to null.
    if (myList != NULL){
	if((*myList) != NULL){
	    if((*myList) -> lead != NULL){
	        if(thatNode != NULL){
		    //setting up nodes to be used.  then setting a status code 
		    //to node so as to obtain a node that is neither the lead
		    //or the last and is in the list, if not the list error 
		    //falls through.
		    Node *tmp  = NULL;
		    Node *tmp2 = NULL;
		    Node *tmp3 = NULL;
		    node       = find((*myList), (*thatNode) -> VALUE, &tmp);
		    tmp        = (*myList) -> lead;
		    //iterate through the list until at thatNode is reached or
		    //tmp hits null.  find only finds the value of the node, and
		    //not necessarily the node at the address we want.
		    while (tmp != (*thatNode) && tmp != NULL){
		        tmp = tmp -> right;
		    }
		    
		    //sobtaining the lead node and making sure to reconnect
		    //the list back together so list integrity is preserved.
		    if (tmp == (*myList) -> lead){
			if ((*myList) -> lead -> right != NULL){
			    (*myList) -> lead = (*myList) -> lead -> right;
			    (*myList) -> lead -> left = NULL;
			    tmp -> right              = NULL;
			    tmp -> left               = NULL;
			    (*myList) -> qty--;
			    status                    = DLL_SUCCESS;
			} else {
			    (*myList) -> lead = NULL;
			    (*myList) -> last = NULL;
			    tmp -> right      = NULL;
			    tmp -> left       = NULL;
			    (*myList) -> qty--;
			    status            = DLL_EMPTY | DLL_SUCCESS;
			}
		    //obtaining the last node and making sure to reconnect
		    //the list back together so list integrity is preserved.
		    } else if (tmp == (*myList) -> last){
			tmp2                       = (*myList) -> last -> left;
			(*myList) -> last          = tmp2;
			(*myList) -> last -> right = NULL;
			tmp -> right               = NULL;
			tmp -> left                = NULL;
			(*myList) -> qty --;
			status                     = DLL_SUCCESS;
		    //If the node is neither last or lead, and is present in
		    //the list, then set nodes to the left and right of
		    //the node we want, and then connect the list.
		    } else if(node == DLN_SUCCESS && tmp != NULL){
			tmp3          = tmp -> right;
			tmp2          = tmp -> left;
			tmp2 -> right = tmp3;
			tmp3 -> left  = tmp2;
			tmp -> right  = NULL;
			tmp -> left   = NULL;
			(*myList) -> qty--;
			status        = DLL_SUCCESS;
		    }
	        }
	    } else {
		status   = status | DLL_EMPTY;
		thatNode = NULL;
	    }
	} else {
	    status   = status | DLL_NULL;
	    thatNode = NULL;
	}
    } else {
	status   = DLL_INVALID | status;
	thatNode = NULL;
    }
    return(status);
}
