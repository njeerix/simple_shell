#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
/**
* displayEnvironment - Prints the current environment.
* @info: Structure containing potential arguments.
* Return: Always 0.
*/
void displayEnvironment(info_t *info)
{
char **env = info->env;
int i = 0;
while (env[i] != NULL)
{
printf("%s\n", env[i]);
i++;
}
}
/**
* findEnvironmentVariable - Finds the value of an environment variable.
* @info: Structure containing potential arguments.
* @name: The name of the environment variable, or NULL if not found.
* Return: NULL if not found
*/
char *findEnvironmentVariable(info_t *info, const char *name)
{
char **env = info->env;
int i = 0;
while (env[i] != NULL)
{
if (strcmp(env[i], name) == 0)
{
return (env[i]);
}
i++;
}
return (NULL);
}
/**
* setEnvironmentVariable - Sets or modifies an environment variable.
* @info: Structure containing potential arguments.
* Return: Always 0.
*/
int setEnvironmentVariable(info_t *info)
{
if (info->argc != 3)
{
printf("Usage: setenv <variable> <value>\n");
return (1);
}
(void)modifyEnvironmentVariable(info->argv[1], info->argv[2]);
return (0);
}
/**
* unsetEnvironmentVariable - Removes an environment variable.
* @info: Strcture containing potential arguments.
* Return: Always 0 on success, 1 on failure.
*/
int unsetEnvironmentVariable(info_t *info)
{
int i;
int success = 0;
if (info->argc == 1)
{
printf("Usage: unsetenv <variable> [variable...]\n");
return (1);
}
for (i = 1; i < info->argc; i++)
{
(void)removeEnvironmentVariable(info->argv[i]);
success = 1;
}
return (success);
}
/**
* populateEnvironmentList - Populates the environment linked list.
* @info: Structure containing potential arguments.
* Return: Always 0.
*/
void populateEnvironmentList(info_t *info)
{
char **env = environ;
int count = 0;
int i = 0;
while (env[count] != NULL)
{
count++;
}
info->env = (char **)malloc((count + 1) * sizeof(char *));
if (info->env == NULL)
{
fprintf(stderr, "Memory allocation failed for env\n");
exit(1);
}
while (env[i] != NULL)
{
info->env[i] = strdup(env[i]);
i++;
}
info->env[count] = NULL;
}
