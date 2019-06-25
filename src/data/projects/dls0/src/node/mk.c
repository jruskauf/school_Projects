#include "node.h"

//////////////////////////////////////////////////////////////////////
//
//    mknode() - a node library function to allocate and initialize
//               a new node (to provided value).
//
// status codes:
//               DLN_SUCCESS:       no problems encountered
//               DLN_MALLOC_FAIL:   error on creation
//               DLN_ALREADY_ALLOC: already exists
//               DLN_NULL:          node is in NULL state
//               DLN_ERROR:         some error occurred
//               DLN_INVALID:       invalid use (NULL pointer)
//
//   suggestion: be sure to error check any allocation or query of
//               external resources; limit initialization steps to
//               only be performed in the allocation was successful.
//
//         NOTE: you are to have only ONE return statement for this
//               entire function. Change the existing one as needed.
//
//               if node is not in valid state, node should be set
//               to NULL.
//
code_t mknode(Node **newNode, char info)
{
    //Setting errcheck to DLN_ERROR, so if it falls through the checks we
    //know something went horribly wrong, as it will simply be a generic ERROR 
    code_t errcheck = DLN_ERROR;
    //We are checking here to see whether the node is in a null or undefined
    //state, and then if it has already been allocated.  If these are not true,
    //then we continue on.
    if (newNode == NULL || newNode == UNDEFINED){
	    errcheck = DLN_INVALID | DLN_ERROR;
    } else if (*newNode != NULL){
	    errcheck = errcheck | DLN_ALREADY_ALLOC;
    } else {
	    //derefrencing the node and then mallocing the memory we want for it
	    Node *nowNode = NULL;
	    nowNode = *newNode;
	    nowNode = malloc(sizeof(Node));
	    //Checking to see if the malloc worked.  If it didn't, we return
	    //an error message.  Otherwise we set the value of the node to the
	    //char variable we were given, and set the left and right pointers
	    //accordingly.
	    if (nowNode == NULL || nowNode == UNDEFINED){
		    errcheck = errcheck | DLN_MALLOC_FAIL | DLN_NULL;
	    } else {
	    	nowNode -> VALUE = info;
	    	nowNode -> left = NULL;
	    	nowNode -> right = NULL;
	    	*newNode = nowNode;
	    	errcheck = DLN_SUCCESS;
	    }
    }
    //returning our built status
    return(errcheck);
}
