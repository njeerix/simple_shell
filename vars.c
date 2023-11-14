#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
/**
* custom_is_chain - checks if the current character in tthe buffer is a chain
* character
* @info: The parameter struct
* @buf: the character buffer.
* @p: Address of the current position in the buffer.
* Return: 1 if it's a chain delimiter, 0 otherwise.
*/
int custom_is_chain(info_t *info, char *buf, size_t *p)
{
size_t j = *p;
size_t i = 1;
if (buf[j] == '|' && buf[j + i] == '|')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_OR;
}
if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ':')
{
buf[j] = 0;
info->cmd_buf_type = CMD_CHAIN;
}
else
{
return (0);
}
*p = j;
return (1);
}
/**
* custom_check_chain - checks whether we should continue chaining based on the
* last status.
* @info: the parameter struct.
* @buf: the character buffer
* @p:  Address of the current position in the buffer.
* @i: starting position in the buffer.
* @len: Length of the buffer.
*/
void custom_check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = len;
if (info->cmd_buf_type == CMD_AND)
{
if (info->status != 0)
{
buf[i] = 0;
j = len;
}
}
if (info->cmd_buf_type == CMD_OR)
{
if (info->status == 0)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}
/**
* custom_replaces_alias - replaces aliases in the tokenized string.
* @info: the parameter struct.
* Return: 1 if replaced, 0 otherwise.
*/
int custom_replaces_alias(info_t *info)
{
list_t *node;
char *p;
node = custom_node_starts_with(info->alias, info->argv[0], '=');
if (!node)
{
return (0);
}
free(info->argv[0]);
p = strchr(node->str, '=');
if (!p)
{
return (0);
}
p = strdup(p + 1);
if (!p)
{
return (0);
}
info->argv[0] = p;
return (1);
}
/**
* custom_replaces_vars - replces variablesin the tokenized strin.
* @info: the parameter struct.
* Return: 1 if replaced, 0 otherwise.
*/
int custom_replaces_vars(info_t *info)
{
list_t *node;
int i = 0;
list_t *info_env = custom_create_list_from_char_array(info->env);
while (info->argv[i])
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
{
i++;
continue;
}
if (strcmp(info->argv[i], "$?") == 0)
{
if (custom_replace_string(&(info->argv[i]), custom_convert_number(info->exit_status)) == 0)
{
return (0);
}
}
else if (!strcmp(info->argv[i], "$$"))
{
if (custom_replace_string(&(info->argv[i]), custom_convert_number((int)getpid())) == 0)
{
return (0);
}
}
else
{
node = custom_node_starts_with(info_env, info->argv[i] + 1, '=');
if (node)
{
char *temp = strdup(strchr(node->str, '=') + 1);
if (custom_replace_string(&info->argv[i], temp) == 0)
{
free(temp);
return (0);
}
free(temp);
}
else
{
if (custom_replace_string(&(info->argv[i]), strdup("")) == 0)
{
return (0);
}
}
}
i++;
}
return (1);
}
/**
* custom_replace_string - replaces a string.
* @old: address of the old string.
* @new: new string
* Return: 1 if replaced, 0 otherwise.
*/
int custom_replace_string(char **old, char *new)
{
char *temp;
if (new != NULL)
{
temp = strdup(new);
*old = temp;
}
else
{
temp = strdup("");
*old = temp;
}
return (1);
}
/**
 * custom_node_starts_with - Find nodes in a list that start with a given string.
 * @list: A pointer to the list of strings.
 * @str: The string to search string.
 * @delimiter: The character that shoulf follow the searched string.
 * Return: A new list containing nodes that match the criteria.
 */
list_t *custom_node_starts_with(list_t *list, const char *str, char delimiter)
{
list_t *result = NULL;
while (list != NULL)
{
if (strncmp(list->str, str, strlen(str)) == 0 && list->str[strlen(str)] == delimiter)
{
list_t *new_node = malloc(sizeof(list_t));
if (new_node == NULL)
{
return (NULL);
}
new_node->str = strdup(list->str);
if (new_node->str == NULL)
{
free(new_node);
return (NULL);
}
new_node->next = result;
result = new_node;
}
list = list->next;
}
return (result);
}
/**
 * custom_convert_number - Convert an integer to a string and back to an integer.
 * @value: The integer to convert.
 * Return: The integer value converted from thr input integer.
 */
char *custom_convert_number(int value)
{
char *result = malloc(20);
if (result == NULL)
{
return (NULL);
}
snprintf(result, 20, "%d", value);
return (result);
}
/**
 * custom_create_list_from_char_array - creates a linked list from an array of strings.
 * @array: the aray of strings to convert into a linked list.
 * Return: A pointer to the head of the linked list.
 */
list_t *custom_create_list_from_char_array(char **array)
{
list_t *head = NULL;
list_t *current = NULL;
int i = 0;
while (array[i] != NULL)
{
list_t *new_node = malloc(sizeof(list_t));
if (new_node == NULL)
{
return (NULL);
}
new_node->str = strdup(array[i]);
if (new_node->str == NULL)
{
free(new_node);
return (NULL);
}
new_node->next = NULL;
if (head == NULL)
{
head = new_node;
current = new_node;
}
else
{
current->next = new_node;
current = new_node;
}
i++;
}
return (head);
}
/**
 * main - Entry point for the custom shell program
 * Return: Always 0.
 */
int main(void)
{
char input_buffer[1024];
info_t info;
info.env = NULL;
info.argv = NULL;
info.alias = NULL;
info.exit_status = 0;
info.cmd_buf_type = CMD_OR;
while (1)
{
printf("Enter a command: ");
if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
{
break;
}
custom_replaces_vars(&info);
custom_replaces_alias(&info);
}
return (0);
}
