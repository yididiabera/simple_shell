#include "header.h"

/**
 * p_of_token - tokenizes directories in a path variable.
 * @rd: represent the path variable
 * @label: reprsent the program label
 *
 * Return: array containing the directories in path
 */

char **p_of_token(char *rd, char *label)
{
	int j = 0;
	char **directory = NULL;
	char stp[] = ":";
	char *tkn;

	directory = malloc(64 * sizeof(char *));
	if (directory == NULL)
	{
		errorII(label, 0, NULL, NULL, isatty(fileno(stdin)));
	}

	tkn = strtok(rd, stp);
	while (tkn != NULL && j < 64)
	{
		directory[j] = strdup(tkn);
		if (directory[j] == NULL)
		{
			errorII(label, 0, NULL, NULL, isatty(fileno(stdin)));
		}
		tkn = strtok(NULL, stp);
		j++;
	}

	directory[j] = NULL;

	return (directory);
}

/**
 * path_p - it parses the variable of the path
 * @label: reprsent a name of the program
 *
 * Return: an array that contains the directories in path
 */

char **path_p(char *label)
{
	char *rd = getenv("PATH");
	char *cpy_p, **directory;

	if (rd == NULL)
	{
		return (NULL);
	}
	cpy_p = strdup(rd);
	if (cpy_p == NULL)
	{
		errorII(label, 0, NULL, NULL, isatty(fileno(stdin)));
		return (NULL);
	}
	directory = p_of_token(cpy_p, label);
	free(cpy_p);
	return (directory);
}

/**
 * path_handler - it manages path
 * @argum: reprsent an array that is executable
 * @bufs: reprsent an input command
 * @label: reprsent a program name
 * @dash: reprsent a command line number
 *
 * Return: executable file's path
 */

char *path_handler(char **argum, char *bufs, char *label, const int dash)
{
	int j;
	char *fr = "/";
	char **albm = path_p(label), *paz = NULL;

	if (albm == NULL)
	{
		f_array(argum);
		errorII(label, dash, bufs, "not found", isatty(fileno(stdin)));
	}
	if (excutablty_c(argum[0]) == 0)
	{
		f_array(albm);
		return (argum[0]);
	}
	j = 0;
	while (albm[j] != NULL)
	{
		paz = malloc(strlen(albm[j]) + strlen(argum[0]) + 2);
		if (paz == NULL)
		{
			perror(label);
			f_array(albm);
			return (NULL);
		}
		strcpy(paz, albm[j]);
		strcat(paz, fr);
		strcat(paz, argum[0]);
		if (excutablty_c(paz) == 0)
		{
			f_array(albm);
			return (paz);
		}
		free(paz);
		j++;
	}
	if (albm != NULL)
		f_array(albm);
	f_array(argum);
	errorII(label, dash, bufs, "not found", isatty(fileno(stdin)));
	return (NULL);
}

/**
 * excutablty_c - makes sure whether a path is executable or not
 * @rd: reprsent a path to the file
 *
 * Return: for sucess 0, 1 otherwise
 */

int excutablty_c(char *rd)
{
	if (access(rd, X_OK) == 0)
	{
		struct stat stts;

		if (stat(rd, &stts) == 0 && S_ISREG(stts.st_mode))
		{
			return (0);
		}
	}

	return (1);
}
