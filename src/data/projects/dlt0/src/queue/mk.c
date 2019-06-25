#include "queue.h"

//////////////////////////////////////////////////////////////////////
//
// mkqueue() - allocate and initialize a new queue
//
//       note: the second parameter is to be the created queue's
//             maximum buffer size (bound).
//
//             be sure to utilize existing list and queue library
//             functions to facilitate your implementation. Do NOT
//             reinvent the wheel.
//
//             the front of the queue should track the first of
//             the underlying list; the back of the queue should
//             track the last node of the list.
//
//     bufsiz: a queue buffer size of 0 indicates an unbounded queue
//             > 0 will limit the total number of nodes in the queue
//
//status code: this function can generate the following status codes:
//                 DLQ_SUCCESS:     no problems encountered
//                 DLQ_EMPTY:       result of normal operation
//                 DLQ_CREATE_FAIL: error on creation
//                 DLQ_NULL:        queue remains in NULL state
//                 DLQ_INVALID:     queue does not exist
//                 DLQ_ERROR:       an error has taken place
//
//       note: as with the other functions, you may use no more
//             than one return() statement per function.
//
code_t mkqueue(Queue **newQueue, ulli bufsiz)
{
    
    code_t status = DLQ_ERROR;
    //if the queue doesn't exist, report an error.
    if(newQueue != NULL){
	//if the queue is null, conitue normall, otherwise report an error.
	if((*newQueue) == NULL){
	    //malloc out the necessary memory for the queue and create a new
	    //list for it to use, setting front and back of the queue to track
	    //lead and last respectively.
	    List *data = NULL;
	    (*newQueue) = (Queue*)malloc(sizeof(Queue*));
	    mklist(&data);
	    (*newQueue) -> data = data;
	    (*newQueue) -> front = (*newQueue) -> data -> lead;
	    (*newQueue) -> back = (*newQueue) -> data -> last;
	    //setting buffsize if the size is greater than 0
	    if(bufsiz > 0)
		(*newQueue) -> buffer = bufsiz;
	    //if the queue is empty, report a success, otherwise report an error
	    if((*newQueue) != NULL){
		status = DLQ_EMPTY | DLQ_SUCCESS | DLL_EMPTY | DLL_SUCCESS;
	    } else {
		status = status | DLQ_CREATE_FAIL | DLQ_NULL;
	    }
	} else {
	    status = status | DLQ_CREATE_FAIL;
	}
    } else {
	status = DLQ_INVALID | status;
    }
    return (status);
}
