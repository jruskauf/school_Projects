#include "group.h"

//////////////////////////////////////////////////////////////////////
//
// lgetpos() - a group library utility function to identify the actual
//             position of a given list in an indicated list group.
//
//       note: Indexing of the group starts from 0
//
//   behavior: on error (NULL/UNDEFINED group/list), return negative
//             value (-1), on out-of-bounds condition, return -2
//
//             as with the other functions, you may use no more
//             than one return() statement per function.
//
sli lgetpos(Group *myListGroup, List *given)
{
    //Same functionality as getpos, but instead we now use lists and groups
    //instead of nodes and lists.
    List *ltmp = NULL;
    sli count = 0;

    if (myListGroup != NULL){
	ltmp = myListGroup -> initial;
	if (ltmp != NULL){
		while (ltmp != given){
	 	    ltmp = ltmp -> next;
		    count++;
		    if (ltmp == NULL){
			count = -2;
			ltmp = given;
	 	   }
		}
	} else if (ltmp == NULL && given != NULL){
		count = -2;
	} else {
		count = -1;
	}
    } else if (myListGroup == NULL || myListGroup == UNDEFINED){
	count = -1;
    }
    return(count);
}

//////////////////////////////////////////////////////////////////////
//
// lsetpos() - a group library utility function to set a list pointer
//             to the list at the indicated position of a group.
//
//       note: Indexing of the group starts from 0
//
//   behavior: on error (NULL/UNDEFINED group or
//             negative/out-of-bounds pos), return NULL.
//
//             as with the other functions, you may use no more
//             than one return() statement per function.
//
List *lsetpos(Group *myListGroup, sli pos)
{
    //Same functionality as setpos, but instead we now use lists and groups
    //instead of nodes and lists.
    List *ltmp2 = NULL;
    sli count = 0; 

    if (myListGroup != NULL && pos >= 0){
	    ltmp2 = myListGroup -> initial;
	    while(count < pos && ltmp2 != NULL){
		    ltmp2 = ltmp2 -> next;
		    count++;
	    }
    } else {
	    ltmp2 = NULL;
    }
    return(ltmp2);
}
