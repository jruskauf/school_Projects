#include <stdio.h>
#include "node.h"

void display(Node *);

int main()
{
	Node *nod1, *nod2;
	char data[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7 };
	int i;
	int size;
	int count;

	fprintf(stdout, "Array: ");
	for(i = 0; i < 14; i++)
		fprintf(stdout, "%hhd ", *(data+i));
	fprintf(stdout, "\n");

	// Create a linked list of nodes, using the node library 
	// functions where applicable (mknode() specifically), and
	// have each node contain one of the above array elements,
	// to have a linked list equivalent of the array.
	
	//Get the number of elements in the array by dividing its size by the
	//size of the datatype of the first element	
	size = sizeof(data)/sizeof(data[0]);
	//setting up nodes to use, nod1 is the "start" of the list, and allows
	//us access to it.
	nod1 = nod2 = mknode(0);
	//initializing count to 0 to use in the while loop
	count = 0;
	//printing out the beginning of the display
	fprintf(stdout, "List:  ");

	//while the count is less than the size, we build the list from the
	//given array element by element, assigning each value to a newly
	//created node
	while( count < size){

		nod2 -> info = data[count];
		nod2 -> right = mknode(0);

		if (count == size-1){

			rmnode(nod2 -> right);
			nod2 -> right = NULL;	
		} else { 
			nod2 = nod2 -> right;
		}
		count++;
	}	

	// Display the list from beginning to end- the above order
	// of values should be seen.
	
	//calling the display function with nod1 as the start of the list
	display(nod1);

	return(0);
}

void display(Node *start){
	
	//setting up a new node
	Node *nod3;
	//setting new node equal to input
	nod3 = start;
	
	//while nod3 is not equal to null, we print out the list by each node
	while (nod3 != NULL){
		fprintf(stdout, "%hhd ", nod3 -> info);
		nod3 = nod3 -> right;
	}

	fprintf(stdout, "\n");
}
