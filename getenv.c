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
char ***current = &(info->env);
int index = 0;
while ((*current)[index] != NULL)
{
if (strcmp((*current)[index], name) == 0)
{
if (delete_node_at_index((Node **)&(info->env), index) == 1)
{
return (1);
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
current = *(list_t **)info->env;
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
add_node_end((list_t **)&(info->env), env_string, 0);
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
int delete_node_at_index(Node **list, int index)
{
Node *current = *list;
Node *temp = NULL;
int i;
if (*list == NULL || index < 0)
{
return (-1);
}
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
{
return (-1);
}
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
int len;
Node *current;
int result;
Node *head = malloc(sizeof(Node));
head->str = strdup("Node 0");
head->next = NULL;
current = head;
for (i = 1; i < 5; i++)
{
current->next = malloc(sizeof(Node));
current = current->next;
if (snprintf(NULL, 0, "Node %d", i) >= 0)
{
len = snprintf(NULL, 0, "Node %d", i) + 1;
current->str = malloc(len);
snprintf(current->str, len, "Node %d", i);
}
else
{
perror("Memory allocation error");
exit(EXIT_FAILURE);
}
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
printf("\nNode at index 2 delete successfully:\n");
current = head;
while (current != NULL)
{
printf("%s\n", current->str);
current = current->next;
}
}
else
{
printf("\nFailed to delete node at index 2,\n");
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
/**
 * find_equals_sign - find the position of the equals sign in a string.
 * @str: the string to search.
 * Return: a pointer to the first occurrence of the equals sign, or NULL if not found.
 */
char *find_equals_sign(const char *str)
{
int index = 0;
while (str[index] != '\0')
{
if (str[index] == '=')
return ((char *)&str[index]);
index++;
}
return (NULL);
}
/**
 * create_new_string - creates an environment variable string
 * @var: the variable name.
 * @value: the value of the variable.
 * Return: a dynamically allocated string in the form "VAR=VALUE".
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
 * printfError - print error message to standard error
 * @msg: the error message to print
 */
void printError(const char *msg)
{
if (msg != NULL)
{
fprintf(stderr, "Error: %s\n", msg);
}
else
{
fprintf(stderr, "An error occurred\n");
}
}
