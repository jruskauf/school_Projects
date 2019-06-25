#include "stack.h"

//////////////////////////////////////////////////////////////////////
//
//      pop() - grab node off top of stack (stack is modified)
//              
//              be sure to utilize existing list and stack library
//              functions to facilitate your implementation. Do NOT
//              reinvent the wheel.
//
//              the top of the stack should track the last node in
//              its underlying list.
//
// status code: this function can generate the following status codes
//                  DLN_INVALID:       newNode doesn't exist
//                  DLN_NULL:          *newNode is NULL (after pop)
//                  DLN_ALREADY_ALLOC: *newNode exists and not NULL
//                  DLS_SUCCESS:       normal operation
//                  DLS_UNDERFLOW:     pop() from an empty stack
//                  DLS_EMPTY:         stack is EMPTY
//                  DLS_NULL:          stack is NULL
//                  DLS_INVALID:       stack does not exist
//                  DLS_ERROR:         error occurred (stack is NULL,
//                                     non-existent, underflow, etc.)
//
//        note: as with the other functions, you may use no more
//              than one return() statement per function.
//
code_t pop(Stack **myStack, Node **newNode)
{
    code_t status = DLS_ERROR;
   
    if(myStack != NULL){
	if((*myStack) != NULL){
  	    if(newNode != NULL){
	    	if((*myStack) -> top != NULL){

		    *newNode = (*myStack) -> top;
		    if((*newNode) -> left != NULL){
		        (*myStack) -> data -> last = (*newNode) -> left;
			(*myStack) -> data -> last -> right = NULL;
			(*myStack) -> top = (*myStack) -> data -> last;
		        (*newNode) -> left = NULL;
		        (*newNode) -> right = NULL;
		    } else {

			(*myStack) -> data -> lead = NULL;
			(*myStack) -> data -> last = NULL;
			(*myStack) -> top = (*myStack) -> data -> last;
		        (*newNode) -> left = NULL;
		        (*newNode) -> right = NULL;
		    }
		    (*myStack) -> size--;
		    if((*myStack) -> top != NULL){
		        status = DLS_SUCCESS;
	            } else {
			status = DLS_EMPTY | DLS_SUCCESS;
		    }
		} else {
	            status = status | DLS_UNDERFLOW | DLS_EMPTY | DLN_NULL;
		}
	    } else {
	    	status = status | DLN_INVALID;
	    }		    
	} else {
	    status = status | DLS_NULL;
	}
    } else {
	status = DLS_INVALID | status;
    }
    return (status);
}
