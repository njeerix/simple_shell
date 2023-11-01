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
