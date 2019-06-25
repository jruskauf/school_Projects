#include <stdio.h>
#include <stdlib.h>

int main()
{
	//////////////////////////////////////////////////////////////////////////
	// real variables such as "a" are always assigned to a value, while 
	// pointers such as "*b" and double pointers such as "**i" are always
	// assigned to NULL
	//

	signed char   a = 7,        *b = NULL;
	unsigned char c = 8,        *d = NULL;
	signed int    e = 9,        *f = NULL;
	float	      g = 3.145938, *h = NULL;
	signed char **i = NULL;

	b = &a; // "b" (single pointer) points at real variable "a"
	d = &c; // "d" (single pointer) points at real variable "c"
	f = &e; // "f" (single pointer) points at real variable "e"
	h = &g; // "h" (single pointer) points at real variable "g"
	i = &b; // "i" (double pointer) points at single pointer "b"
	
	//////////////////////////////////////////////////////////////////////////
	// "&a" is the address of "a", while "a" contains the value of "7"
	//
	
	fprintf(stdout, "a contains: %hhd, address of a: %p\n", a, &a);
	
	//////////////////////////////////////////////////////////////////////////
	// "&b" is the address of "b", while "b" contains the address of "a",
	// and "*b" contains the value of "a"
	//
	
	fprintf (stdout, "b contains %p, *b contains: %hhd, address of b: %p\n", b, *b, &b);
	
	//////////////////////////////////////////////////////////////////////////
	// "&c" is the address of "c", while "c" contains the value of "8"
	// 

	fprintf (stdout, "c contains: %hhu, address of c: %p\n", c, &c);

	//////////////////////////////////////////////////////////////////////////
	// "d" contains the address of "c", while "*d" contains the value of "c",
	// while "&d" contains the address of "d"
	//
	
	fprintf (stdout, "d contains: %p, *d contains: %hhu, address of d: %p\n", d, *d, &d);

	//////////////////////////////////////////////////////////////////////////
	// "&e" contains the address of "e", while "e" contains the value of "9"
	//
	
	fprintf(stdout, "e contains: %hhd, address of c: %p\n", e, &e);

	//////////////////////////////////////////////////////////////////////////
	// "f" contains the address of "e", while "*f" contains the value of "c",
	// while "&f" contains the address of "f"
	//
	
	fprintf (stdout, "f contains: %p, *f contains %d, address of f: %p\n", f, *f, &f);

	//////////////////////////////////////////////////////////////////////////
	// "&g" contains the address of "g", while "g" contains the value of 
	// "3.145938"
	//

	fprintf (stdout, "g contains: %.2f, address of g: %p\n", g, &g);

	//////////////////////////////////////////////////////////////////////////
	// "h" contains the address of "g", while "*h" contains the value of "g",
	// and "&h" contains the address of "h" 
	//
	
	fprintf (stdout, "h contains %p, *h contains %.2f, address of h: %p\n", h, *h, &h);
	
	//////////////////////////////////////////////////////////////////////////
	// now for the double pointery goodness
	// "i" points to the address of "b", while "*i" points to the address of
	// "a", while "**i" points to the value of "a", and "&i" contains the
	// address of "i".
	//

	fprintf (stdout, "i contains: %p, *i contains: %p, **i contains %hhd, address of i: %p\n", i, *i, **i, &i);

	return(0);

}
