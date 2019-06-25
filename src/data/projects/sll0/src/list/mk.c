#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// mklist() - a list library function to allocate and initialize a 
//			new list.
//
//  behavior: on error, return NULL.
//
//	  note: you are to have only ONE return statement for this
//			entire function. Change the existing one as needed.
//


List *mklist(void)
{
	
	//Setting up the container of empty memory so we have space to put
	//our nodes in. 
	List* link = malloc(sizeof(List));

	//Checking to see if link has been properly malloc'd, if not, then
	//link is set to NULL.
	if (!link){
		link = NULL;
	}

	//returning the container to be assigned to a variable
	return(link);
}
