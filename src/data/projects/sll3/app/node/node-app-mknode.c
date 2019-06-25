#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main()
{
	Node *tmp1, *tmp2;
	
	fprintf(stdout, "Before calling mknode() ... \n");
	fprintf(stdout, "---------------------------------------------\n");
	fprintf(stdout, "tmp1 has an address of:		%p\n", &tmp1);
	fprintf(stdout, "tmp1 points to:				%p\n",  tmp1);
	fprintf(stdout, "tmp2 has an address of:		%p\n", &tmp2);
	fprintf(stdout, "tmp2 points to:				%p\n",  tmp2);

	tmp1 = mknode(8);

	if (tmp1 == NULL)
	{
		fprintf(stderr, "Error creating new node (tmp1).\n");
		exit(1);
	}

	tmp1 -> right = mknode(13);

	if (tmp1 -> right == NULL)
	{
		fprintf(stderr, "Error creating new node (tmp1 -> right).\n");
		exit(1);
	}

	tmp2 = mknode(7);

	if (tmp2 == NULL)
	{
		fprintf(stderr, "Error creating new node (tmp2).\n");
		exit(1);
	}

	tmp2 -> right = tmp1;
 
	fprintf(stdout, "\nAfter calling mknode() ... \n");
	fprintf(stdout, "---------------------------------------------\n");
	fprintf(stdout, "tmp1 has an address of:		%p\n",   &tmp1);
	fprintf(stdout, "tmp1 points to:				%p\n",	tmp1);
	fprintf(stdout, "tmp1 contains info of:	  %d\n",	tmp1 -> info);
	fprintf(stdout, "tmp1's right pointer points to: %p\n\n",  tmp1 -> right);

	fprintf(stdout, "tmp1's right contains info:	%d\n",	tmp1 -> right -> info);
	fprintf(stdout, "tmp1 right's right points to:	%p\n\n",  tmp1 -> right -> right);
 
	fprintf(stdout, "tmp2 has an address of:		%p\n",   &tmp2);
	fprintf(stdout, "tmp2 points to:				%p\n",	tmp2);
	fprintf(stdout, "tmp2 contains info of:	  %d\n",	tmp2 -> info);
	fprintf(stdout, "tmp2's right pointer points to: %p\n\n",  tmp2 -> right);

	fprintf(stdout, "draw this collection of nodes\n\n");

	return(0);
}
