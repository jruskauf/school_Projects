#include <stdio.h>
#include "list.h"

int main()
{
	List *myList = NULL;
	Node *tmp    = NULL;
	int   i      = 0;
	int   data[] = { 2, 4, 8, 16, 32, 64 };
	int   testno = 0;

	fprintf(stdout, "UNIT TEST: list library getpos() function\n");
	fprintf(stdout, "=========================================\n");

	fprintf(stdout, "\nTest %d: Running on NULL list ...\n", testno++);
	tmp = NULL;
	i = getpos(myList, tmp);
	fprintf(stdout, " you have: list position %d\n", i);
	fprintf(stdout, "should be: list position -1\n");

	myList       = mklist();

	for (i = 0; i < 6; i++)
	{
		if ((myList != NULL) && (myList != UNDEFINED))
		{
			if (myList -> last == NULL)
			{
				myList -> lead          = mknode(data[i]);
				myList -> last           = myList -> lead;
			}
			else
			{
				myList -> last -> right  = mknode(data[i]);
				myList -> last           = myList -> last -> right;
			}
		}
	}

	fprintf(stdout, "\nDisplaying list, with position values:\n");
	displayf(myList, 1);

	fprintf(stdout, "\nTest %d: Pointing tmp to myList -> lead -> right ...\n", testno++);
	if ((myList != NULL) && (myList != UNDEFINED))
		tmp = myList -> lead -> right;
	i = getpos(myList, tmp);
	fprintf(stdout, " you have: list position %d\n", i);
	fprintf(stdout, "should be: list position 1\n");

	fprintf(stdout, "\nTest %d: Pointing tmp to myList -> last ...\n", testno++);
	if ((myList != NULL) && (myList != UNDEFINED))
		tmp = myList -> last;
	i = getpos(myList, tmp);
	fprintf(stdout, " you have: list position %d\n", i);
	fprintf(stdout, "should be: list position 5\n");

	fprintf(stdout, "\nTest %d: Pointing tmp to myList -> lead -> right -> right -> right ...\n", testno++);
	if ((myList != NULL) && (myList != UNDEFINED))
		tmp = myList -> lead -> right -> right -> right;
	i = getpos(myList, tmp);
	fprintf(stdout, " you have: list position %d\n", i);
	fprintf(stdout, "should be: list position 3\n");

	fprintf(stdout, "\nTest %d: Pointing tmp to myList -> lead -> right -> right ...\n", testno++);
	if ((myList != NULL) && (myList != UNDEFINED))
		tmp = myList -> lead -> right -> right;
	i = getpos(myList, tmp);
	fprintf(stdout, " you have: list position %d\n", i);
	fprintf(stdout, "should be: list position 2\n");

	fprintf(stdout, "\nTest %d: Pointing tmp to myList -> lead ...\n", testno++);
	if ((myList != NULL) && (myList != UNDEFINED))
		tmp = myList -> lead;
	i = getpos(myList, tmp);
	fprintf(stdout, " you have: list position %d\n", i);
	fprintf(stdout, "should be: list position 0\n");

	fprintf(stdout, "\nTest %d: Pointing tmp to invalid node (not in list) ...\n", testno++);
	tmp = mknode(37);
	i = getpos(myList, tmp);
	fprintf(stdout, " you have: list position %d\n", i);
	fprintf(stdout, "should be: list position -2\n");

	fprintf(stdout, "\nTest %d: Pointing tmp to myList -> lead -> right -> right -> right -> right ...\n", testno++);
	if ((myList != NULL) && (myList != UNDEFINED))
		tmp = myList -> lead -> right -> right -> right -> right;
	i = getpos(myList, tmp);
	fprintf(stdout, " you have: list position %d\n", i);
	fprintf(stdout, "should be: list position 4\n");

	return(0);
}
