#include "header.h"

/**
 * _fetchline - read a line of input from a stream
 * @dashp: buffer to store the line read
 * @bufs_s: size of the buffer
 * @iomngr: stream from which to read
 * Return: number of bytes read or -1
 */

ssize_t _fetchline(char **dashp, size_t *bufs_s, FILE *iomngr)
{
	char *bufs = NULL, ch;
	size_t size, x = 0;

	if (dashp == NULL || bufs_s == NULL || iomngr == NULL)
		return (-1);
	size = *bufs_s;
	if ((*dashp) == NULL || size == 0)
	{
		size = 120;
		(*dashp) = malloc(sizeof(char) * size);
		if (dashp == NULL)
			return (-1);
	}
	while ((ch = fgetc(iomngr)) != EOF && ch != '\n')
	{
		if (x == size - 1)
		{
			size *= 2;
			bufs = realloc((*dashp), size);
			if (bufs == NULL)
			{
				free(*dashp);
				*dashp = NULL;
				return (-1);
			}
			*dashp = bufs;
		}
		(*dashp)[x++] = ch;
	}
	if (x > 0 || ch == '\n')
		(*dashp)[x] = '\0';
	if (x > 0 || ch == '\n' || ch == EOF)
	{
		*bufs_s = size;
		return (x);
	}
	return (-1);
}

/**
 * _stk - tokenizes a string based on dilimiters
 * @string: string to tokenize
 * @separator: a string of delimiter characters
 * Return: a pointer to the next token or NULL
 */

char *_stk(char *string, const char *separator)
{
	static char *ptr;
	char *init = ptr;

	if (string != NULL)
		ptr = string;
	while (*ptr != '\0' && strchr(separator, *ptr) != NULL)
		ptr++;
	if (*ptr == '\0')
		return (NULL);
	init = ptr;
	while (*ptr != '\0')
	{
		if (strchr(separator, *ptr) != NULL)
		{
			*ptr = '\0';
			ptr++;
			return (init);
		}
		ptr++;
	}
	return (init);
}
