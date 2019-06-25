#include "queue.h"

//////////////////////////////////////////////////////////////////////
//
//   cpqueue() - duplicate a given queue (especially the state of
//               its contents), in a new queue.
//
//               be sure to utilize existing list and queue library
//               functions to facilitate your implementation. Do NOT
//               reinvent the wheel.
//
//  status code: this function can generate the following status code
//                 DLQ_SUCCESS:     normal operation
//                 DLQ_CREATE_FAIL: *newQueue already exists
//                 DLQ_EMPTY:       curQueue is EMPTY
//                 DLQ_NULL:        queue is NULL
//                 DLQ_INVALID:     queue does not exist
//                 DLQ_ERROR:       an error occurred
//
//         note: as with the other functions, you may use no more
//               than one return() statement per function.
//
code_t cpqueue(Queue *curQueue, Queue **newQueue)
{
    code_t status = DLQ_ERROR;
    //if the queue is null, check is the newqueue exists.  If yes, is it null?
    //if not existant, report an error, as well as errors if the newqueue is null
    //or not.
    if(curQueue != NULL){
	//If the current queue is empty, then check if newqueue is empty.  If so,
	//report a success, if not, then an error. Otherwise, continue with
	//normal operation.
	if(curQueue -> front != NULL){
	    //malloc the newqueue and then copy the old data from the old queue
	    //into a list, then set the new list up accordingly with the new
	    //queue, reporting a successful operation at the end.
	    mkqueue(newQueue, 0);
	    List *newtmp = NULL;
	    List *oldtmp = curQueue -> data;
	    oldtmp -> lead = curQueue -> data -> lead;
	    oldtmp -> last = curQueue -> data -> last;
	    cplist(oldtmp, &newtmp);

	    (*newQueue) -> data = newtmp;
	    (*newQueue) -> front = newtmp -> lead;
	    (*newQueue) -> back  = newtmp -> last;
	    status = DLQ_SUCCESS | DLL_SUCCESS;
	} else {
	    if((*newQueue) != NULL){
	        status = status | DLQ_CREATE_FAIL;
	    } else {
		status = DLQ_EMPTY | DLQ_SUCCESS | DLL_EMPTY | DLL_SUCCESS;
	    }
	}
    } else {
	if(newQueue != NULL){
	    if((*newQueue) != NULL){
	        status = status | DLQ_CREATE_FAIL;
	    } else {
		status = status | DLQ_NULL;
	    }
	} else {
	    status = DLQ_INVALID | status;
	}     
    }
    return (status);
}
