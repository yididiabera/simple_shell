#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

void errorI(const char *direc, const char *npe, const char *msg);

void errorII(const char *label, const int dash, char *cmdx, const char *msg, const int intreact);

void rem_n(char *string);

char **token(char *string, char *label);

void f_array(char **array);

char *acc_cmd(char *label, int dash);

int excuter(char **argum, char *bufs, char *paz, char *label, int dash);

void prmt(const int react);

char *path_handler(char **argum, char *bufs, char *label, const int dash);

void checking_exit(char **cmdx, char *bufs, int *stat);

int environment_c(char *cmdx);

char **path_p(char *label);

char **p_of_token(char *rd, char *label);

int excutablty_c(char *rd);

ssize_t _fetchline(char **dashp, size_t *bufs_s, FILE *iomngr);

char *_stk(char *string, const char *separator);
#endif
