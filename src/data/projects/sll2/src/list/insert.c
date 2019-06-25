#include "list.h"

//////////////////////////////////////////////////////////////////////
//
//   insert() - add a new node to the given list before the node
//			  at the indicated place. insert() needs to manage
//			  the necessary connections pointers) to maintain list
//			  integrity, along with ensuring the start and end
//			  indicators of the list remain relevant and up-to-date.
//
//	behavior: on an UNDEFINED list- do nothing; return list as is
//			  on a NULL list- allocate a list and proceed
//			  on a NULL or UNDEFINED newNode- return list as is
//
//		note: you are expected to make use of the getpos() and
//			  setpos() functions to aid you in accomplishing this
//			  task. Don't needlessly reinvent the wheel.
//
//			  as with the other functions, you may use no more
//			  than one return() statement per function.
//
List *insert(List *myList, Node *place, Node *newNode)
{
	//here we initialize our variables and Nodes
	int check  =    0;
	int count  =    0;
	Node *tmp  = NULL;
	Node *tmp2 = NULL;
	
	//Here we check if the list is NULL or undefined.  If NULL we initialize
	//a new list and continue.  If its undefined, we set our check value to
	//1 so we are able to skip the entire inserting a value code and return
	//the list as is.
	if (myList == NULL){

		myList = mklist();

	} else if (myList == UNDEFINED){

		check = 1;

	}

	if (check == 0){
		//If the node is equal to NULL or UNDEFINED, skip inserting the
		//value and return the list as is by setting check to 1.
		//Otherwise, set tmp equal to newnode, and if lead does not
		//equal NULL we get the position of the place node.  We don't
		//need to get the ndoe we want to insert before in an empty
		//list, as we'll be adding the first node into the list.
		if(newNode == NULL || newNode == UNDEFINED){

			check = 1;

		} else {

			tmp = newNode;

			if (myList -> lead != NULL){

				count = getpos(myList, place);

			}
		}

		//This is for a new, empty list, where we just insert the first
		//node into the list.  No need for positional values here.
		if (check == 0 && myList -> lead == NULL){

			myList -> lead = tmp;
			myList -> last = tmp;

		//This is for inserting before the first element in the array.
		//This just skips a lot of unneeded steps since we can just
		//put the node before the current lead and then point lead
		//to the new node.
		} else if (check == 0 && count == 0){

			tmp -> right = myList -> lead;
			myList -> lead = tmp;
		
		//If we want to insert before any other position other than
		//the first node, and the list is not empty, we have to do
		//some extra steps.
		} else if (check == 0 && count > 0){
			
			//Here we add a node to the right of last. This is just
			//a transition node for the moment.  We then set last
			//to the new node and set tmp to the node we want to 
			//insert before.  then we set tmp2 to the last node in
			//the list (had to get creative to get around a seg 
			//fault) 
			myList -> last -> right = mknode(9);
			myList -> last = myList -> last -> right;
			tmp = setpos(myList, count);
			count = getpos(myList, myList -> last);
			tmp2 = setpos(myList, count);
			
			//While we havent reached tmp, we iterate backwards 
			//through the list, copying values from current node
			//to the node to the right.  This preserves the values
			//of the list, so we don't overwrite anything with our
			//new value.	
			while (tmp2 != tmp){
				
				if (tmp2 -> right != NULL){
					tmp2 -> right -> info = tmp2 -> info;
				}

				count--;
				tmp2 = setpos(myList, count);	

			}
			
			//After we get to tmp, we coping the current value
			//to the node to the right before overwriting the node
			//with newNode's value.
			tmp2 -> right -> info = tmp -> info;
			tmp2 -> info = newNode -> info;

		}

	}
	//returning the new list
	return(myList);

}
