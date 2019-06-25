#include "list.h"

//////////////////////////////////////////////////////////////////////
//
//    find() - a list library utility function to locate a node in
//             an existing list by value it contains.
//
//       note: find() focuses on the actual content of what is in the
//             nodes, setting a (double) pointer to the first node
//             that contains the matching value (from the start of the
//             list, if foundNode is initially NULL, or from the point
//             in the list that foundNode points).
//
//status code: this function can generate the following status codes
//               DLN_SUCCESS:  match found
//               DLN_NULL:     match not found (node is NULL)
//               DLN_ERROR:    error encountered
//               DLN_INVALID:  node doesn't exist (UNDEFINED)
//               DLL_NULL:     list is NULL
//               DLL_EMPTY:    list is EMPTY
//               DLL_ERROR:    error encountered
//               DLL_INVALID:  list doesn't exist (UNDEFINED)
//
//   behavior: on error (NULL/UNDEFINED list/node), foundNode, if
//             it exists, is NULL.
//
//             as with the other functions, you may use no more
//             than one return() statement per function.
//
//             do not count; navigate by comparison
//
code_t find(List *myList, char searchval, Node **foundNode)
{
    code_t status = DLL_ERROR;
    int check = 1;
    //checking if the list is null or empty, and if either, spit out an error.
    if (myList != NULL){
	if (myList -> lead != NULL){
	    status = DLN_ERROR;
	    //If the foundNode is null, spit out an error.
	    if(foundNode != NULL){
	 	    Node *tmp = NULL;
		    //if the foundNode is null, set tmp to the lead, otherwise
		    //set tmp to the right of the foundNode.
		    if (*foundNode == NULL){
			 tmp = myList -> lead;
		    } else {
			 tmp = (*foundNode) -> right;
		    }
		    //iterate through the list, checking to see if the value
		    //is hit once.  When it hits once, place a marker on it and
		    //exit the loop.
		    while (tmp != NULL && check == 1){
		        if (tmp -> VALUE == searchval){
		  	    status = DLN_SUCCESS;
			    *foundNode = tmp;
			    check = 0;
		        } else if(check == 1){
			    status = DLN_NULL;    
			    *foundNode = NULL;
		        }
			tmp = tmp -> right;
		    }
	    } else {
		status = DLN_INVALID;
	    }
	} else {
	    status = status | DLL_EMPTY;
	}
    } else {
	status = status | DLL_NULL;
    }
    return(status);
}
