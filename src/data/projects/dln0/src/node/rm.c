#include "node.h"

//////////////////////////////////////////////////////////////////////
//
//    rmnode() - a node library function to clear and deallocate an 
//               existing node
//
// status codes:
//               DLN_SUCCESS: no problems encountered
//               DLN_NULL:    node in NULL state
//               DLN_ERROR:   some error occurred
//               DLN_INVALID: invalid use (NULL pointer)
//
//   suggestion: avoid deallocating an already NULL or non-existant
//               node; do proper error checking!
//
//         NOTE: you are to have only ONE return statement for this
//               entire function. Change the existing one as needed.
//
//               be sure to explicitly set the node to NULL after
//               performing all necessary steps (but don't JUST
//               set it NULL- clear and deallocate first).
//
code_t rmnode(Node **curNode)
{
	code_t errcheck;
	//Checking to see if the node is in a NULL or undefined state, and if
	//it isn't we proceed to isolate and then deallocate the node we want.
	//
        if (curNode == NULL || curNode == UNDEFINED){
		errcheck = DLN_INVALID | DLN_ERROR;
	} else if ((*curNode) == NULL){
		errcheck = DLN_ERROR | DLN_NULL;
	} else {
		(*curNode) -> left = (*curNode) -> right;
		free((*curNode));
		(*curNode) = NULL;
		//If for some reason freeing the node and then setting it to 
		//NULL failed, we return a generic error message.
		if ((*curNode) != NULL){
			errcheck = DLN_ERROR;
		} else {
			errcheck = DLN_NULL | DLN_SUCCESS;
		}
	}
        return(errcheck);
}
