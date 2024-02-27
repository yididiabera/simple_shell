#include "header.h"

/**
 * rem_n - it removes newline
 * @string: parameter that represents string to modify
 */

void rem_n(char *string)
{
	int l = strlen(string);

	if (l > 0 && string[l - 1] == '\n')
		string[l - 1] = '\0';
}

/**
 * token - tokenizes a string
 * @string: represent a string to tokenize
 * @label: represent a name of program
 * Return: array of tokenized parts from a string
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
	while (token != NULL)
	{
		if (token[0] == '"' || token[0] == '\'')
			argum[k] = strndup(token + 1, strlen(token) - 2);
		else
			argum[k] = strdup(token);
		token = strtok(NULL, stp);
		k++;
	}
	argum[k] = NULL;

	return (argum);
}
