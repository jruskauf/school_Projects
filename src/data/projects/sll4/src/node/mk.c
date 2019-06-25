#include "node.h"

//////////////////////////////////////////////////////////////////////
//
// mknode() - a node library function to allocate and initialize a 
//			new node.
//
//  behavior: on error, return NULL.
//
//	  NOTE: you are to have only ONE return statement for this
//			entire function. Change the existing one as needed.
//
Node *mknode(char value)
{
	//sets up a new node pointing at NULL
	Node *box = NULL;
	//mallocs out the memory needed to store the value's datatype
	box = malloc(sizeof(value));
	//sets the value of box to the input
	box -> info = value;
	//sets the right of the node to point at NULL
	box -> right = NULL;	
	//returns the node to be assigned to a variable
	return(box);
}
