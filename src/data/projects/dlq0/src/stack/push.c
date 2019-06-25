#include "stack.h"

//////////////////////////////////////////////////////////////////////
//
//     push() - place newNode onto top of given stack
//
//              be sure to utilize existing list and stack library
//              functions to facilitate your implementation. Do NOT
//              reinvent the wheel.
//
//              the top of the stack should track the last node in
//              its underlying list.
//
// status code: this function can generate the following status codes
//                  DLN_NULL:     newNode is NULL (an error)
//                  DLS_SUCCESS:  normal operation (push successful)
//                  DLS_NULL:     stack is NULL
//                  DLS_OVERFLOW: tried to push onto a full bounded
//                                stack (considered an error)
//                  DLS_ERROR:    error encountered
//                  DLS_INVALID:  stack does not exist
//
//        note: as with the other functions, you may use no more
//              than one return() statement per function.
//
code_t push(Stack **myStack, Node *newNode)
{
    code_t status = DLS_ERROR;
   
    if(myStack != NULL){
	if((*myStack) != NULL){
  	    if(newNode != NULL){
	        if(newNode -> DATA != NULL){
	    	    if((*myStack) -> size >= (*myStack) -> data -> qty 
		    || (*myStack) -> size == 0){
			List *data = (*myStack) -> data;
	                append(&data, data -> last, newNode);
			(*myStack) -> data = data;
			(*myStack) -> top = (*myStack) -> data -> last;
		        (*myStack) -> data -> qty++;
			display(data, 0);
		        status = DLS_SUCCESS;
		    } else {
	                status = status | DLS_OVERFLOW;
		    }
	        } else {
		    status = status | DLN_NULL;
	        }
	    } else {
	    	status = status | DLN_NULL;
	    }		    
	} else {
	    status = status | DLS_NULL;
	}
    } else {
	status = DLS_INVALID | status;
    }
    return (status);
}
