#include "group.h"

//////////////////////////////////////////////////////////////////////
//
//  lobtain() - take and isolate indicated list out of group of lists,
//              through a careful adjustment of necessary pointers.
//              lobtain() needs to maintain group of lists integrity.
//              
//    behavior: on a NULL Group- do nothing; return NULL.
//              on UNDEFINED Group- return UNDEFINED.
//              on a NULL/UNDEFINED thatList- return as is
//
//        note: you are expected to make use of the lgetpos() and
//              lsetpos() functions to aid you in accomplishing this
//              task. Don't needlessly reinvent the wheel.
//
//              it is important to acknowledge that thatList, the one
//              being isolated from the group, is being passed in as a
//              double pointer (we're passing the List pointer by
//              reference). As such, you need to be mindful that you
//              need to dereference it once on each usage when in this
//              function to use it as you expect.
//
//              as with the other functions, you may use no more
//              than one return() statement per function.
//
Group *lobtain(Group *myListGroup, List **thatList)
{
    //functionality and logic identical to the obtain node function.  Only
    //difference is that we are using groups and lists instead of lists and
    //nodes.
    int check = 0;
    int countto = 0;
    int count = 0;
    List *tmp = NULL;
    List *tmp2 = NULL;
    List *iso = NULL;
    Group *newGroup = NULL;

    iso = *thatList;

    newGroup = myListGroup;

    if (newGroup == NULL){
	check = 1;
    } else if (newGroup == UNDEFINED){
	check = 1;
    } else if(iso == NULL || iso == UNDEFINED){
	check = 1;
    } else {
	countto = lgetpos(newGroup, iso);
    }

    if (check == 0){
	if (countto == 0 && newGroup -> initial -> next == NULL){
	    newGroup -> initial = NULL;
	    newGroup -> closing = NULL;
	} else if (countto == 0){
	    tmp = newGroup -> initial;
	    newGroup -> initial = newGroup -> initial -> next;
	    tmp -> next = NULL;
	} else { 
	    while (count <= countto && tmp2 != iso){
		 tmp = lsetpos(newGroup, count);
		 tmp2 = lsetpos(newGroup, count+1);
		 count++;
	    }
	    tmp -> next = tmp2 -> next;
	    if (tmp2 == newGroup -> closing){
		 tmp -> next = NULL;
		 newGroup -> closing = tmp;
	    }
	}
    }
    return(newGroup);

}
