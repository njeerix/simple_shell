#include <string.h>
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
* exitShell - Exits the shell with a specified status.
* @info: Structure containing potential arguments.
* Return: Exits the shell with a specified status, or 0 if no
* status provided.
*/
int exitShell(info_t *info)
{
int exitStatus = 0;
if (info->argc > 1)
{
exitStatus = atoi(info->argv[1]);
if (exitStatus == 0 && info->argv[1][0] != '0')
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
* @info: Structure containing potential arguments.
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
printf("Error: Unable to get current directory.\n");
return (1);
}
if (info->argc > 1)
{
newDir = info->argv[1];
chdirResult = chdir(newDir);
if (chdirResult == -1)
{
printError("Can't change to directory : ");
printf("%s\n", newDir);
return (1);
}
_setEnvironmentVariable("OLDPWD", _getEnvironmentVariable("PWD"), 1);
_setEnvironmentVariable("PWD", getcwd(buffer, sizeof(buffer)), 1);
}
else
{
newDir = _getEnvironmentVariable("HOME=");
chdirResult = chdir(newDir);
if (chdirResult == -1)
{
printError("Can't change to directory : ");
printf("%s\n", newDir);
return (1);
}
_setEnvironmentVariable("OLDPWD", _getEnvironmentVariable("PWD"), 1);
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
