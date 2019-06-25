#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// clearlist() - a list library function to clear an existing list of
//               any and all of its component nodes (deallocate them).
//               The list itself continues to exist, but is in an
//               empty state following the successful call to
//               clearlist().
//
//     behavior: on error, return NULL.
//
//         note: you are to have only ONE return statement for this
//               entire function. Change the existing one as needed.
//
List *clearlist(List *myList)
{	
	//setting up variables to be used, and setting the list to return.
	List *emptyList = NULL;
	Node *tmp = NULL;
	emptyList = myList;

	//If the list is not in an undesirable state, we set tmp to the lead and
	//iterate through the list, seperating the node before we deallocate it.
	//If the list is in an undesirable state, we return NULL
	if (emptyList != NULL && emptyList != UNDEFINED){
		tmp = emptyList -> lead;
		while (tmp != NULL){
			emptyList = obtain(emptyList, &tmp);
			tmp = rmnode(tmp);
			tmp = emptyList -> lead;
		}
	} else {
		emptyList = NULL;
	}
	
	return(emptyList);
}
