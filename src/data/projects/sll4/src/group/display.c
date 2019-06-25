#include <stdio.h>
#include "group.h"

//////////////////////////////////////////////////////////////////////
//
// ldisplay() - display the list group in an organized fashion (list
//              by list) or to display an isolated list from the group
//              of lists (as indicated by the pos parameter).
//
//    behavior: on a NULL group, output "<NULL>", return -1
//              on an EMPTY group, output "<EMPTY>", return 0
//              on an error state, output "<ERROR>", return -2
//
//              pos serves a dual purpose:
//                  -1: displays all lists in the list group
//                   0-n: displays that particular list in the group
//
//      output: (if pos is a -1):
//              <0>: 2 -> 4 -> 8 -> NULL
//              <1>: 3 -> 6 -> NULL
//              <2>: -> NULL
//              <3>: 12 -> 36 -> 96 -> 112 -> 119 -> NULL
//
//              (if pos is a 1):
//              <1>: 3 -> 6 -> NULL
//
//return value: the number of lists displayed
//
//        note: ALL output ends with a newline character
//
sli ldisplay(Group *myListGroup, sli pos)
{
	//Setting up needed varbles.
	List *tmp = NULL;
	sli count = 0;
	//checking for any undesired group/pos conditions, returning errors if
	//needed, otherwise proceeding as normal.
	if (myListGroup == NULL){
		fprintf(stdout, "<NULL>\n");
		return(-1);

	} else if (myListGroup -> initial == NULL){
		fprintf(stdout, "<EMPTY>\n");
		return(0);
	} else if (pos < -1){
		fprintf(stdout, "<ERROR>\n");
		return(-2);
	} else if (pos == -1){
		//iterate through the group, displaying each list and its contents.
		tmp = myListGroup -> initial;
		while (tmp != NULL){
			fprintf(stdout, "<%ld>: ", count);
			displayf(tmp, 0);
			count++;
			tmp = tmp -> next;
		}
	} else if (pos > lgetpos(myListGroup, myListGroup -> closing)){
		fprintf(stdout, "<ERROR>\n");
		return(-2);
	} else if (pos >= 0){
		//iterate through the group to the desired list, then display it
		//and its place in the group
		tmp = myListGroup -> initial;
		for(count = pos - 1; count >= 0; count--){
			tmp = tmp -> next;
		}
		fprintf(stdout, "<%ld>: ", pos);
		displayf(tmp, 0);
		count = 1;
	}
	return(count);
}

