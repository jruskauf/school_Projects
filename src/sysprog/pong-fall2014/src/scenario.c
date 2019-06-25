#include "pong.h"

Pong *set_scenario(Pong *game, int level)
{
	Player  *ptmp = NULL;
	Object  *otmp = NULL;
	Missile *mtmp = NULL;
	int         i = 0;

	ptmp = game -> paddle;
	while (ptmp != NULL)
	{
		switch(level)
		{
			case 1:
				if (ptmp -> num == 0)
				{
					ptmp -> pos.x = ptmp -> wide;
					ptmp -> pos.y = game -> field.height / 2 - ptmp -> high / 2;
				}
				else if (ptmp -> num == 1)
				{
					ptmp -> pos.x = game -> field.width - (ptmp -> wide * 2);
					ptmp -> pos.y = game -> field.height / 2 - ptmp -> high / 2;
				}
				else if (ptmp -> num == 2)
				{
					ptmp -> pos.x = game -> field.width / 2 - ptmp -> wide / 2;
					ptmp -> pos.y = ptmp -> high;
				}
				else if (ptmp -> num == 3)
				{
					ptmp -> pos.x = game -> field.width / 2 - ptmp -> wide / 2;
					ptmp -> pos.y = game -> field.height - (ptmp -> high * 2);
				}
				break;

			default:
				break;
		}
		ptmp = ptmp -> next;
	}

	otmp = game -> item;
	for(i = 0; i < game -> num[HWALL]; i++)
	{
		switch(level)
		{
			case 1:
				while (otmp != NULL)
				{
					if (otmp -> type == HWALL)
					{
						break;
					}

					otmp = otmp -> next;
				}

				if (otmp != NULL)
				{
					if      ((i == 0) && (otmp -> type == HWALL))
					{
						otmp -> pos.x = 0;
						otmp -> pos.y = 0;
						otmp -> solid = SOLID;
						otmp -> visible = 1;
					}
					else if ((i == 1) && (otmp -> type == HWALL))
					{
						otmp -> pos.x = 0;
						otmp -> pos.y = game -> field.height - (otmp -> high);
						otmp -> solid = SOLID;
						otmp -> visible = 1;
					}
				}
				break;

			default:
				break;
		}
	}

	otmp = game -> item;
	for(i = 0; i < game -> num[VWALL]; i++)
	{
		switch(level)
		{
			case 1:
				while (otmp != NULL)
				{
					if (otmp -> type == VWALL)
					{
						break;
					}

					otmp = otmp -> next;
					if ((i == 0) && (otmp -> type == VWALL))
					{
						otmp -> pos.x = game -> field.width - (otmp -> wide);
						otmp -> pos.y = 0;
						otmp -> solid = SOLID;
						otmp -> visible = 1;
					}
				}
		}
	}
	return (game);
}
