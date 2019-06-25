#include "group.h"

//////////////////////////////////////////////////////////////////////
//
// rmgroup() - a group library function to deallocate an existing
//             list group; care must be taken to ensure any component
//             lists have been properly disposed of so as to prevent
//             a memory leak. The resulting group will be in a NULL
//             state following successful processing.
//
//       note: as with the other functions, you may use no more
//             than one return() statement per function.
//
Group *rmgroup(Group *oldGroup)
{
	//this is the same logic as remove node, but in this case we use groups
	//and lists instead of lists and nodes.
	if(oldGroup != NULL && oldGroup != UNDEFINED &&oldGroup->initial==NULL){
		free(oldGroup -> initial);
		oldGroup = NULL;
	} else if (oldGroup != NULL && oldGroup != UNDEFINED){
		List *tmp = NULL;
		tmp = oldGroup -> initial;
		while (tmp != NULL){
			oldGroup = lobtain(oldGroup, &tmp);
			tmp = rmlist(tmp);
			tmp = oldGroup -> initial;
		}
		free(oldGroup);
		oldGroup = NULL;
	}
	return(oldGroup);
}
