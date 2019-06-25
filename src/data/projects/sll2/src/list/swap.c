#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// swapnode() - swap the position of two given nodes in a list, being
//              sure to appropriately adjust any and all pertinent
//              pointers to ensure list integrity following the
//              operation (including potential changes to the list's
//              own initial and closing pointers, along with
//              connectivity between the nodes from the start to end
//              of the list).
//
//        note: you are NOT to just adjust node info values. You must
//              disconnect the identified nodes from the list and 
//              reconnect them- the node is our unit of transaction,
//              NOT the data it contains.
//
//    behavior: on a NULL list- do nothing: return NULL
//              on UNDEFINED list- return list as is
//              on an EMPTY list- do nothing: return list unchanged
//              on a NULL/invalid nodes to swap- do nothing: return
//                  the list unchanged
//
//        note: where applicable, make use of the getpos() and
//              setpos() functions to aid you in accomplishing this
//              task. Don't needlessly reinvent the wheel.
//
//              as with the other functions, you may use no more
//              than one return() statement per function.
//
List *swapnode(List *myList, Node *item1, Node *item2)
{

	//Setting up variables
	List *newList = NULL;
	Node *tmp     = NULL;
	Node *tmp2    = NULL;
	int check     =    0;

	//setting up the list we want to return
	newList = myList;

	//setting up nodes to append after the ones we wish to obtain
	tmp  = cpnode(item1);
	tmp2 = cpnode(item2);

	//checking to see if we have any undesirable starting conditions.  If
	//there is an undesirable condition, we skip the processes and return
	//the list as it is.
	if (newList == NULL){
		newList = NULL;
		check = 1;
	} else if (newList == UNDEFINED || newList -> lead == NULL){
		check = 1;
	} else if (tmp == NULL || tmp2 == NULL){
		check = 1;
	} else if (tmp == UNDEFINED || tmp2 == UNDEFINED){
		check = 1;
	}

	//This handles appending the value we want to swap after the earliest
	//node, and then isolating that from the list.  If the node we are
	//trying to swap is in the middle of the list, we don't swap it as
	//it is trying to swap with itself.
	if (check == 0 && getpos(myList, item1) > getpos(myList, item2)){
		newList = append(newList, item1, tmp2);
		newList = obtain(newList, &item1);
		newList = append(newList, item2, tmp);
		newList = obtain(newList, &item2);
	}else if (check == 0 && getpos(myList, item1) != getpos(myList, item2)){
		newList = append(newList, item2, tmp);
		newList = obtain(newList, &item2);
		newList = append(newList, item1, tmp2);
		newList = obtain(newList, &item1);
	}  
	//returning the modified/unmodified list
	return(newList);
}
