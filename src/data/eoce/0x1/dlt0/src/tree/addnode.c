#include "tree.h"

//////////////////////////////////////////////////////////////////////
//
// addnode()   - place newNode into indicated tree at proper position.
//
//  status code: this function can generate the following status codes
//                  DLT_SUCCESS:  normal operation (success!)
//                  DLT_NULL:     tree is NULL
//                  DLT_MAX:      tried to add onto a full bounded
//                                tree (considered an error)
//                  DLT_ERROR:    error encountered
//                  DLT_INVALID:  tree pointer doesn't exist
//
//         note: a max_height of 0 indicates an unbounded tree
//              
//  assumptions: duplicate values are allowed;
//               nodes with values less than or equal to that of
//               an analyzed node are placed to the left,
//               where greater than are placed to the right.
//
//         note: you are to have only ONE return statement for this
//               entire function. Change the existing one as needed.
//
code_t addnode(Tree **myTree, Node *newNode)
{
	code_t status = DLT_ERROR;

	if(myTree != NULL){
	    if((*myTree) != NULL){
		Node *tmp = NULL;
		tmp = (*myTree) -> root;
		int check = 0;
		int count = 0;
		int buffer = (*myTree) -> max_height;
		//Node *mtmp = NULL;
		
		if((*myTree) -> root == NULL){
		    (*myTree) -> root = newNode;
		    (*myTree) -> root -> left = NULL;
		    (*myTree) -> root -> right = NULL;
		    check = 1;

		} 
		count = 1;
		while(check != 1 && (count <= buffer || buffer == 0)){ 
		    if(tmp -> VALUE >= newNode -> VALUE){
			if(tmp -> left != NULL){
			    tmp = tmp -> left;
			    count++;
			} else {
			    tmp -> left = newNode;
			    newNode -> right = NULL;
			    newNode -> left = NULL;
			    check = 1;
			}
		    } else {
			if(tmp -> right != NULL){
			    tmp = tmp -> right;
			    count++;
			} else {
			    tmp -> right = newNode;
			    newNode -> right = NULL;
			    newNode -> left = NULL;
			    check = 1;
			}
		    }
		}
   		if(buffer != 0 && count > buffer){
		    status = status | DLT_MAX;
		} else {
		    status = DLT_SUCCESS;
		}
	     } else {
		status = status | DLT_NULL;
	    }
	} else {
	    status = status | DLT_INVALID;
	}
	return (status);
}
