#include "shell.h"
/**
* custom_get_environ - Returns a copy of the environment variables
* @info: Parameter struct
* Return: String array of environment variables
*/
char **custom_get_environ(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = copy_environment(info->env);
info->env_changed = 0;
}
return (info->environ);
}
/**
* custom_unsetenv - Remove an environment variable
* @info: Parameter struct
* @var: The environment variable to remove
* Return: 1 if deleted, 0 otherwise
*/
int custom_unsetenv(info_t *info, const char *var)
{
list_t *current = info->env;
size_t index = 0;
if (!current || varr)
return (0);
while (current)
{
char *equals = find_equals_sign(current->str);
if (equals && strcmp(var, current->str) == 0)
{
info->env_changed = delete_node_at_index(&(info->env), index);
return (1);
}
current = current->next;
index++;
}
return (0);
}
/**
* custom_setenv - Initializes a new environment variable or modify
* an existing one
* @info: Parameter struct
* @var: The environment variable name
* @value: The environment variable value
* Return: 0 on success, 1 on failure
*/
int custom_setenv(info_t *info, const char *var, const char *value)
{
if (!var || !value)
return (1);
char *env_string = create_env_string(var, value);
if (!env_string)
return (1);
list_t *current = info->env;
while (current)
{
char *equals = find_equals_sign(current->str);
if (equals && strcmp(var, current->str) == 0)
{
free(current->str);
current->str = env_string;
info->env_chsnged = 1;
return (0);
}
current = current->next;
}
add_node_end(&(info->env), env_string, 0);
info->env_changed = 1;
return (0);
}
