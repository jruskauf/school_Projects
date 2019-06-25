#include "list.h"

//////////////////////////////////////////////////////////////////////
//
// sortlist() - a list library function to sort an existing list
//              according to the mode indicated.
//
//              the original list is **preserved**, and the altered/
//              sorted list (a new list) is what is returned.
//
//   modes are: 0 - least to greatest (least is first)
//              1 - greatest to least (greatest is first)
//              2 - reverse order of original list
//
//    behavior: on error, return NULL.
//              on invalid mode, MOD by total modes and continue,
//                  performing whatever that result is.
//
//        note: you are to have only ONE return statement for this
//              entire function. Change the existing one as needed.
//
List *sortlist(List *myList, int mode)
{
	//setting up variables to use
	List *sortList = NULL;
	Node *tmp1     = NULL;
	Node *tmp2     = NULL;
	int count1   =    0;
	int count2   =    0;

	//checking to see if the list is in any undesirable states, and if not,
	//we continue on to sorting the list by the mode provided.
	if (myList == NULL || myList == UNDEFINED){
		sortList = NULL;
	} else if (myList -> lead == NULL || myList -> lead -> right == NULL){
		sortList = cplist(myList);
	} else {
		//copying the list provided to a new list, so as to preserve
		//the original.  Then we check to see if the mode is valid,
		//and if not we mod it to make a valid mode.
		sortList = cplist(myList);
		if (mode < 0 || mode > 2){
			mode = mode%3;
		}
		
		//This handles sorting from least to greatest.  This is done by
		//setting tmp1 to the lead node and tmp2 to the right of that.
		//Then, iterate tmp2 through the list, swapping nodes with tmp1
		//if tmp2 is less than tmp1, and then setting tmp1 and tmp2 back
		//to their initial positions.  Once the lowest value node is
		//at the left, the process is repeated until the last node is 
		//reached, which at that point is the highest value.
		if (mode == 0){
			tmp1 = sortList -> lead;
			tmp2 = sortList -> lead  -> right;
			count1 = getpos(sortList, tmp1);	
			count2 = getpos(sortList, tmp2);
			while (tmp1 -> right != NULL){
				if (tmp1 -> info > tmp2 -> info && tmp2 != NULL){
					sortList = swapnode(sortList, tmp1, tmp2);
					tmp1 = setpos(sortList, count1);
					tmp2 = tmp1 -> right;
				} else if (tmp2 -> right == NULL){
					count1++;
					count2++;
					tmp1 = setpos(sortList, count1);
					tmp2 = setpos(sortList, count2);
				

				} else {
					tmp2 = tmp2 -> right;
					
				}
			}

		//This is the exact same as the above code, except it is 
		//checking whether or not tmp2 is greater than tmp1, 
		//resulting in a least that goes from greatest to least.
		} else if (mode == 1){
			tmp1 = sortList -> lead;
			tmp2 = sortList -> lead  -> right;
			count1 = getpos(sortList, tmp1);	
			count2 = getpos(sortList, tmp2);
			while (tmp1 -> right != NULL){
				if (tmp1 -> info < tmp2 -> info && tmp2 != NULL){
					sortList = swapnode(sortList, tmp1, tmp2);
					tmp1 = setpos(sortList, count1);
					tmp2 = tmp1 -> right;
				} else if (tmp2 -> right == NULL){
					count1++;
					count2++;
					tmp1 = setpos(sortList, count1);
					tmp2 = setpos(sortList, count2);
				} else {
					tmp2 = tmp2 -> right;
					
				}
			}

		//This reverses the list by swapping nodes tmp1 and tmp2, which
		//are set at lead and last, and iterate forwards and backwards 
		//through the list respectively.  Once they reach the middle,
		//the process is completed, whether the list is equal or odd
		//in number of nodes.
		} else if (mode == 2){
			tmp1 = sortList -> lead;
			tmp2 = sortList -> last;
			count1 = getpos(sortList, tmp1);	
			count2 = getpos(sortList, tmp2);
			while (count1 < count2){
				sortList = swapnode(sortList, tmp2, tmp1);
				count1++;
				count2--;
				tmp1 = setpos(sortList, count1);
				tmp2 = setpos(sortList, count2);
			}
		}
	}

	//returning new list
	return(sortList);
}
