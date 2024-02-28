#include "header.h"

/**
 * rem_n - eliminate trailing newline
 * @string: it is a parameter that represents string to modify
 *
 * return: void
 */

void rem_n(char *string)
{
	int l = strlen(string);

	if (l > 0 && string[l - 1] == '\n')
	{
		string[l - 1] = '\0';
	}
}

/**
 * token - tokenizes a string
 * @string: represent a text literal to be tokenized
 * @label: represents program label
 *
 * Return: list of parsed elements
 */

char **token(char *string, char *label)
{
	int k = 0;
	char **argum = NULL;
	char *token;
	char stp[] = " \t\n\r";

	argum = malloc(64 * sizeof(char *));
	if (argum == NULL)
	{
		errorII(label, 0, NULL, NULL, isatty(fileno(stdin)));
	}

	token = strtok(string, stp);
	while (token != NULL && k < 64)
	{
		if (token[0] == '"' || token[0] == '\'')
		{
			argum[k] = strndup(token + 1, strlen(token) - 2);
		}
		else
		{
			argum[k] = strdup(token);
		}
		token = strtok(NULL, stp);
		k++;
	}

	argum[k] = NULL;

	return (argum);
}
