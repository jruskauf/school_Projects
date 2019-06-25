#include <stdio.h>
#include "node.h"

int main()
{
	Node *tmp, *tmp2, *tmp3, *tmp4;

	tmp		   = (Node *) malloc (sizeof(Node)*1);
	tmp  -> info = 8;
	tmp  -> right  = tmp2 = (Node *) malloc (sizeof(Node)*1);
	tmp2 -> info = 12;
	tmp2 -> right  = NULL;

	tmp3		  = (Node *) malloc (sizeof(Node)*1);
	tmp3 -> info = 17;
	tmp3 -> right  = tmp2;

	tmp2 -> info = tmp2 -> info + 16;

	tmp2 -> right  = tmp4 = (Node *) malloc (sizeof(Node)*1);
	tmp4 -> info = tmp2 -> info - 2;
	tmp4 -> right  = NULL;

	fprintf(stdout, "tmp  points to %p, contains: %d, ", tmp,  tmp  -> info);
	fprintf(stdout, "tmp's right is: %p\n", tmp -> right);
	fprintf(stdout, "tmp2 points to %p, contains: %d, ", tmp2, tmp2 -> info);
	fprintf(stdout, "tmp2's right is: %p\n", tmp2 -> right);
	fprintf(stdout, "tmp3 points to %p, contains: %d, ", tmp3, tmp3 -> info);
	fprintf(stdout, "tmp3's right is: %p\n", tmp3 -> right);
	fprintf(stdout, "tmp4 points to %p, contains: %d, ", tmp4, tmp4 -> info);
	fprintf(stdout, "tmp4's right is: %p\n", tmp4 -> right);

	return(0);
}
