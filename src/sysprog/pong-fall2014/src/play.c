#include "pong.h"

int sfxplay(void *data)
{
	Pong *game                 = (Pong *) data;
	char *sfx_filename         = NULL;
	char *sfx_filename_short   = NULL;
	char *sfx_wd               = NULL;
	int   count                = 0;
	int   i                    = 0;

	if (game -> sfx           == ON)
	{
		if (Mix_OpenAudio(11025, AUDIO_U8, 2, 128) == -1)
		{
			fprintf(stderr, "[error] Mix_OpenAudio()\n");
			exit(3);
		}

		sfx_wd                 = dirproc("sfx");

		for (i = 0; i <= 2; i++)
		{
			count              = strlen("ballX.wav");
			sfx_filename_short = (char *) malloc (sizeof(char) * count);
			sprintf(sfx_filename_short, "ball%d.wav", i);

			count              = strlen(sfx_wd)+strlen(sfx_filename_short);
			sfx_filename       = (char *) malloc (sizeof(char) * count);
			sprintf(sfx_filename, "%s/%s", sfx_wd, sfx_filename_short);
			fprintf(verbose, "[verbose]    sfx ball%d ... ", i);
			ball[i]            = Mix_LoadWAV(sfx_filename);
			if (ball[i]       == NULL)
			{
				fprintf(verbose, "FAIL\n");
				exit(9);
			}
			fprintf(verbose, "OK\n");
			free(sfx_filename);
			sfx_filename       = NULL;
		}
	}

	while (game_quit == 0)
	{
		if(readysfx == 1)
		{
			if(Mix_PlayChannel(-1, sfx, 0) == -1)
				fprintf(debug, "[warning] Mix_PlayChannel()\n");

			readysfx = 0;
		}
		else
			SDL_Delay(20);
	}
	return(0);
}
