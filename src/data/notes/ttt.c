#include <stdio.h>
#include <stdlib.h>

#define  N		0
#define  S		1
#define  E		2
#define	 W		3
#define  NW		4
#define  NE		5
#define  SW		6
#define  SE		7

#define  PLAIN  0
#define  OFFSET 1

#define  TRUE   0
#define  FALSE  1
#define  MAYBE  2

struct sector
{
	char mark;
	struct sector **link;
};
typedef struct sector Sector;

void display(Sector *, int);
int  checkwin(Sector *);

int main()
{
	int num        = 0;
	int value      = 0;
	int result     = 2;
	int offsetNW   = -1;
	int offsetSE   = -1;
	int offsetSW   = 1;
	int location   = 0;
	int hack       = 1;
	int pwn3d      = -2;
	int win        = FALSE;
	int input      = 0;
	int player     = 0;
	int turn       = 0;
	unsigned char row  = -3;
	Sector *arena  = NULL;
	Sector *tmp    = NULL;
	
	arena          = (Sector *)  malloc (sizeof (Sector)   * 9);
	for (num = 0; num < 9; num++)
		(arena+num) -> link  = (Sector **) malloc (sizeof (Sector *) * 8);

	for (num = 0; num < 9; num++) // for each sector in the arena
	{
		if ((num % 3) == 0)
			row        = row + 3;
		tmp = (arena+num);

		tmp -> mark     = ' ';

		tmp -> link[E]  = (arena+(((num % 3) + 1) % 3) + row);
//		fprintf (stdout, "E:%d -> %d, ", num, (((num%3)+1)%3)+row);
		tmp -> link[W]  = (arena+((num + 2) % 3) + row);
//		fprintf (stdout, "W:%d -> %d, ", num, ((num+2)%3)+row);
		tmp -> link[N]  = (arena+((6 + num) % 9));
//		fprintf (stdout, "N:%d -> %d, ", num, ((6+num)%9));
		tmp -> link[S]  = (arena+((3 + num) % 9));
//		fprintf (stdout, "S:%d -> %d, ", num, ((3+num)%9));

		location        = ((num+((row/3)+1)*8)-(3*num)-num);
		if ((num != 0) && (num % 4) == 0)
		{
			location    = location + (4 * offsetNW);
			offsetNW     = offsetNW + 2;
		}
		tmp -> link[NW] = (arena+location);
//		fprintf (stdout, "NW:%d -> %d, ", num, location);

		if ((num % 4)  == 0)
		{
			location    = location + (4 * (offsetSE * hack));
			hack        = hack - offsetSE;
			offsetSE    = offsetSE * -1;
		}
		tmp -> link[SE] = (arena+location);
//		fprintf (stdout, "SE:%d->%d, ", num, location);

		location        = ((num + (2 * value)) % 8);
		value           = value + 1;
		if ((num >= 4) && (num % 2) == 0)
		{
			location    = result;
			result      = result * 2;
		}
		tmp -> link[NE] = (arena+location);
//		fprintf (stdout, "NE:%d->%d, ", num, location);

		if ((num >= 2) && (num <= 6) && (num % 2) == 0)
		{
			pwn3d       = pwn3d + (6 * offsetSW);
			location    = pwn3d;
			offsetSW    = offsetSW * -1;
		}

		if (num == 4)
		{
			location = 6;
		}

		if (num == 6)
		{
			location = 2;
		}

		tmp -> link[SW] = (arena+location);

//		fprintf (stdout, "SW:%d->%d\n", num, location);
	}

	//(arena+5) -> mark = 'X';

	fprintf (stdout, "BEST Ultimate Tic Tac Toe v4.0 GOLD MASTER+\n");

	while (win == FALSE)
	{
		display(arena, OFFSET);
		fprintf (stdout, "Player %d, please choose sector: ", player+1);
		fscanf  (stdin,  "%d", &input);

		if ((arena+input) -> mark == ' ')
		{
			if (player == 0) // 'X'
				(arena+input) -> mark = 'X';
			else // 'O'
				(arena+input) -> mark = 'O';
		}

		// check for win
		win = checkwin(arena);

		// switch to other player
		if (win != TRUE)
		{
			if (player == 0)
				player  = 1;
			else
				player  = 0;
		}

		turn = turn + 1;
		if ((turn == 9) && (win == FALSE))
			win   = MAYBE;
	}

	if (win == TRUE)
		fprintf (stdout, "Congratulations. Player %d wins 3 internets\n", player+1);
	else if (win == MAYBE)
		fprintf (stdout, "No. Stop hurting the internet. Just no.\n");

	display(arena, PLAIN);
//	fprintf(stdout, "\n");
//	display(arena, OFFSET);

	return (0);
}

void display(Sector *arena, int mode)
{
	// display the board
	int num  = 0;
	for (num = 0; num < 9; num++) // for each sector in the arena
	{
		if (mode == PLAIN)
			fprintf (stdout, " %c ", (arena+num) -> mark);
		else
		{
			if ((arena+num) -> mark == ' ')
				fprintf (stdout, " %d ", num);
			else
				fprintf (stdout, " %c ", (arena+num) -> mark);
		}

		if ((num % 3) < 2)
			fprintf (stdout, "|");
		else
			fprintf (stdout, "\n");

		if ((num < 6) && ((num % 3) == 2))
			fprintf (stdout, "---+---+---\n");
	}
}

int  checkwin(Sector *arena)
{
	int status    = FALSE;
	int index     = 0;
	int num       = 0;
	int Xmatch    = 0;
	int Omatch    = 0;
	int location  = 0;

	for (num = 0; num < 3; num++)
	{
		Xmatch  = 0;
		Omatch  = 0;
		for (index = 0; index < 3; index++)
		{
			
			location = (num*3)+index;
			if ((arena+location) -> mark != ' ')
			{
				if (((arena+location) -> mark) == (arena+(location+1)) -> mark)
				{
					if ((arena+location) -> mark == 'X')
						Xmatch  = Xmatch + 1;
					else
						Omatch  = Omatch + 1;
				}
			}
		}

		if ((Xmatch == 2) || (Omatch == 2))
		{
			status = TRUE;
			break;
		}

		Xmatch  = 0;
		Omatch  = 0;
		for (index = 0; index < 3; index++)
		{
			location = num+(index*3);
			if ((arena+location) -> mark != ' ')
			{
				if (((arena+location) -> mark) == (arena+(location+3)) -> mark)
				{
					if ((arena+location) -> mark == 'X')
						Xmatch  = Xmatch + 1;
					else
						Omatch  = Omatch + 1;
				}
			}
		}

		if ((Xmatch == 2) || (Omatch == 2))
		{
			status = TRUE;
			break;
		}
	}

	if ((status != TRUE) && ((arena+0) -> mark != ' '))
	{
		Xmatch  = 0;
		Omatch  = 0;
		if ((((arena+0) -> mark) == (arena+(4)) -> mark) &&
		 (((arena+4) -> mark) == (arena+8) -> mark))
		{
			if ((arena+location) -> mark == 'X')
				Xmatch  = Xmatch + 2;
			else
				Omatch  = Omatch + 2;
		}

		if ((Xmatch == 2) || (Omatch == 2))
		{
			status = TRUE;
		}
	}

	if ((status != TRUE) && ((arena+2) -> mark != ' '))
	{
		Xmatch  = 0;
		Omatch  = 0;
		if ((((arena+2) -> mark) == (arena+(4)) -> mark) &&
		 (((arena+4) -> mark) == (arena+6) -> mark))
		{
			if ((arena+location) -> mark == 'X')
				Xmatch  = Xmatch + 2;
			else
				Omatch  = Omatch + 2;
		}

		if ((Xmatch == 2) || (Omatch == 2))
		{
			status = TRUE;
		}
	}

	return (status);
}
