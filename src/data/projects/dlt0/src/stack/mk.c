#include "stack.h"

//////////////////////////////////////////////////////////////////////
//
// mkstack() - allocate, initialize, and return a pointer to
//             the newly created stack.
//
//       note: the second parameter is to be the created stack's
//             maximum size (upper bound).
//
//             be sure to utilize existing list and stack library
//             functions to facilitate your implementation. Do NOT
//             reinvent the wheel.
//
//             the top of the stack should follow the last node in
//             its underlying list.
//
//       size: a stack size of 0 will indicate an unbounded stack
//             > 0 will limit the total number of nodes in the stack
//
//   behavior: in the event of an existing yet non-NULL newStack,
//             just fall though (do nothing), and generate the
//             appropriate status code(s).
//
//status code: this function can generate the following status codes:
//                 DLL_SUCCESS:     normal operations
//                 DLL_EMPTY:       result of normal operation
//                 DLS_SUCCESS:     normal operations
//                 DLS_EMPTY:       result of normal operation
//                 DLS_CREATE_FAIL: error on creation
//                 DLS_NULL:        stack remains in NULL state
//                 DLS_ERROR:       an error has taken place
//                 DLS_INVALID:     stack does not exist
//
//       note: as with the other functions, you may use no more
//             than one return() statement per function.
//
code_t mkstack(Stack **newStack, ulli size)
{
    //Setting initial error code in the case of fall through
    code_t status = DLS_ERROR;
    List *data = NULL;
    //checking if stack exists and is null, if either of these arent true
    //we fall through and give an appropriate error message.
    if(newStack != NULL){
	if((*newStack) == NULL){
	    //mallocing out a new stack in the instance of an existent yet
	    //null list, as well as creating a new list for the underlying
	    //data to be used.  set stack size to what's given.
	    (*newStack) = (Stack*)malloc(sizeof(Stack));
	    mklist(&data);
	    (*newStack) -> data = data;
	    (*newStack) -> top = data -> last;
	    (*newStack) -> size = (size > 0) ? size : 0;
	    //If list is still null, report an error, otherwise report success
	    if(newStack == NULL){
		status = status | DLS_NULL;
	    } else {
		status = DLS_EMPTY | DLS_SUCCESS | DLL_EMPTY | DLL_SUCCESS;
	    }
	} else {
	    status = status | DLS_CREATE_FAIL;
	}
    } else {
	status = DLS_INVALID | status;
    }	
    return (status);
}
