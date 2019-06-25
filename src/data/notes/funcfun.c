#include <stdio.h>
#include <stdlib.h>

/*===============================================================+
||								||
||								||
||								||
||								||
||								||
||								||
||								||
+===============================================================*/

// function prototypes
char func1 (char  a, char  b); // full "pass by value" function
char func2 (char  a, char *b); // a is "by by value", b "by address"
void func3 (char *x, char *y); // x and y are "by address"

int main ()
{
	char j     = 5;
	char k     = 7;
	char *m    = NULL;
	char *zard = NULL;

	m    = &j;
	zard = &k;

	fprintf (stdout, " j    is: %hhd\n",  j);
	fprintf (stdout, " k    is: %hhd\n",  k);
	fprintf (stdout, "*m    is: %hhd\n", *m);
	fprintf (stdout, "*zard is: %hhd\n", *zard);

	*zard = func1 (j, k);

	fprintf (stdout, " j    is: %hhd\n",  j);
	fprintf (stdout, " k    is: %hhd\n",  k);
	fprintf (stdout, "*m    is: %hhd\n", *m);
	fprintf (stdout, "*zard is: %hhd\n", *zard);

	j = func2 (j, zard);
		
	fprintf (stdout, " j    is: %hhd\n",  j);
	fprintf (stdout, " k    is: %hhd\n",  k);
	fprintf (stdout, "*m    is: %hhd\n", *m);
	fprintf (stdout, "*zard is: %hhd\n", *zard);

	func3 (m, zard);

	fprintf (stdout, " j    is: %hhd\n",  j);
	fprintf (stdout, " k    is: %hhd\n",  k);
	fprintf (stdout, "*m    is: %hhd\n", *m);
	fprintf (stdout, "*zard is: %hhd\n", *zard);


	return (0);

}

char func1 (char a, char b)
{
	a = a + 7;
	b = b * 2;

	fprintf (stdout, "a is: %hhd\n", a);
	fprintf (stdout, "b is :%hhd\n", b);

	a = a + 3;
	b = b - 2;

	return (b);

}

char func2 (char a, char *b)
{
	a  =  a + 7;
	*b = *b * 2;

	fprintf (stdout, "a is: %hhd\n",  a);
	fprintf (stdout, "*b is: %hhd\n", *b);

	a  =  a + 3;
	*b = *b - 2;

	return (a);
}

void func3 (char *x, char *y)
{
	*x = *x + 7;
	*y = *y * 2;

	fprintf (stdout, "*x is: %hhd\n", *x);
	fprintf (stdout, "*y is: %hhd\n", *y);

	*x = *x + 3;
	*y = *y - 2;

}


