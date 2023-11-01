#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
* initialize_info - Initializes the info_t struct
* @info: Pointer to the info_t struct
*/
void initialize_info(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}
/**
* configure_info - Configures the info_t struct
* @info: Pointer to the info_t struct
* @av: Argument vector
*/
void configure_info(info_t *info, char **av)
{
int i = 0;
info->executable_name = av[0];
if (info->arg)
{
info->argv = split_arguments(info->arg, " \t");
if (!info->argv)
{
info->argv = (char **)malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = duplicate_string(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv && info->argv[i]; i++);
info->argc = i;
replace_aliases(info);
replaces_variables(info);
}
}
/**
* release_info - frees the fields of the info_t struct
* @info: pointer to the info_t struct
* @free_all: true if all fields should be freed
*/
void release_info(info_t *info, int free_all)
{
free_string_array(info->argv);
info->argv = NULL;
info->path = NULL;
if (free_all)
{
if (!info->command_buffer)
free(info->arg);
if (info->environment)
free_linked_list(&(info->enironment));
if (info->command_history)
free_linked_list(&(info->command_history));
if (info->aliases)
free_linked_list(&(info->aliases));
free_string_array(info->environ);
info->environ = NULL;
free_command_buffer(info);
}
}
/**
* split_arguments - splits a string into an array of tokens using a delimiter.
* @input: the string to split
* @delimiter: the delimiter used for splitting.
* Return: an array of tokens.
*/
char **split_arguments(char *input, const char *delimiter)
{
char **tokens = NULL;
char *tokens = strtok(input, delimiter);
int token_count = 0;
while (token != NULL)
{
tokens = (char **)realloc(tokens, (token_count + 1) * sizeof(char *));
if (tokens == NULL)
{
return (NULL);
}
tokens[token_count] = strdup(token);
token = strtok(NULL, delimiter);
token_count++;
}
tokens = (char **)realloc(tokens, (token_count + 1) * sizeof(char *));
if (tokens == NULL)
{
return (NULL);
}
tokens[token_count] = NULL;
return (tokens);
}
/**
* duplicate_string - Duplicates a string.
* @str: the string to duplicate.
* Return: a duplicated string.
*/
char *duplicate_string(const char *str)
{
char *duplicate = NULL;
int length;
if (str == NULL)
{
return (NULL);
}
length = _strlen(str);
duplicate = (char *)malloc(length + 1);
if (duplicate == NULL)
{
return (NULL);
}
strcpy(duplicate, str);
return (duplicate);
}
