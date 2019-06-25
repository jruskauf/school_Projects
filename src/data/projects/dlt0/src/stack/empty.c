#include "stack.h"

//////////////////////////////////////////////////////////////////////
//
//  isempty() - return an indication as to stack's emptiness
//
//              be sure to utilize existing list and stack library
//              functions to facilitate your implementation. Do NOT
//              reinvent the wheel.
//
//              the top of the stack should follow the last node in
//              its underlying list.
//
// status code: this function can generate the following status codes
//                  DLS_SUCCESS:  normal operations
//                  DLS_OVERFLOW: stack is populated
//                  DLS_NULL:     stack is NULL
//                  DLS_EMPTY:    stack is empty
//                  DLS_ERROR:    error encountered (stack is NULL)
//
//        note: as with the other functions, you may use no more
//              than one return() statement per function.
//
code_t isempty(Stack *myStack)
{
    //setting status to error in case of fallthrough.
    code_t status = DLS_ERROR;
    //if the stack is not null, report on whether it is populated or empty.
    //Otherwise, fall through and report that stack is null.
    if(myStack != NULL){
	if(myStack -> top != NULL){
	    status = DLS_OVERFLOW | DLS_SUCCESS;
	} else {
	    status = DLS_EMPTY | DLS_SUCCESS;
	}
    } else {
	status = status | DLS_NULL;
    }
    return (status);
}
