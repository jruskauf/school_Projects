#include "list.h"

//////////////////////////////////////////////////////////////////////
//
//   append() - add a new node to the given list after the node
//              at the indicated place. append() needs to manage
//              the necessary connections (pointers) to maintain list
//              integrity, along with ensuring the initial and closing
//              pointers of the list remain relevant and up-to-date.
//
//    behavior: on an UNDEFINED list- do nothing; return list as is
//              on a NULL list- allocate a list and proceed
//              on a NULL or UNDEFINED newNode- return list as is
//
//              as with the other functions, you may use no more
//              than one return() statement per function.
//
List *append(List *myList, Node *place, Node *newNode)
{
	//Initializing variables and nodes.
	int check = 0;
	int count = 0;
	Node *tmp = NULL;
	Node *tmp2 = NULL;
	//Here we check if the list is NULL or undefined.  If NULL we initialize
	//a new list and continue.  If its undefined, we set our check value to 
	//1 so we skip trying to insert a value and return the list as is.
	if (myList == NULL){

		myList = mklist();

	} else if (myList == UNDEFINED){

		check = 1;

	}

	if (check == 0){
		//Here we check if the Node is either null or undefined.  If the
		//node is either, we skip inserting a value and return the list 
		//as is.  Otherwise, we set tmp equal to newNode, and if the 
		//lead of the list is not null, we set the count.
		if (newNode == NULL || newNode == UNDEFINED){

			check = 1;
		
		} else {

			tmp = newNode;

			if (myList -> lead != NULL){

				count = getpos(myList, place);

			}

		}
		
		//This handles inserting into an empty list, as we only need to
		//have list lead and last point to the new node.
		if (check == 0 && myList -> lead == NULL){

			myList -> lead = tmp;
			myList -> last = tmp;
		
		//Since we append after a value, we only need to check if the
		//check has not been changed, indicating a populated list.
		} else if (check == 0){
			
			//We add a node to the right of the last node in the
			//list.  Then we set tmp to the node we want to append
			//after, and tmp2 to the last node in the list.
			myList -> last -> right = mknode(9);
			myList -> last = myList -> last -> right;
			tmp = setpos(myList, count);
			count = getpos(myList, myList -> last);
			tmp2 = setpos(myList, count);

			//Iterate backwards through the list until we reach the
			//node we want to append after.  Then we set the node to
			//the right equal to the info of the new node.
			while (tmp2 != tmp){

				if (tmp2 -> right != NULL){
					tmp2 -> right -> info = tmp2 -> info;
				}

				count--;
				tmp2 = setpos(myList, count);
			}

			tmp2 -> right -> info = newNode -> info;

		}

	}
	//returning the new list
	return(myList);
}
