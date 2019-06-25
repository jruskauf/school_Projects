#include<stdio.h>
#include "pong.h"

void display_usage()
{
	fprintf(stdout, "Usage: pong [OPTION]...\n");
	fprintf(stdout, "Play a game of pong.\n");

	fprintf(stdout, "\nBasic Options and Output Behaviors:\n");
	fprintf(stdout, "  -h, --help              display this help information\n");
	fprintf(stdout, "  -V, --version           output version information\n");
	fprintf(stdout, "  -v, --verbose           enable/increase verbosity level\n");
	fprintf(stdout, "  -D, --debug             enable debug output\n");
	fprintf(stdout, "  -q, --quiet             toggle all program output off\n");
	fprintf(stdout, "  -n, --num-paddles=NUM   number of paddles (default:   2)\n");
	fprintf(stdout, "  -L, --logos             display opening logos\n");
	fprintf(stdout, "  -S, --sfx               enable sound effects\n");
	fprintf(stdout, "\nNetwork Settings:\n");
	fprintf(stdout, "  -d, --daemon            start program in daemon mode\n");
	fprintf(stdout, "  -f, --foreground        daemon mode, don't detach\n");
	fprintf(stdout, "  -s, --server=IP|HOST    client mode, connect to server\n");
	fprintf(stdout, "\nSpecify player settings (lead with -P argument):\n");
	fprintf(stdout, "  -P, --player-config     set player settings\n");
	fprintf(stdout, "  -J, --joystick=on|off   joystick support  (default: off)\n");
	fprintf(stdout, "  -K, --keyboard=on|off   keyboard support  (default:  on)\n");
	fprintf(stdout, "  -M, --mouse=on|off      mouse support     (default: off)\n");
	fprintf(stdout, "\n");
}
