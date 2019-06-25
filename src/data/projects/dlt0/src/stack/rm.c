#include "stack.h"

//////////////////////////////////////////////////////////////////////
//
//  rmstack() - unset, nullify members, and de-allocate the given 
//              stack.
//
//              be sure to utilize existing list and stack library
//              functions to facilitate your implementation. Do NOT
//              reinvent the wheel.
//
//              the top of the stack should follow the last node in
//              its underlying list.
//
// status code: this function can generate the following status codes
//                  DLL_SUCCESS: normal operation
//                  DLL_NULL:    stack data element is NULL
//                  DLS_SUCCESS: no problems encountered
//                  DLS_NULL:    normal operation
//                  DLS_INVALID: stack does not exist
//                  DLS_ERROR:   error encountered (or stack was
//                               already NULL)
//
//        note: as with the other functions, you may use no more
//              than one return() statement per function.
//
code_t rmstack(Stack **oldStack)
{
    code_t status = DLS_ERROR;
    //if the stack does not exist, is null, or is empty, report as such.  if
    //empty, then we report a success after nulling the stack.
    if(oldStack != NULL){
	if(*oldStack != NULL){
	    if((*oldStack) -> top != NULL){
		//If the stack is populated, we pop off and remove the top of
		//the stack, and do so until the list is empty.  Then we null
		//the stack and report a success.
		Node *tmp = NULL;
		while((*oldStack) -> data -> last != NULL){
		    pop(oldStack, &tmp);
		    rmnode(&tmp);
		}
		(*oldStack) = NULL;
		status = DLS_NULL | DLS_SUCCESS | DLL_NULL | DLL_SUCCESS;
	    } else {
		(*oldStack) = NULL;
		status = DLS_NULL | DLS_SUCCESS | DLL_NULL | DLL_SUCCESS;
	    }
	} else {
	   status = status | DLS_NULL;
	}	
    } else {
	status = DLS_INVALID | status;
    }
    return (status);
}
