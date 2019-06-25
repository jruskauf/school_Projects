#include <getopt.h>
#include <strings.h>
#include "pong.h"

Config *args(int argc, char **argv, Pong *game)
{
	int         option_index              = 0;
	int         status                    = 0;
	Config     *cfg                       = NULL;
	Config     *tmp                       = NULL;
	signed char opt;

	static struct option long_options[] = {
        { "help",             0, 0, 'h' }, // { long option, argument, 0, short option }
        { "version",          0, 0, 'V' },
        { "verbose",          0, 0, 'v' },
        { "debug",            0, 0, 'D' },
        { "quiet",            0, 0, 'q' },
        { "num-paddles",      1, 0, 'n' },
        { "logos",            0, 0, 'L' },
        { "sfx",              0, 0, 'S' },
        { "daemon",           0, 0, 'd' },
        { "foreground",       0, 0, 'f' },
        { "server",           1, 0, 's' },
        { "player-settings",  0, 0, 'P' },
        { "joystick",         1, 0, 'J' },
        { "keyboard",         1, 0, 'K' },
        { "mouse",            1, 0, 'M' },
        { 0,                  0, 0, 0   }
	};

	while ((opt = getopt_long(argc, argv, ":hVvDqn:LSdfs:PJ:K:M:", long_options, &option_index)) != -1)
	{
		option_index = 0;

		switch(opt)
		{
			case '?':
			case 'h':
				display_usage();
				exit(0);
				break;

			case 'V':
				display_version();
				exit(0);
				break;

			case 'v':
				verbosity_level           = verbosity_level + 1;

				if (verbosity_level == 1)
					verbose               = stdout;
				else if (verbosity_level == 2)
					verbose2              = stdout;
				else
					verbose3              = stdout;
				break;

			case 'D':
				debug                     = stdout;
				break;

			case 'q':
				debug                     = NULL;
				output                    = NULL;
				verbose                   = NULL;
				break;

			case 'n':
				game -> num_paddles       = atoi(optarg);
				break;

			case 'L':
				game -> logos             = ON;
				break;

			case 'S':
				game -> sfx               = ON;
				break;

			case 'd':
				// not yet implemented
				break;

			case 'f':
				// not yet implemented
				break;

			case 's':
				// not yet implemented
				break;

			case 'P': //Works with J, K, or M
				if (cfg == NULL)
				{
					cfg                   = (Config *) malloc (sizeof(Config));
					tmp                   = cfg;
					tmp  -> next          = NULL;
					game -> num_players   = 0;
				}
				else
				{
					tmp -> next           = (Config *) malloc (sizeof(Config));
					tmp                   = tmp -> next;
				}

				tmp  -> num               = game -> num_players;
				game -> num_players       = game -> num_players + 1;
				tmp  -> device            = KEYBOARD;
				tmp  -> location          = LOCAL;
				tmp  -> type              = HUMAN;

				if (game -> num_paddles   < game -> num_players)
					game -> num_paddles   = game -> num_players;
				break;

			case 'J':
			case 'K':
			case 'M':
				if (tmp == NULL)
				{
					fprintf(stderr, "[error] Must specify leading '-P'! Ignoring.\n");
					break;
				}

				if (strcasecmp("on", optarg) == 0)
					status                = ON;
				else
					status                = OFF;
					
				if (opt == 'J')
				{
					if (status == ON)
						tmp  -> device    = JOYSTICK;
					else
						tmp  -> device   &= ~JOYSTICK;	
				}
				else if (opt == 'K')
				{
					if (status == ON)
						tmp  -> device    = KEYBOARD;
					else
						tmp  -> device   &= ~KEYBOARD;	
				}
				else
				{
					if (status == ON)
						tmp  -> device    = MOUSE;
					else
						tmp  -> device   &= ~MOUSE;	
				}
				break;

			default:
				fprintf(stderr, "[error] Unrecognized option '%c'\n", opt);
				fprintf(stderr, "\tRun '%s --help' for usage\n\n", *(argv+0));
				exit(1);
				break;
		}
	}
		
	return(cfg);
}
