#include "shell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
/**
* exitShell - Exits the shell with a specified status.
* @info: Structure containing potential arguments.
* Return: Exits the shell with a specified status, or 0 if no
* status provided.
*/
int exitShell(info_t *info)
{
if (info->argc > 1)
{
char *endptr;
strtol(info->argv[1], &endptr, 10);
if (*endptr != '\0')
{
printError("Illegal number : ");
printf("%s\n", info->argv[1]);
return (1);
}
return (-2);
}
return (0);
}
/**
* changeDirectory - Changes the current directory of the process.
* @info: pointer
* Return: Always 0.
*/
int changeDirectory(info_t *info)
{
char *currentDir, *newDir;
char buffer[1024];
int chdirResult;
currentDir = getcwd(buffer, 1024);
if (!currentDir)
{
perror("Error: Unable to get current directory");
return (1);
}
if (info->argc > 1)
{
newDir = info->argv[1];
chdirResult = chdir(newDir);
if (chdirResult == -1)
{
perror("Can't change to directory");
printf("%s\n", newDir);
return (1);
}
_setEnvironmentVariable("OLDPWD", currentDir, 1);
_setEnvironmentVariable("PWD", getcwd(buffer, sizeof(buffer)), 1);
}
else
{
newDir = _getEnvironmentVariable("HOME");
chdirResult = chdir(newDir);
if (chdirResult == -1)
{
perror("Can't change to directory");
printf("%s\n", newDir);
return (1);
}
_setEnvironmentVariable("OLDPWD", currentDir, 1);
_setEnvironmentVariable("PWD", getcwd(buffer, sizeof(buffer)), 1);
}
return (0);
}
/**
* displayHelp - Displays help information.
* @info: Structure containing potential arguments.
* Return: Always 0.
*/
int displayHelp(info_t *info)
{
char **arguments = info->argv;
int i;
printf("Help command is functional, but not yet implemented.\n");
if (arguments)
{
for (i = 0; arguments[i] != NULL; i++)
{
printf("%s\n", arguments[i]);
}
}
return (0);
}
