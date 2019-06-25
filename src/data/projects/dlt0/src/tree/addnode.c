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
	//Initializing status code so if it falls through, we get an error
	//message
	code_t status = DLT_ERROR;

	//If the tree is either nonexistant/null, fall through and give an error
	//message.  Otherwise, continue with operations.
	if(myTree != NULL){
	    if((*myTree) != NULL){
		//setting a temporary "travelling" node to the root of the tree.
		//The tree does not need to be populated for this to work.
		Node *tmp = NULL;
		tmp = (*myTree) -> root;
		int check = 0;
		int count = 0;
		int buffer = (*myTree) -> max_height;
		
		//If the tree is empty, set the root equal to the node we want 
		//to add, and skip the unecessary processes.
		if((*myTree) -> root == NULL){
		    (*myTree) -> root = newNode;
		    (*myTree) -> root -> left = NULL;
		    (*myTree) -> root -> right = NULL;
		    check = 1;

		}

		//If the buffer has not been reached or it is zero and check has
		//not been tripped, the loop handling traversal and appending of
		//the node at the end of a "branch" as the value falls through 
		//the tree.	
		count = 1;
		while(check != 1 && (count <= buffer || buffer == 0)){ 
		    //If the value of the node being added is greater or equal
		    //to the current node, check to see if there is a node to
		    //the left.  If there is a node to the left, traverse left,
		    //otherwise place the new node there.
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
		    //If the value of the node being added is less than the
		    //current node we're tracking, then check if there is a
		    //node to the right of the tracked node.  If there is,
		    //traverse to the right.  Otherwise, add the node to the
		    //right of the current node.
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

		//If the buffer size has been set and reached, report an error,
		//otherwise we report a succesful process
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
