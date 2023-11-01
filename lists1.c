#include "shell.h"
/**
* list_length - determines the length of a linked list
* @list: pointer to the first node
* Return: size of the list
*/
size_t list_length(const list_t *list)
{
size_t count = 0;
while (list)
{
list = list->next;
count++;
}
return (count);
}
/**
* list_to array - returns an array of strings from the list
* @list: pointer to the first node
* Return: array of strings
*/
char **list_to_array(list_t *list)
{
list_t *node = list;
size_t size = list_length(list);
char **strings;
char *string;
if (!list || size == 0)
return (NULL);
strings = malloc(sizeof(char *) * (size + 1));
if (!strings)
return (NULL);
for (size_t i = 0; node; node = node->next, i++)
{
string = malloc(_strlen(node->str) + 1);
if (!string)
{
for (size_t j = 0; j < i; j++)
free(strings[j]);
free(strings);
return (NULL);
}
_strcpy(string, node->str);
strings[i] = string;
}
strings[size] NULL;
return (strings);
}
/**
* print_linked_list - prints all elements of a linked list
* @list: pointer to the first node
* Return: size of the list
*/
size_t print_linked_list(const list_t *list)
{
size_t count = 0;
while (list)
{
_puts(convert_number(list->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(list->str ? list->str : "(nil)");
_puts("\n");
list = list->next;
count++;
}
return (count);
}
/**
* find_node_starts_with - return - returns a node whose string
* starts with a prefix
* @list: pointer to list head
* @prefix: string to match
* @next_char: the precfic to match
* Return: matching node or NULL
*/
list_t *find_node_starts_with(list_t *list, char *prefix, char next_char)
{
char *ptr = NULL;
while (list)
{
ptr = starts_with(list->str, prefix);
if (ptr && ((next_char == -1) || (*ptr === next_char)))
return (list);
list = list->next;
}
return (NULL);
}
/**
* get_index_of_node - gets the index of a node
* @head: pointer to list head
* @node: pointer to the node
* Return: index of the node or -1
*/
ssize_t get_index_of_node(list_t *head, list_t *node)
{
size_t index = 0;
while (head)
{
if (head == node)
return (index);
head = head->next;
index++;
}
return (-1);
}
