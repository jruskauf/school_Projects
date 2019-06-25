#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main()
{
	Node *tmp	= NULL;
	Node *tmp2   = NULL;

	int   testno = 0;

	UNIT_CODE	= 0;

	fprintf(stdout, "UNIT TEST: node library cpnode() function\n");
	fprintf(stdout, "=========================================\n");

	tmp2		 = cpnode(tmp);

	fprintf(stdout, "Test %d: Copying a NULL node ...\n", testno++);
	if (tmp2 == NULL)
		fprintf(stdout, " you have: NULL (success)\n");
	else
		fprintf(stdout, " you have: *NOT* NULL\n");

	fprintf(stdout, "should be: NULL (success)\n\n"); 
	fflush(stdout);
	
	tmp		  = mknode(37);
	tmp2		 = cpnode(tmp); 

	fprintf(stdout, "Test %d: Copying a node ...\n", testno++);
	if (tmp2	== UNDEFINED)
		fprintf(stdout, " you have: UNDEFINED\n");
	else if ((tmp != NULL) && (tmp2 != NULL) && (tmp != tmp2))
		fprintf(stdout, " you have: different (success)\n");
	else if ((tmp == NULL) && (tmp2 == NULL))
		fprintf(stdout, " you have: NULL\n");
	else
		fprintf(stdout, " you have: the same\n");

	fprintf(stdout, "should be: different (success)\n\n"); 
	fflush(stdout);

	if (tmp != NULL)
		tmp -> info  = 57;

	fprintf(stdout, "Test %d: Changing tmp ...\n", testno++);
	if ((tmp != NULL) && (tmp2 != NULL) && (tmp -> info != tmp2 -> info))
		fprintf(stdout, " you have: different (success)\n");
	else if ((tmp == NULL) && (tmp2 == NULL))
		fprintf(stdout, " you have: NULL\n");
	else
		fprintf(stdout, " you have: the same\n");

	fprintf(stdout, "should be: different (success)\n\n"); 
	fflush(stdout);

	if (tmp != NULL)
	{
		tmp -> right				 = mknode(73);

		if (tmp -> right != NULL)
		{
			tmp -> right -> right	= mknode(81);
			tmp2					 = cpnode (tmp -> right);
		}
	}

	fprintf(stdout, "Test %d: Checking value on copied node in list ...\n", testno++);
	if ((tmp == NULL) || (tmp -> right == NULL) || (tmp2 == NULL))
		fprintf(stdout, " you have: NULL node\n");
	else if (tmp -> right -> info == tmp2 -> info)
		fprintf(stdout, " you have: the same value (success)\n");
	else
		fprintf(stdout, " you have: different\n");
	fprintf(stdout, "should be: the same value (success)\n\n");

	fprintf(stdout, "Test %d: Checking right on copied node in list ...\n", testno++);
	if ((tmp == NULL) || (tmp -> right == NULL) || (tmp2 == NULL))
		fprintf(stdout, " you have: NULL node\n");
	else if (tmp -> right -> right == tmp2 -> right)
		fprintf(stdout, " you have: the same right (success)\n");
	else
		fprintf(stdout, " you have: different\n");
	fprintf(stdout, "should be: the same right (success)\n\n");

	return(0);
}
