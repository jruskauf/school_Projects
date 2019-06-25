#include "group.h"

//////////////////////////////////////////////////////////////////////
//
// mkgroup() - a group library function to allocate and initialize a 
//             new group.
//
//   behavior: on error, return NULL.
//
//       note: as with the other functions, you may use no more
//             than one return() statement per function.
//
Group *mkgroup(void)
{
    //mallocing out the needed memory, setting initial to null.  if this fails,
    //return the group as null.
    Group *myGroup = malloc(sizeof(Group));
    myGroup -> initial = NULL;

    if (!myGroup){
	   myGroup = NULL;
    }

    return(myGroup);
}
