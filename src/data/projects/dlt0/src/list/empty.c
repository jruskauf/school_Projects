#include "list.h"

//////////////////////////////////////////////////////////////////////
//
//     empty() - a list library function to clear an existing list of
//               any and all of its component nodes (deallocate them).
//               The list itself continues to exist, but is in an
//               empty state following the successful call to
//               empty().
//
//               be sure to utilize existing list and node library
//               functions to facilitate your implementation. Do NOT
//               reinvent the wheel.
//
//  status code: this function can generate the following status code
//                 DLL_SUCCESS: everything went according to plan
//                 DLL_EMPTY:   list is now empty (normal operation)
//                 DLL_NULL:    *myList is NULL
//                 DLL_ERROR:   a failure was encountered, NULL
//                 DLL_INVALID: invalid condition (myList NULL)
//
//               as with the other functions, you may use no more
//               than one return() statement per function.
//
//               do not count; navigate by comparison
//
code_t  empty(List **myList)
{
    code_t status = DLL_ERROR;
    //Checking to see if the list is in a proper state, if the list is either
    //null or empty, we return an error.  Else, we iterate through the list and
    //remove the nodes from the end of the list until the list is empty.
    if(myList != NULL){
	if((*myList) != NULL){
	    while((*myList) -> lead != NULL){
		Node *tmp = NULL;
		tmp = (*myList) -> last;
		obtain(myList, &tmp);
		rmnode(&tmp);
	    }
	    if((*myList) -> lead == NULL)
		status = DLL_EMPTY | DLL_SUCCESS;
	} else {
	    status = status | DLL_NULL;
	}
    } else {
	status = DLL_INVALID | status;
    }
    return(status);
}
