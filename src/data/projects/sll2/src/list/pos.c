#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// getpos() - a list library utility function to identify the actual
//			position of a given node in an indicated list.
//
//	  note: Indexing of the list starts from 0
//
//  behavior: on error (NULL/UNDEFINED list or given node), return
//			negative value (-1), on out-of-bounds condition,
//			return -2
//
//			you are to have only ONE return statement for this
//			entire function. Change the existing one as needed.
//
int getpos(List *myList, Node *given)
{	
	//We create a temporary node so we can skim through the list, and set
	//the count to 0 representing the first position in the list
	Node *tmp = NULL;
	int count = 0;
	//If the given node/value is not null, we set tmp to the lead node and
	//then iterate through the list until we find the node we want.  else
	//we return -1 on a NULL or UNDEFINED LIST
	if (given != NULL){
		tmp = myList -> lead;
		while (tmp != given){
			tmp = tmp -> right;
			count++;
			if (tmp == NULL){
				count = -2;
				tmp = given;
			}
		}
	} else if(given == NULL || given == UNDEFINED){
		count = -1;
	}
	return(count);
}

//////////////////////////////////////////////////////////////////////
//
// setpos() - a list library utility function to set a node pointer
//			to the node at the indicated position of a list.
//
//	  note: Indexing of the list starts from 0
//
//  behavior: on error (NULL/UNDEFINED list or negative/out-of-bounds
//			pos), return NULL.
//
//			you are to have only ONE return statement for this
//			entire function. Change the existing one as needed.
//
Node *setpos(List *myList, int pos)

{
	//We set up tmp2 as an empty Node so we can skim through the list and
	//stop on the node we want to return, and we set count equal to 0 to
	//represent the lead node.
	Node *tmp2 = NULL;
	int count = 0;
	//If the list is not NULL and the position is a positive number/0, we
	//iterate through the list until we find the Node we want to return.
	//else, we return tmp instead of a Node.
	if (myList != NULL && pos >= 0){
		tmp2 = myList -> lead;
		while(count < pos && tmp2 != NULL){
			tmp2 = tmp2 -> right;
			count++;
		}
	} else {
		tmp2 = NULL;
	}
	return(tmp2);
}
