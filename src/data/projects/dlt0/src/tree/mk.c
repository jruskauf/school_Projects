#include "tree.h"

//////////////////////////////////////////////////////////////////////
//
//  mktree() - allocate, initialize, and return a pointer to the newly
//             created tree.
//
//       note: the second parameter is to be the created tree's
//             maximum height (bound).
//
//     height: a height of 0 indicates an unbounded tree
//             > 0 will limit the total number of levels in the tree
//
//status code: this function can generate the following status codes:
//                 DLT_SUCCESS:     no problems encountered
//                 DLT_EMPTY:       result of normal operation
//                 DLT_CREATE_FAIL: error on creation (malloc-
//                                  related or already exists)
//                 DLT_NULL:        tree remains in NULL state
//                 DLT_ERROR:       an error has taken place
//
//             you are to have only ONE return statement for this
//             entire function. Change the existing one as needed.
//
code_t mktree(Tree **newTree, uc height)
{
	//initializing the status code so that if it falls through, we get an
	//error message
	code_t status = DLT_ERROR;
	//If the tree is neither populated or empty, malloc out the memory to
	//the address given, setting the root to null and setting a height if
	//any.  Otherwise, it will fall through and then be checked, reporting
	//on whether it was NULL or empty
	if(newTree != NULL && (*newTree) == NULL){
	    (*newTree) = (Tree*)malloc(sizeof(Tree*));
	    (*newTree) -> root = NULL;
	    status = DLT_EMPTY | DLT_SUCCESS;
	    if(height > 0)
		(*newTree) -> max_height = height;
	} else {
	    if(newTree == NULL){
		    status = status | DLT_NULL;
	    } else {
		status = DLT_ERROR | DLT_CREATE_FAIL;
	    }
	}
	return (status);
}
