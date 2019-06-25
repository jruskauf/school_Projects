#include "list.h"

//////////////////////////////////////////////////////////////////////
//
//   obtain() - take and isolate indicated node out of list, through
//              a careful adjustment of necessary pointers. obtain()
//              needs to maintain list integrity.
//              
//    behavior: on a NULL list- do nothing; return NULL.
//              on an UNDEFINED list- do nothing, return list as is
//              on a NULL thatNode- do nothing; return list as is
//              on UNDEFINED thatNode- do nothing; return list as is
//
//        note: you are expected to make use of the getpos() and
//              setpos() functions to aid you in accomplishing this
//              task. Don't needlessly reinvent the wheel.
//
//              it is important to acknowledge that thatNode, the one
//              being isolated from the list, is being passed in as a
//              double pointer (we're passing the Node pointer by
//              reference). As such, you need to be mindful that you
//              need to dereference it once on each usage when in this
//              function to use it as you expect.
//
//              as with the other functions, you may use no more
//              than one return() statement per function.
//
List *obtain(List *myList, Node **thatNode)
{
	//
	// Quick illustration of a double pointer node and its equivalents
	//
	// **thatNode = *referenceNode = info
	//
	// *thatNode = referencedNode = &info
	//
	// thatNode = &referencedNode
	//
	///////////////////////////////////////////////////////////////////////
	
	//setting up variables to be used throughout the program
	int check     =    0;
	int countto   =    0;
	int count     =    0;
	Node *tmp     = NULL;
	Node *tmp2    = NULL;
	Node *iso     = NULL;
	List *newList = NULL;

	//This sets our dereferenced node
	iso = *thatNode;
	
	//setting up our new list to modify and return
	newList = myList;

	//Here we check if we have any undesirable starting conditions.  If we
	//do, we skip the processing and return the list as is.  Otherwise, we
	//set countto and continue on.
	if (newList == NULL){	
		check = 1;
	}else if (newList == UNDEFINED){
		check = 1;
	} else if (iso == NULL || iso == UNDEFINED){
		check = 1;
	} else {
		countto = getpos(newList, iso);
	}
	
	if (check == 0){

		//This handles if the list is empty, simply setting lead and last 
		//to NULL so iso is the only thing holding onto the node we wish
		//to remove
		if (countto == 0 && newList -> lead -> right == NULL){
			newList -> lead = NULL;
			newList -> last = NULL;

		//This handles removing the first node by having lead move one
		//node to the right, and then seperating tmp (which points to
		//iso) from the list.
		} else if (countto == 0){
			tmp = newList -> lead;
			newList -> lead = newList -> lead -> right;
			tmp -> right = NULL;
		//This handles seperating nodes past the first one.  We iterate
		//through the list, with tmp trailing tmp2, which is what will
		//let us isolate iso from the list.  once tmp2 reaches iso, we
		//set the right of tmp to the right of tmp2 if its not last.
		//This effectively jetisons the node from the list. 
		} else {
			while (count <= countto && tmp2 != iso){
				tmp  = setpos(newList, count);
				tmp2 = setpos(newList, count+1);
				count++;
			}
			tmp -> right = tmp2 -> right;
			if (tmp2 == newList -> last){
				tmp -> right = NULL;
				newList -> last = tmp;
			}
		}
	}		
	//returning the modified/unmodified list
	return(newList);
}
