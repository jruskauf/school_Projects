#include "queue.h"

//////////////////////////////////////////////////////////////////////
//
//  dequeue() - grab node off front of queue (queue is modified)
//              
//              be sure to utilize existing list and queue library
//              functions to facilitate your implementation. Do NOT
//              reinvent the wheel.
//
//              the front of the queue should follow the first of
//              the underlying list; the back of the queue should
//              follow the last node of the list.
//
//              the dequeued node pointer, if it exists, does not
//              need to be NULL; any existing content will be
//              discarded.
//
// status code: this function generates the following status codes
//                  DLN_INVALID:  dequeued node does not exist
//                  DLQ_SUCCESS:  normal operation
//                  DLQ_UNDERRUN: tried to dequeue() when empty
//                  DLQ_EMPTY:    queue is EMPTY
//                  DLQ_NULL:     queue is NULL
//                  DLQ_INVALID:  queue does not exist
//                  DLQ_ERROR:    error occurred (queue is NULL,
//                                underrun occurred, etc.)
//
//        note: as with the other functions, you may use no more
//              than one return() statement per function.
//
code_t dequeue(Queue **myQueue, Node **newNode)
{
    code_t status = DLQ_ERROR;
    //if the queue is invalid or null, or if newnode is invalid, or if queue is
    //empty, report an error with fallthrough.  Otherwise, preform the normal
    //operations.
    if(myQueue != NULL){
	if((*myQueue) != NULL){
	    if(newNode != NULL){
		if((*myQueue) -> front != NULL){
		    //grab the node off the end of the list, setting newnode to
		    //that obtained node, and then properly tracking the front
		    //of the queue.  Then report a success whether the list is
		    //empty or populated.
		    List *ltmp = (*myQueue) -> data;
		    Node *tmp = (*myQueue) -> data -> lead;
		    obtain(&ltmp, &tmp);
		    *newNode = tmp;
		    (*myQueue) -> front = (*myQueue) -> data -> lead;
		    if((*myQueue) -> front != NULL){
			status = DLQ_SUCCESS | DLL_SUCCESS;
		    } else {
			status = DLQ_EMPTY | DLQ_SUCCESS | DLL_EMPTY | DLL_SUCCESS;
		    }
		} else {
		    status = status | DLQ_UNDERRUN;
		}
	    } else {
	        status = status | DLN_INVALID;
	    }
	} else {
	    status = status | DLQ_NULL;
	}
    } else {
	status = DLQ_INVALID | status;
    }
    return (status);
}
