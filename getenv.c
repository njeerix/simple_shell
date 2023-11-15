#include "shell.h"
#include "node.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
* custom_get_environ - Returns a copy of the environment variables
* @info: Parameter struct
* Return: String array of environment variables
*/
char **custom_get_environ(info_t *info)
{
if (!info->environ)
{
info->environ = copy_environment(environ);
}
return (info->environ);
}
/**
* custom_unsetenv - Remove an environment variable
* @info: Parameter struct
* @name: The environment variable to remove
* Return: 1 if deleted, 0 otherwise
*/
int custom_unsetenv(info_t *info, const char *name)
{
char **current = info->env;
int index = 0;
while (current[index] != NULL)
{
if (strcmp(current[index], name) == 0)
{
if (delete_node_at_index(&(info->env), index) == 0)
{
return (0);
}
else
{
return (-1);
}
}
index++;
}
return (-1);
}
/**
* custom_setenv - Initializes a new environment variable or modify
* an existing one
* @info: Parameter struct
* Return: 0 on success, 1 on failure
*/
int custom_setenv(info_t *info)
{
char *env_string, *var, *value, *equals;
list_t *current;
if (info->argc < 3)
{
printError("Usage: setenv VARIABLE VALUE\n");
return (1);
}
var = info->argv[1];
value = info->argv[2];
current = info->env;
while (current != NULL)
{
equals = find_equals_sign(current->str);
if (equals != NULL && strncmp(current->str, var, equals - current->str) == 0)
{
free(current->str);
current->str = create_env_string(var, value);
return (0);
}
current = current->next;
}
env_string = create_env_string(var, value);
add_node_end(&(info->env), env_string, 0);
return (0);
}
/**
 * copy_environment - copy an array of strings.
 * @env: the array of strings to copy.
 * Return: A new copy of the array of strings.
 */
char **copy_environment(char **env)
{
int count;
int i;
char **copy;
int len;
int j;
if (env == NULL)
return (NULL);
for (count = 0; env[count] != NULL; count++);
copy = malloc((count + 1) * sizeof(char *));
if (copy == NULL)
return (NULL);
for (i = 0; i < count; i++)
{
len = strlen(env[i]) + 1;
copy[i] = malloc(len);
if (copy[i] == NULL)
{
for (j = 0; j < i; j++)
free(copy[j]);
free(copy);
return (NULL);
}
strcpy(copy[i], env[i]);
}
copy[count] = NULL;
return (copy);
}
/**
 * delete_node_at_index - Deletes the node at a given index in a linked list
 * @list: A pointer to the head of the linked list
 * @index: The index of the node to delete
 * Return: 1 on success, -1 on failure
 */
int delete_node_at_index(list_t **list, unsigned int index)
{
char *current = *list;
list_t *temp;
unsigned int i = 0;
if (list == NULL || *list == NULL || index < 0)
return (-1);
if (index == 0)
{
*list = current->next;
free(current->str);
free(current);
return (1);
}
for (i = 0; i < index - 1 && current != NULL; i++)
{
current = current->next;
}
if (current == NULL || current->next == NULL)
return (-1);
temp = current->next;
current->next = temp->next;
free(temp->str);
free(temp);
return (1);
}
/**
 * main - entry point
 * return: 0 always
 */
int main(void)
{
int i;
int result;
Node *head = malloc(sizeof(Node));
head->str = strdup("Node 0");
head->next = NULL;
Node *current = head;
for (i = 1; i < 5; i++)
{
current->next = malloc(sizeof(Node));
current = current->next;
asprintf(&(current->str), "Node %d", i);
current->next = NULL'
}
printf("Original list:\n");
current = head;
while (current != NULL)
{
printf("%s\n", current->str);
current = current->next;
}
result = delete_node_at_index(&head, 2);
if (result == 1)
{
printf("\nNode at index 2 deleted successfully:\n");
current = head;
while (current != NULL)
{
printf("%s\n", current->str);
current = current->next;
}
}
else
{
printf("\nFailed to delete node at index 2.\n");
}
current = head;
while (current != NULL)
{
Node *temp = current;
current = current->next;
free(temp->str);
free(temp);
}
return (0);
}
/**
 * create_env_string - create an environment variable string.
 * @var: the variable name.
 * @value: the value of the variable.
 * Return: A dynamically allocated string in the form "VAR=VALUE".
 */
char *create_env_string(const char *var, const char *value)
{
char *env_string;
size_t len_var = strlen(var);
size_t len_value = strlen(value);
env_string = malloc(len_var + len_value + 2);
if (env_string == NULL)
{
perror("Memory allocation error");
exit(EXIT_FAILURE);
}
snprintf(env_string, len_var + len_value + 2, "%s=%s", var, value);
return (env_string);
}
/**
 * add_node_end - add a node to the end of a linked list.
 * @head: Apointer to the head of the linked list.
 * @str: the string to be stored in the new node.
 * @overwrite: if 1, overwrite the existing node if the same string exists.
 */
void add_node_end(list_t **head, char *str, int overwrite)
{
list_t *new_node, *current;
if (*head == NULL)
{
*head = malloc(sizeof(list_t));
if (*head == NULL)
{
perror("Memory allocation error");
exit(EXIT_FAILURE);
}
(*head)->str = strdup(str);
(*head)->next = NULL;
return;
}
current = *head;
while (current->next != NULL)
{
if (overwrite && strcmp(current->str, str) == 0)
{
free(current->str);
current->str = strdup(str);
return;
}
current = current->next;
}
new_node = malloc(sizeof(list_t));
if (new_node == NULL)
{
perror("Memory allocation error");
exit(EXIT_FAILURE);
}
new_node->str = strdup(str);
new_node->next = NULL;
current->next = new_node;
}
