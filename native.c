#include "header.h"

/**
 * checking_exit - handles the exit builtin
 * @cmdx: command entered
 * @bufs: input buffer
 * @stts: exit status
 */

void checking_exit(char **cmdx, char *bufs, int *stts)
{
	int stat;
	char *ex_cmdx = "exit";

	if (strcmp(cmdx[0], ex_cmdx) == 0)
	{
		if (cmdx[1] == NULL)
		{
			free(bufs);
			f_array(cmdx);
			exit(*stts);
		}
		else
		{
			stat = atoi(cmdx[1]);
			free(bufs);
			f_array(cmdx);
			exit(stat);
		}
	}
}

/**
 * environment_c - it handles the env builtin
 *@cmdx: represent entered command
 *
 *Return: 0 or 1
 */

int environment_c(char *cmdx)
{
	int x = 0;
	char *env = "env";

	if (strcmp(cmdx, env) == 0)
	{
		while (environ[x] != NULL)
		{
			printf("%s\n", environ[x]);
			x++;
		}
		free(cmdx);
		return (0);
	}
	return (1);
}
