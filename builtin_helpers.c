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
* @varname: The name of the environment variable to retrieve.
* Return: The value of the environment variable, or NULL if not found.
*/
char *_getEnvironmentVariable(const char *varname __attribute__((unused)))
{
return (getenv(varname));
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
/**
 * main - entry point for the shell program.
 * Return: 0 on success, 1 on failure.
 */
int main(void)
{
info_t info;
int status;
status = changeDirectory(&info);
if (status != 0)
{
printError("Failed to change directory");
return (1);
}
status = displayHelp(&info);
if (status != 0)
{
printError("Failed to display help");
return (1);
}
status = exitShell(&info);
if (status == -2)
{
printf("Exiting with status %d\n", atoi(info.argv[1]));
return (atoi(info.argv[1]));
}
else if (status != 0)
{
printError("Failed to exit shell");
return (1);
}
return (0);
}
