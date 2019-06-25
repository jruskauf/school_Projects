#include "stack.h"

//////////////////////////////////////////////////////////////////////
//
//     peek() - read node off top of stack (do not modify stack)
//              passing back a COPY of the node that is read
//
//              be sure to utilize existing list and stack library
//              functions to facilitate your implementation. Do NOT
//              reinvent the wheel.
//
//              peekNode, if it exists, will be discarded in favor
//              of information obtained from the stack (so no need
//              to pre-NULL the value)
//
//              the top of the stack should follow the last node in
//              its underlying list.
//
// status code: this function can generate the following status codes
//                  DLN_INVALID: peeknode doesn't exist
//                  DLS_SUCCESS: normal operation
//                  DLS_NULL:    stack is NULL
//                  DLS_EMPTY:   stack is EMPTY (not an error)
//                  DLS_ERROR:   stack is NULL or other error state
//
//        note: as with the other functions, you may use no more
//              than one return() statement per function.
//
code_t peek(Stack *myStack, Node **peekNode)
{
    code_t status = DLS_ERROR;
    //if the stack is null, fall through and report an error, otherwise continue
    if(myStack != NULL){
	//if stack is not empty, continue.  Otherwise, check if peeknode exists,
	//and report on its existence.
        if(myStack -> top != NULL){
	    //If peeknode does not equal null, then we copy the last node in the
	    //data list and set peeknode to that isolated node.  Otherwise, we
	    //spit out an error message if peeknode already exists.
	    if(peekNode != NULL){
		Node *tmp = NULL;
		List *ltmp = myStack -> data;
		cpnode(ltmp -> last, &tmp);
		tmp -> left = NULL;
		tmp -> right = NULL;
		*peekNode = tmp;
		status = DLS_SUCCESS;
	    } else {
		status = status | DLN_INVALID;
	    }
	} else {
    	    if(peekNode != NULL){
		status = DLS_EMPTY | DLS_SUCCESS;
	    } else {
		status = status | DLN_INVALID;
	    }		    
	}		
    } else {
	status = status | DLS_NULL;
    }
    return (status);
}
