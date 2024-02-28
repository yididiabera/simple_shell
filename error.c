#include "header.h"

/**
 * errorI - renders error msg and exits the program
 * @direc: represents path of the directory
 * @npe: path of the file that causes an error
 * @msg: shows the error message
 *
 * Return: void
 */

void errorI(const char *direc, const char *npe, const char *msg)
{
	dprintf(2, "%s: You can't access '%s': %s\n", direc, npe, msg);
	exit(EXIT_FAILURE);
}
