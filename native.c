#include "header.h"

/**
 * checking_exit - it handles the exit for the cmd that is builtin
 * @cmdx: represents an entered command
 * @bufs: specifies the buffer used for input
 * @stts: indicates status of the exit
 *
 * return: void
 */

void checking_exit(char **cmdx, char *bufs, int *stts)
{
	char *ex_cmdx = "exit";

	if (strcmp(cmdx[0], ex_cmdx) == 0)
	{
		int exit_status = *stts;

		if (cmdx[1] != NULL)
		{
			exit_status = atoi(cmdx[1]);
		}

		free(bufs);
		f_array(cmdx);

		exit(exit_status);
	}
}

/**
 * environment_c - processes the "env" built-in command.
 *@cmdx: represent user input
 *
 *Return: 0 on success, 1 else
 */

int environment_c(char *cmdx)
{
	char *env = "env";

	if (strcmp(cmdx, env) == 0)
	{
		int x = 0;

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
