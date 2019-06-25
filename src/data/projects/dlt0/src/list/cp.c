#include "list.h"

//////////////////////////////////////////////////////////////////////
//
//    cplist() - duplicate a given list (especially the state of
//               its contents), in a new list.
//
//               be sure to utilize existing list and node library
//               functions to facilitate your implementation. Do NOT
//               reinvent the wheel.
//
//  status code: this function can generate the following status code
//                 DLL_SUCCESS:       normal operation
//                 DLL_ALREADY_ALLOC: *newList already exists
//                 DLL_EMPTY:         cur & ending *newList are EMPTY
//                 DLL_NULL:          oldList or *newList are NULL
//                 DLL_ERROR:         an error was encountered
//                 DLL_INVALID:       newList doesn't exist
//
//               as with the other functions, you may use no more
//               than one return() statement per function.
//
//               do not count; navigate by comparison
//
code_t cplist(List *oldList, List **newList)
{
    code_t status = DLL_ERROR;
    //if the newList is not NULL, undefined, we continue with operations.
    //Otherwise spit out an error.
    if ((newList   != NULL)      && 
       (newList    != UNDEFINED) && 
       ((*newList) != UNDEFINED))
    {
	//if the newlist contents are NULL we proceed.  Otherwise, spit out
	//an error
	if ((*newList) == NULL)
	{
	    //if the oldlist is not null or UNDEFINED we proceed.  otherwise
	    //spit out an error
	    if (oldList != NULL        &&
	       (oldList != UNDEFINED))
	    {
		//if the newList is not already allocated, allocate a new list
		//and continue.  Otherwise, check if both lists are empty or
		//spit out an error.
		mklist(newList);
		if ((*newList) != NULL && oldList -> lead != NULL)
		{
		    //tmp1 points to a node in the oldlist, while tmp2
		    //has a node copied to it as it builds the new list.
		    Node *tmp1 = NULL;
		    Node *tmp2 = NULL;
		    tmp1 = oldList -> lead;
		    tmp2 = (*newList) -> lead;
		    while (tmp1 != NULL && status == DLN_SUCCESS){
		    	status = cpnode(tmp1, &tmp2);
			tmp1 = tmp1 -> right;
			tmp2 = tmp2 -> right;
			if(tmp1 == oldList -> last)
			    (*newList) -> last = tmp2;
		    }
		    display((*newList), 0);
		    status = DLL_SUCCESS;	 
		}
		//if the newlist is empty, and the oldlist is empty, report a
		//success.
		else if ((*newList) != NULL && oldList -> lead == NULL){
		   status = DLL_EMPTY | DLL_SUCCESS;
		}
		else 
		{   
		    status = DLL_ERROR | DLL_MALLOC_FAIL;
		    status = status | DLL_NULL;
		}
	    }
	    else if (oldList == NULL)
	    {
		status = DLL_ERROR | DLL_NULL;
	    }
	}
	else
            status = status | DLL_ALREADY_ALLOC;
    }
    else
        status = status | DLL_INVALID;

    return (status);
}
