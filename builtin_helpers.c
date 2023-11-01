#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
/**
* printError - Print an error message to standard error.
* @message: The error ,essagge to print.
*/
void printError(const char *message)
{
fprintf(stderr, "Error: %s\n", message);
}
/**
* _getEnvironmentVariable - Get the value of an environment variable.
* @name: The name of the environment variable to retrieve.
* Return: The value of the environment variable, or NULL if not found.
*/
char *_getEnvironmentVariable(const char *name)
{
return (getenv(name));
}
/**
* _setEnvironmentVariable - Set or modify an environment variable.
* @name: The name of the environment variable to set/modify.
* @value: The value to assign to the wnvironment variable.
* @overwrite: If non-zero, overwrite an existing variable.
* Return: 0 on success, -1 on failure.
*/
int _setEnvironmentVariable(const char *name, const char *value, int overwrite)
{
if (setenv(name, value, overwrite) == -1)
{
return (-1);
}
return (0);
}
