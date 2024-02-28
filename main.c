#include "header.h"

/**
 * main - Entry point of the shell
 * @argc: reprsents a number of an arguments
 * @argv: indicates an array containing command-line arguments
 *
 * Return: Always 0(Success)
 */

int main(int argc, char **argv)
{
	char *bufs = NULL, *paz = NULL;
	char **argum = NULL;
	int dash = 0, stat = 0;
	int react = isatty(fileno(stdin));
	(void)argc;
	while (1)
	{
		dash++;
		prmt(react);
		bufs = acc_cmd(argv[0], dash);
		if (strspn(bufs, "/"))
		{
			argum = token(bufs, argv[0]);
			if (excuter(argum, bufs, NULL, argv[0], dash) == 2)
				stat = 2;
			continue;
		}
		if (environment_c(bufs) == 0)
			continue;
		if (bufs[0] == '\0' || strspn(bufs, " ") == strlen(bufs))
		{
			free(bufs);
			continue;
		}
		argum = token(bufs, argv[0]);
		checking_exit(argum, bufs, &stat);
		paz = path_handler(argum, bufs, argv[0], dash);
		if (paz == NULL)
			continue;
		if (strcmp(argum[0], paz) != 0)
		{
			free(argum[0]);
			argum[0] = strdup(paz);
			excuter(argum, bufs, paz, argv[0], dash);
		}
		else
			excuter(argum, bufs, NULL, argv[0], dash);
	}
	return (0);
}
