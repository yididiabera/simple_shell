#include "header.h"

/**
 * errorII - handles errors
 *@label: program label
 * @dash: indicate line number
 * @cmdx: command which has an error
 * @msg: renders an error msg
 * @react: shows it is interactive mode or not
 *
 * Return: error code
 */

void errorII(char *label, int dash, char *cmdx, char *msg, int react)
{
	dprintf(STDERR_FILENO, "%s: %d: %s: %s\n", label, dash, cmdx, msg);
	free(cmdx);
	if (!react)
		exit(127);
}

/**
 * f_array - it frees an array of strings
 * @array: represents an array of strings
 */

void f_array(char **array)
{
	int i = 0;

	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}

	free(array);
}

/**
 * acc_cmd - it accepts the cmdx from the standard error
 * @label: label of program
 * @dash: line number
 *
 * Return: 0 or -1 accordingly
 */

char *acc_cmd(char *label, int dash)
{
	char *bufs = NULL;
	size_t bufs_s = 0;

	if (getline(&bufs, &bufs_s, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(bufs);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(bufs);
			errorII(label, dash, NULL, NULL, isatty(fileno(stdin)));
		}
	}
	rem_n(bufs);

	return (bufs);
}

/**
 * excuter - it executes the command
 * @argum: reprsents an arguments of the program
 * @bufs: reprsent an input buffer
 * @paz: reprsent a path of the executable
 * @label: reprsent a label of the program
 * @dash: represent a command number
 *
 * Return: exit status
 */

int excuter(char **argum, char *bufs, char *paz, char *label, int dash)
{
	char msg[] = "No such file or directory", rd[] = "/bin/ls";
	int stat;
	pid_t prntid;

	(void)dash;
	if (excutablty_c(argum[0]) != 0)
	{
		if (argum != NULL)
			f_array(argum);
		if (paz != NULL)
			free(paz);
		if (bufs != NULL)
			free(bufs);
		errorI(rd, "/test_hbtn", msg);
		return (2);
	}
	prntid = fork();
	if (prntid == -1)
	{
		free(bufs);
		if (paz != NULL)
			free(paz);
		f_array(argum);
		errorII(label, 0, NULL, NULL, isatty(fileno(stdin)));
	}
	if (prntid == 0)
	{
		execve(argum[0], argum, environ);
	}
	else
	{
		wait(&stat);
		if (argum != NULL)
			f_array(argum);
		if (paz != NULL)
			free(paz);
		if (bufs != NULL)
			free(bufs);
	}
	return (0);
}

/**
 * prmt - it shows prompt
 * @react: make sure whether the mode is interactive or not
 */

void prmt(int react)
{
	if (react)
	{
		printf("$ ");
		fflush(stdout);
	}
}