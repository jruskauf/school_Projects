#include "tree.h"

//////////////////////////////////////////////////////////////////////
//
//grabnode()  - grab node out of indicated tree, ensuring integrity
//              is maintained (tree is modified)
//              
// status code: this function can generate the following status codes
//                  DLT_SUCCESS: normal operation
//                  DLT_EMPTY:   tree is now EMPTY after grabnode_r()
//                  DLT_NULL:    tree is NULL
//                  DLT_ERROR:   error occurred (tree is NULL,
//                               tried to grab from an empty tree)
//
//              The key with getting a node out of the tree is 
//              that, in many cases, you are removing a parent;
//              so, what takes its place?
//
//              as with the other functions, you may use no more
//              than one return() statement per function.
//
code_t grabnode(Tree **myTree, Node **newNode)
{
	// to be implemented (remove this comment upon completion)
	return (DLT_DEFAULT_FAIL);
}
