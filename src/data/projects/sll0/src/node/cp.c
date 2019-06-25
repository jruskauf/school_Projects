#include "node.h"

//////////////////////////////////////////////////////////////////////
//
// cpnode() - a node library function to duplicate a node and its 
//			contents -- it must call other functions as needed, and
//			take care to ensure all aspects of the source node have
//			been successfully replicated in the copied node.
//
//  behavior: on error or NULL source node, return NULL.
//
//	  NOTE: you are to have only ONE return statement for this
//			entire function. Change the existing one as needed.
//
//			the contents of the "right" pointer, if non-NULL,
//			should be pointing to any next node (even though we
//			are not copying it here).
//
Node *cpnode(Node *curNode)
{
	//Setting up a new node
	Node *box = NULL;
	//malloc the memory size of the input's datatype
	box = (Node*)malloc(sizeof(curNode));
	//This handles the setting of the new node to the value of the input,
	//or if input is not populated by a value set to null.
	if (curNode != NULL){
		*box = *curNode;
		box -> right = curNode -> right;
	} else {
		box = NULL;
	}
	//return the new node to be assigned to a variable
	return(box);
}
