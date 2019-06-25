#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "pong.h"

char * dirproc(const char *dirname)
{
	char    pwd[1024];
	char   *dirwd                 = NULL;
	DIR    *dir_cwd               = NULL;
	size_t  count                 = 0;

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		fprintf(debug, "[debug]  Current directory is: '%s'\n", pwd);

		count                     = strlen(pwd) + strlen(dirname);
		dirwd                     = (char *) malloc (sizeof(char) * count);
		if (dirwd                == NULL)
		{
			fprintf(stderr, "[error] malloc()\n");
			exit(3);
		}

		sprintf(dirwd, "%s/%s", pwd, dirname);
		dir_cwd                   = opendir(dirwd);
		if (dir_cwd              == NULL)
		{
			free(dirwd);

			count                 = strlen(pwd)+strlen("/../")+strlen(dirname);
			dirwd                 = (char *) malloc (sizeof(char) * count);
			if (dirwd            == NULL)
			{
				fprintf(stderr, "[error] malloc()\n");
				exit(4);
			}

			sprintf(dirwd, "%s/../%s", pwd, dirname);
			dir_cwd               = opendir(dirwd);
			if (dir_cwd          == NULL)
			{
				fprintf(stderr, "[error] Unable to locate game image assets\n");
				exit(5);
			}
			else
				closedir(dir_cwd);
		}
		else
			closedir(dir_cwd);
	}
	else
	{
		fprintf(stderr, "[error] getcwd()\n");
		exit(6);
	}

	return (dirwd);
}
