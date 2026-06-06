#ifndef ERRORM_H
#define ERRORM_H

#define ERROR_HANDLING_FILENAME       "error.txt"

int ReadLine(const char *filename, char *line, int size, int ln);
int pushError(const char *filename, const int priority, const char *msg, ...);
int printError(const char *filename);

#endif