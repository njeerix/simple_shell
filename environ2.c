#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
* modifyEnvironmentVariable - Modify an environment variable.
* @value: the variable
* @name: The name of the enironment variable.
*/
void modifyEnvironmentVariable(const char *name, const char *value)
{
if (_getEnvironmentVariable(name) != NULL)
{
_setEnvironmentVariable(name, value, 1);
}
else
{
}
}
/**
* removeEnvironmentVariable - Remove an environment variable.
* @name: The name of the environment variable to remove.
*/
void removeEnvironmentVariable(const char *name)
{
unsetenv(name);
}
/**
 * _getEnvironmentVariable - get the value of an environment variable.
 * @varname: the name of the environment variable to retrieve.
 * Return: the value of the environment variable, or NULL if not found.
 */
char *_getEnvironmentVariable(const char *varname)
{
return (getenv(varname));
}
/**
 * _setEnvironmentVariable - set or modify an environment variable.
 * @name: the name of the environment variable to set/modify.
 * @value: the value to assign to the environment variable.
 * @overwrite: if non-zero, overwrite an existing variable.
 * Return: 0 on success, -1 on failure.
 */
int _setEnvironmentVariable(const char *name, const char *value, int overwrite)
{
if (setenv(name, value, overwrite) == -1)
{
perror("setenv");
return (-1);
}
return (0);
}
/**
 * main - entry point for the shell program.
 * @void: No parameters.
 * Return: 0 on success, non-zero on failure.
 */
int main(void)
{
info_t myInfo;
myInfo.env = NULL;
populateEnvironmentList(&myInfo);
displayEnvironment(&myInfo);
modifyEnvironmentVariable("MY_VARIABLE", "new_value");
removeEnvironmentVariable("MY_VARIABLE");
setEnvironmentVariable(&myInfo);
unsetEnvironmentVariable(&myInfo);
free(myInfo.env);
return (0);
}
