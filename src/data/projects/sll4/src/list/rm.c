#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// rmlist() - a list library function to deallocate an existing list;
//            care must be taken to ensure any component nodes have
//            been properly disposed of so as to prevent a memory
//            leak. The resulting list will be in a NULL state.
//
//      note: you are to have only ONE return statement for this
//            entire function. Change the existing one as needed.
//
List *rmlist(List *myList)
{
	//if the list is in a desirable state, we free the list and set it to
	//null.  Otherwise we clear out the list and then deallocate it.
	if(myList != NULL && myList != UNDEFINED && myList -> lead == NULL){
		free(myList);
		myList = NULL;
	} else if (myList != NULL && myList != UNDEFINED){
		myList = clearlist(myList);
		free(myList);
		myList = NULL;
	}
	return(myList);
}
