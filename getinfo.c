#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "node.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
for (i = 0; info->argv && info->argv[i] != NULL; i++);
info->argc = i;
replace_aliases(info);
replaces_variable(info);
}
}
/**
* release_info - frees the fields of the info_t struct
* @info: pointer to the info_t struct
*/
void release_info(info_t *info, int free_all)
{
if (info == NULL)
return;
free_linked_list((struct Node **)&(info->aliases));
free_linked_list((struct Node **)&(info->variables));
if (info->environment)
{
free_linked_list((struct Node **)&(info->environment));
}
free_linked_list((struct Node **)&(info->history));
free_string_array(info->argv);
info->argv = NULL;
info->path = NULL;
if (free_all)
{
if (!info->command_buffer)
free(info->arg);
if (info->command_history)
free_linked_list(&(info->command_history));
if (info->aliases)
free_linked_list((struct Node **)&(info->aliases));
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
char *token = strtok(input, delimiter);
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
 * free_linked_list - frees a linked list.
 * @head_ref: pointer to the head of the linked list
 */
void free_linked_list(struct Node **head_ref)
{
struct Node *current = *head_ref;
struct Node *next;
while (current != NULL)
{
next = current->next;
free(current);
current = next;
}
*head_ref = NULL;
}
/**
 * free_string_array - frees an array of strings.
 * @array: array of strings to be freed.
 */
void free_string_array(char **array)
{
int i;
if (array == NULL)
return;
for (i = 0; array[i] != NULL; i++)
{
free(array[i]);
}
free(array);
}
/**
 * free_info - frees the allocated memory in the info_t struct.
 * @info: pointer to the info_t struct.
 */
void free_info(info_t *info)
{
if (info == NULL)
return;
free_linked_list((struct Node **)&(info->aliases));
free_linked_list((struct Node **)&(info->variables));
if (info->environment)
{
free_linked_list((struct Node **)&(info->environment));
}
free_linked_list((struct Node **)&(info->history));
free_string_array(info->argv);
if (info->arg)
free(info->arg);
if (info->command_history)
free_linked_list(&(info->command_history));
if (info->aliases)
free_string_array(info->aliases);
free_string_array(info->environ);
free_command_buffer(info);
}
/**
 * init_info - initializes the info_t struct with environment and arguments.
 * @info: pointer to the info_t struct.
 * @env: environment vriables.
 * @argv: argument vector.
 */
void init_info(info_t *info, char **env, char **argv)
{
if (info == NULL)
return;
initialize_info(info);
if (env)
info->environ = duplicate_string_array(env);
if (argv && argv[0])
info->arg = duplicate_string(argv[0]);
}
/**
 * execute_command - executes a command.
 * @arg_vector: array of arguments fo the command.
 * Return: exit status of the command.
 */
int execute_command(char **arg_vector)
{
pid_t pid, wpid;
int status;
pid = fork();
if (pid == -1)
{
perror("fork");
return (-1);
}
else if (pid == 0)
{
if (execvp(arg_vector[0], arg_vector) == -1)
{
perror("execvp");
exit(EXIT_FAILURE);
}
}
else
{
do
{
wpid = waitpid(pid, &status, WUNTRACED);
if (wpid == -1)
{
perror("waitpid");
return (-1);
}
}
while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
return (WEXITSTATUS(status));
}
/**
 * duplicate_string_array - duplicates an array of strings.
 * @arr: the array of strings to duplicate.
 * Return: a duplicated array of strings or NULL on failure.
 */
char **duplicate_string_array(char **arr)
{
int size = 0;
int i, j;
char **duplicate;
if (arr == NULL)
{
return (NULL);
}
while (arr[size] != NULL)
{
size++;
}
duplicate = (char **)malloc((size + 1) * sizeof(char *));
if (duplicate == NULL)
{
return (NULL);
}
for (i = 0; i < size; i++)
{
duplicate[i] = duplicate_string(arr[i]);
if (duplicate[i] == NULL)
{
for (j = 0; j < i; j++)
{
free(duplicate[j]);
}
free(duplicate);
return (NULL);
}
}
duplicate[size] = NULL;
return (duplicate);
}
/**
 * free_command_buffer - frees the command buffer in the info_t struct.
 * @info: pointer to the info_t struct
 */
void free_command_buffer(info_t *info)
{
if (info->command_buffer)
{
free(info->command_buffer);
info->command_buffer = NULL;
}
}
/**
 * _strlen - calculates the length of string.
 * @str: string to calculate the length o
 * Return: length of the string
 */
int _strlen(const char *str)
{
int len = 0;
while (str[len] != '\0')
{
len++;
}
return (len);
}
/**
 * duplicate_string - duplicates a string.
 * @str: the string to duplicate.
 * Return: a duplicate string.
 */
char *duplicate_string(const char *str)
{
char *duplicate = NULL;
int length;
if (str == NULL)
return (NULL);
length = _strlen(str);
duplicate = (char *)malloc(length + 1);
if (duplicate == NULL)
return (NULL);
strcpy(duplicate, str);
return (strdup(str));
}
/**
 * main - entry point
 * Return: always 0
 */
int main(void)
{
int exit_status;
info_t info;
init_info(&info, NULL, NULL);
info.arg = "your_command_here";
configure_info(&info, NULL);
exit_status = execute_command(info.argv);
printf("Command exited with status: %d\n", exit_status);
release_info(&info, 1);
return (exit_status);
}
/**
 * replace_aliases - placeholder function to replace aliases in command arguments.
 * @info: pointer to the info_t struct
 */
void replace_aliases(info_t *info)
{
int i;
char **new_argv;
char *replacement;
if (info == NULL || info->argv == NULL)
return;
new_argv = NULL;
for (i = 0; info->argv[i] != NULL; i++)
{
if (strcmp(info->argv[i], "alias1") == 0)
{
replacement = "replacement1";
new_argv[i] = strdup(replacement);
}
else
{
new_argv[i] = strdup(info->argv[i]);
}
}
new_argv[info->argc] = NULL;
free_string_array(info->argv);
info->argv = new_argv;
}
/**
 * replaces_variable - placeholder function to replace variables in command arguments
 * @info: pointer to the info_t struct
 */
void replaces_variable(info_t *info)
{
char **new_argv;
int i;
char *replacement;
if (info == NULL || info->argv == NULL)
return;
new_argv = NULL;
for (i = 0; info->argv[i] != NULL; i++)
{
if (strcmp(info->argv[i], "$VAR") == 0)
{
replacement = "value";
new_argv[i] = strdup(replacement);
}
else
{
new_argv[i] = strdup(info->argv[i]);
}
}
new_argv[info->argc] = NULL;
free_string_array(info->argv);
info->argv = new_argv;
}
