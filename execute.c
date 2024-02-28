#include "header.h"

/**
* errorII - render error msg and exits the program
* @label: represents a program label
* @dash: reprsent which number is a line
* @cmdx: reprsent an error message of a command
* @msg: renders a messag of an error
* @react: shows whether it is interactive mode or not
*
* Return: void
*/

void errorII(const char *label, const int dash,
			 char *cmdx, const char *msg, const int react)
{
	fprintf(stderr, "%s: %d: %s: %s\n", label, dash, cmdx, msg);

	if (cmdx != NULL)
	{
		free(cmdx);
		cmdx = NULL;
	}

	if (!react)
		exit(127);
}

/**
* f_array - dellocates a memory used by string array
* @array: represents pointer to a string array
*/

void f_array(char **array)
{
	int i = 0;

	if (array == NULL)
	{
		return;
	}

	for (i = 0; array[i] != NULL; i++)
	{
		free(array[i]);
	}

	free(array);
}

/**
* acc_cmd - it reads the command from the standard input
* @label: represent program label
* @dash: indicates which number is the line
*
* Return: string from stdiin or null accordingly
*/

char *acc_cmd(char *label, int dash)
{
	char *bufs = NULL;

	size_t bufs_s = 0;

	int getline_result = getline(&bufs, &bufs_s, stdin);

	if (getline_result == -1)
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
* excuter - it runs the command
* @argum: reprsents an array of the program arguments
* @bufs: reprsent an input buffer
* @paz: reprsent which path is an executable
* @label: reprsent a name of the program
* @dash: represent which line is a command
*
* Return: Exit status
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
*
* return: void
*/

void prmt(const int react)
{
	if (!react)
	{
		return;
	}
	printf("$ ");
	fflush(stdout);
}
