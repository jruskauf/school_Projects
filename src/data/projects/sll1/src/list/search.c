#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// searchlist() - a list library utility function to locate a node in
//                an existing list by value it contains.
//
//      note: unlike getpos()/setpos(), which worked in units of list
//            positional offsets, searchlist() focuses on the actual
//            content of what is in the nodes, returning a pointer to
//            the initial node that contains the matching value (from 
//            the start of the list).
//
//  behavior: on error (NULL/UNDEFINED list, NULL node, no match),
//            return NULL
//
//            you are to have only ONE return statement for this
//            entire function. Change the existing one as needed.
//
Node *searchlist(List *myList, char value)
{
	//setting up a positional node, will return null if list is NULL,
	//UNDEFINED, or empty.
	Node *tmp = NULL;
	if ((myList != NULL && myList != UNDEFINED) && myList -> lead != NULL){
		//setting tmp equal to lead before iterating throught the list,
		//checking the value of each node against the value provided
		tmp = myList -> lead;
		while (tmp -> info != value && tmp -> right != NULL){
			tmp = tmp -> right;
		}
		//If the last value in the list is not equal to the value,
		//return NULL as we have not found the value that was given.
		if (tmp == myList -> last && tmp -> info != value){
			tmp = NULL;
		}
	}

	return(tmp);
}
