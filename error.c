#include "header.h"

/**
 * errorI - error handling
 * @direc: path
 * @npe: path of the error
 * @msg: shows error message
 */

void errorI(char *direc, char *npe, char *msg)
{
	dprintf(2, "%s: cannot access '%s': %s\n", direc, npe, msg);
	exit(2);
}
