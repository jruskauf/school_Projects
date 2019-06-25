#include "stack.h"

//////////////////////////////////////////////////////////////////////
//
//   cpstack() - duplicate a given stack (especially the state of
//               its contents), in a new stack.
//
//     behavior: in the event of an existing yet non-NULL newStack,
//               just fall though (do nothing), and generate the
//               appropriate status code(s).
//
//               be sure to utilize existing list and stack library
//               functions to facilitate your implementation. Do NOT
//               reinvent the wheel.
//
//               the top of the stack should follow the last node in
//               its underlying list.
//
//  status code: this function can generate the following status code
//                 DLL_SUCCESS:     normal operation
//                 DLL_EMPTY:       stack data element is empty
//                 DLS_SUCCESS:     normal operation
//                 DLS_CREATE_FAIL: *newStack already exists
//                 DLS_EMPTY:       stack is EMPTY
//                 DLS_NULL:        stack is NULL
//                 DLS_ERROR:       a failure was encountered
//                 DLS_INVALID:     stack does not exist
//
//         note: as with the other functions, you may use no more
//               than one return() statement per function.
//
//               do not count; navigate by comparison
//
code_t cpstack(Stack *curStack, Stack **newStack)
{
    //initializing status code to report an error in case of fall through
    code_t status = DLS_ERROR;
    //if stack is not null, create a new stack and set status to new stack's
    //return status.  by setting it to the status, we report a proper error
    //on fallthrough
    if(curStack != NULL){
	status = mkstack(newStack, 0);
	if(curStack -> top != NULL){
	    //If the top of the stack isn't null, then we copy the underlying
	    //data list to a temp variable, then set newStack -> data equal
	    //to the copied list, and set the top of the stack to the last of
	    //said list.
	    List *tmp = NULL;
	    cplist(curStack -> data, &tmp);
	    (*newStack) -> data = tmp;
	    (*newStack) -> top = tmp -> last;
	    status = DLS_SUCCESS | DLL_SUCCESS;
	}
    } else {
	status = status | DLS_NULL;
    }
    return (status);
}
