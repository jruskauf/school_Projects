#include "group.h"

//////////////////////////////////////////////////////////////////////
//
//  lappend() - add a new list to the given list group after the list
//              at the indicated place. lappend() needs to manage
//              the necessary connections (pointers) to maintain list
//              group integrity, along with ensuring initial and
//              closing indicators of the list group remain relevant
//              and up-to-date.
//
//    behavior: on a NULL/UNDEFINED group- return NULL
//              on a NULL/UNDEFINED newList- return group as is
//
//              as with the other functions, you may use no more
//              than one return() statement per function.
//
Group *lappend(Group *myListGroup, List *place, List *newList)
{

    //The functionality of this is exactly the same as node append.  The
    //only changes are to what it is moving, in this case we are moving
    //lists around in a group.  The only difference in terms of logic is
    //for inserting a list, as we cannot simply change the info in the list,
    //but rather take one out and insert a new one.
    int check = 0;
    int count = 0;
    List *tmp = NULL;
    List *tmp2 = NULL;

    if (myListGroup == NULL || myListGroup == UNDEFINED){
	myListGroup = NULL;
	check = 1;
    } else if (newList == NULL || newList == UNDEFINED){
	check = 1;
    }
    
    if (check == 0){

	tmp = newList;

	if (myListGroup -> initial != NULL){
	    count = lgetpos(myListGroup, place);
	}else if (myListGroup -> initial == NULL){
	    myListGroup -> initial = tmp;
	    myListGroup -> closing = tmp;
	    check = 1;
	}
	
	if (check == 0 && count >= 0){
	   myListGroup -> closing -> next = mklist();
	   myListGroup -> closing = myListGroup -> closing -> next;
	   tmp = lsetpos(myListGroup, count);
	   count = lgetpos(myListGroup, myListGroup -> closing);
	   tmp2 = lsetpos(myListGroup, count);
	   List *tmp3 = NULL;
	   while (tmp2 != tmp){
		   //The change needed to happen here, as the list first needs
		   //to be isolated then removed.  Then, we insert the new list
		   //into the empty space and reconnect the lists as needed to
		   //preserve the integrity of the group
		   if (tmp2 -> next != NULL){
			   tmp3 = tmp2 -> next -> next;
			   tmp2 -> next = rmlist(tmp2 -> next);
			   tmp2 -> next = cplist(tmp2);
			   tmp2 -> next -> next = tmp3;
		   }
		   count--;
		   tmp2 = lsetpos(myListGroup, count);
	   }
	   tmp3 = tmp2 -> next -> next;
	   tmp2 -> next = rmlist(tmp2 -> next);
	   tmp2 -> next = cplist(newList);
	   tmp2 -> next -> next = tmp3;
  	
	}
    }
    return(myListGroup); 
}

