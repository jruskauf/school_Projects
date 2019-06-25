#include <stdio.h>
#include "node.h"

void display(Node *);

int main()
{
	// rewrite node-app-display to use the node library functions
	// (mknode(), specifically). The resulting output
	// should be IDENTICAL to the original node-app-display program.
	
	//setting up nodes to use
	Node *tmp, *tmp2;
	//setting a variable for input
	char input;

	//setting up a node with two variables pointing to it	
	tmp = tmp2 = mknode(0);
	
	//starting to build the list
	fprintf(stdout, "Enter a value (-1 to quit): ");
	fscanf(stdin, "%hhd", &input);

	//while the input is not -1, build the list node by node containing the
	//values inputted through the command line prompt.  If -1 is the input,
	//the node to the right of tmp2 is removed and then pointed to NULL.
	while (input != -1){

		tmp2 -> info = input;
		tmp2 -> right = mknode(0);
		fprintf(stdout, "Enter a value (-1 to quit): ");
		fscanf(stdin, "%hhd", &input);

		if (input == -1){	

			rmnode(tmp2 -> right);
			tmp2 -> right = NULL;

		} else {	

			tmp2 = tmp2 -> right;

		}
	}	
	// Display list from start to end by calling the display() 
	// function, passing in a pointer to the start of the list.
	
	display(tmp);
	
	return(0);
}

void display(Node *start)
{
	//Setting up new node
	Node *tmp3;
	//setting the new node equal to the input
	tmp3 = start;
	//while the node does not equal null, print out the value contained in
	//the node.
	while (tmp3 != NULL){
		fprintf(stdout, "%hhd -> ", tmp3 -> info);
		tmp3 = tmp3 -> right;
	}
	fprintf(stdout, "NULL\n");	
}
