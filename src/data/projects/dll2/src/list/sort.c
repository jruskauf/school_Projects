#include "list.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
//
// sortlist() - a list library function to sort an existing list
//              according to the mode indicated.
//
//              the original list is **MODIFIED**, and becomes the
//              sorted list.
//
//              be sure to utilize existing list and node library
//              functions to facilitate your implementation. Do NOT
//              reinvent the wheel.
//
//   modes are: 0 - least to greatest (least is first)
//              1 - greatest to least (greatest is first)
//              2 - reverse order of original list
//
//    behavior: on error, list becomes NULL.
//              on invalid mode, MOD by total modes and continue,
//                  performing whatever that result is.
//
// status code: this function can generate the following status codes
//                DLL_SUCCESS: normal operation
//                DLL_NULL:    list is NULL
//                DLL_EMPTY:   list is empty
//                DLL_ERROR:   error encountered
//                DLL_INVALID: list does not exist
//
//              as with the other functions, you may use no more
//              than one return() statement per function.
//
//              do not count; navigate by comparison
//
code_t  sortlist(List **myList, int mode)
{   
    code_t status = DLL_ERROR;
    //checking if the list is in a proper state before we begin to sort it,
    //otherwise we print out an error.
    if(myList != NULL){
	if((*myList) != NULL){
	    if((*myList) -> lead != NULL){
		if((*myList) -> lead -> right != NULL){
		    //if not a valid mode, we mod by 3 and continue as normal.
		    if(mode > 2){
			mode = mode % 3;
		    }

		    //if mode equals zero, we set nods to lead and last and
		    //iterate the node at the last position backwards through
		    //the list, checking the value to of the node against the
		    //start, and if the node is greater than the start, we swap.
		    //we then iterate start forward through the list to sort the
		    //rest of the list properly.
		    if (mode == 0){
 		        Node *start = NULL;
		        Node *tmp1  = NULL;
		        start = (*myList) -> lead;
		        tmp1 = (*myList) -> last;
			while(start -> right != NULL){

			    if(start -> VALUE > tmp1 -> VALUE && tmp1 != NULL){
				swapnode(myList, tmp1, start);
				start = (*myList) -> lead;
				tmp1  = (*myList) -> last;

			    }else if(tmp1  == start){
				start = start -> right;
				tmp1 = (*myList) -> last;

		    	    } else {
				tmp1 = tmp1 -> left;

		   	    }
			} 	
			status = DLL_SUCCESS;

		    //if mode equals one, we set nods to lead and last and
		    //iterate the node at the last position backwards through
		    //the list, checking the value to of the node against the
		    //start, and if the node is less than the start, we swap.
		    //we then iterate start forward through the list to sort the
		    //rest of the list properly.
		    } else if (mode == 1){
 		        Node *start = NULL;
		        Node *tmp1  = NULL;
		        start = (*myList) -> lead;
		        tmp1 = (*myList) -> last;
			while(start -> right != NULL){

			    if(start -> VALUE < tmp1 -> VALUE && tmp1 != NULL){
				swapnode(myList, tmp1, start);
				start = (*myList) -> lead;
				tmp1  = (*myList) -> last;

			    }else if(tmp1  == start){
				start = start -> right;
				tmp1 = (*myList) -> last;

		    	    } else {
				tmp1 = tmp1 -> left;
				
		   	    }
			} 	
			status = DLL_SUCCESS;
		    //if the mode is equal to 2, we set a node at the start and last node in
		    //the list.  Then we iterate each through the list until they meet in the
		    //middle, swapping the nodes to reverse the orientation of the list.
		    } else if(mode == 2){
	      		Node *start = NULL;
			Node *last = NULL;
			start = (*myList) -> lead -> right;
			last = (*myList) -> last -> left;
			while((start -> left != last) && (start -> left != last -> right)){
			    swapnode(myList, start -> left, last -> right);
			    start = start -> right;
			    last = last -> left;
			}
			status = DLL_SUCCESS;    
		    }			
		} else {
		    status = DLL_SUCCESS;
		}	    
	    } else {
		rmlist(myList);
		status = DLL_EMPTY | status;
	    }	
	} else {
	    status = status | DLL_NULL;
	}
    } else {
	rmlist(myList);
	status = DLL_INVALID | status;
    }
    return(status);
}
