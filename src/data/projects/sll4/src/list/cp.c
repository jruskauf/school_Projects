#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// cplist() - a list library function to duplicate or copy an existing
//            list and all its component nodes.
//
//            the operative idea here is "separate copies"; you may
//            want to make use of cpnode() to assist.
//
//  behavior: on error, return NULL.
//
//      note: you are to have only ONE return statement for this
//            entire function. Change the existing one as needed.
//
List *cplist(List *oldList)
{
	//setting up a new list to copy to, and then nodes to iterate through
	//each list.
	List *newList = NULL;
	Node *tmp1 = NULL;
	Node *tmp2 = NULL;
	//If the list we want to copy from is NULL or UNDEFINED, we return null
	//and skip the process of copying.
	if (oldList != NULL && oldList != UNDEFINED){	
		//if the list is not empty, we initialize the new list and
		//copy the lead node of the list we want to copy from, and then
		//set tmp1 to the second node in the list to copy from,and tmp2
		//to the lea dnode in the list to copy to.
		if (oldList -> lead != NULL){
			newList = mklist();
			tmp1 = oldList -> lead;
			newList -> lead = cpnode(tmp1);
			tmp1 = tmp1 -> right;
			tmp2 = newList -> lead;
			newList -> qty++;
			//iterate tmp1 through the list to copy from, copying
			//the node from tmp to the right of tmp2 until tmp1 
			//reaches NULL
			while (tmp1 != NULL){
				tmp2 -> right = cpnode(tmp1);
				tmp2 = tmp2 -> right;
				tmp1 = tmp1 -> right;
				newList -> qty++;
			}
		} else {
			//if the list to copy from is empty, initialize an
			//empty list
			newList = mklist();	
			newList -> lead = NULL;
			newList -> qty++;
		}
	newList -> next = oldList -> next;
	}	
	return(newList);
}
