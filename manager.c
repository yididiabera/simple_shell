#include "header.h"

/**
 * p_of_token - tokenizes the rd directories
 * @rd: represent the path variable
 * @label: reprsent the name of program
 * Return: array of directories in path
 */

char **p_of_token(char *rd, char *label)
{
	int j = 0;
	char **directory = NULL;
	char stp[] = ":";
	char *tkn;

	directory = malloc(64 * sizeof(char *));
	if (directory == NULL)
		errorII(label, 0, NULL, NULL, isatty(fileno(stdin)));
	tkn = strtok(rd, stp);
	while (tkn != NULL)
	{
		directory[j] = strdup(tkn);
		tkn = strtok(NULL, stp);
		j++;
	}
	directory[j] = NULL;
	return (directory);
}

/**
 * path_p - it parses the variable of the path
 * @label: reprsent a name of the program
 * Return: an array that contains the directories in path
 */

char **path_p(char *label)
{
	char *rd = NULL;
	char *cpy_p;
	char **directory;

	rd = getenv("PATH");
	if (rd == NULL)
		return (NULL);
	cpy_p = strdup(rd);
	directory = p_of_token(cpy_p, label);
	free(cpy_p);

	return (directory);
}

/**
 * path_handler - it handles path
 * @argum: reprsent an array that is executable
 * @bufs: reprsent an input command
 * @label: reprsent a program name
 * @dash: reprsent a command line number
 * Return: the full path of the executable
 */

char *path_handler(char **argum, char *bufs, char *label, int dash)
{
	int j;
	char *fr = "/", **albm = path_p(label), *paz = NULL;

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
 * excutablty_c - it checks if a path is executable or not
 * @rd: reprsent a path to the file
 * Return: 0 or 1
 */

int excutablty_c(char *rd)
{
	if (access(rd, X_OK) == 0)
	{
		struct stat stts;

		if (stat(rd, &stts) == 0)
		{
			if (S_ISREG(stts.st_mode))
				return (0);
		}
	}

	return (1);
}
