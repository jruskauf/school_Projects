#include "list.h"

//////////////////////////////////////////////////////////////////////
//
//  mklist() - allocate, initialize, and return a pointer to the
//             newly allocated and initialized list struct.
//
//status code: this function generates the following status codes:
//               DLL_SUCCESS:       no problems encountered
//               DLL_EMPTY:         result of normal operation
//               DLL_MALLOC_FAIL:   error on creation
//               DLL_ALREADY_ALLOC: list pointer already allocated
//               DLL_NULL:          list remains in NULL state
//               DLL_ERROR:         an error has taken place
//
//             be sure you perform any necessary error checking,
//             and that any and all struct members are appropriately
//             initialized.
//
//             as with the other functions, you may use no more
//             than one return() statement per function.
//
code_t mklist(List **newList)
{
	//setting up the status code as the beginning error statement
        code_t status = DLL_ERROR; 
	//checking if the newlist is either null or undefined, if so we spit
	//out an error.  If the list is already allocated we spit out an error
	//for that.  Otherwise we allocate a new list.
	if (newList == NULL || newList == UNDEFINED){
		status = DLL_INVALID | status;
	} else if ((*newList) != NULL){
		status = status | DLL_ALREADY_ALLOC;
	} else {
		(*newList) = (List *)malloc(sizeof(List));
		(*newList) -> lead = NULL;
		(*newList) -> last = NULL;
		//if the new list didn't allocate, spit out an error, otherwise
		//report a new empty list.
		if ((*newList) == NULL || (*newList) == UNDEFINED){
			status = status | DLL_MALLOC_FAIL | DLL_NULL;
			(*newList) = NULL;
		} else {
			status = DLL_EMPTY | DLL_SUCCESS;
			(*newList) -> qty = 0;
		}
	}
        return(status);
}
