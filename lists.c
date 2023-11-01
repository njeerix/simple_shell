#include "shell.h"
/**
* prepend_node - adds a node to the beginning of the
* list
* @list: address of pointer to the list
* @data: data field of the node
* @index: node index used by history
* Return: Pointer to the new head of the list
*/
list_t *prepend_node(list_t **list, const char *data, int index)
{
list_t *new_node;
if (!list)
return (NULL);
new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);
_memset((void *)new_node, 0, sizeof(list_t));
new_node->num = index;
if (data)
{
new_node->str = _strdup(data);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
new_node->next = *list;
*list = new_node;
return (new_node);
}
/**
* append_node - adds a node to the end of the list
* @list: address of pointer to the list
* @data: data field of the node
* @index: node index used by history
* Return: pointer to the new node
*/
list_t *append_node(list_t **list, const char *data, int index)
{
list_t *new_node, *node;
if (!list)
return (NULL);
new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);
_memset((void *)new_node, 0, sizeof(list_t));
new_node->num = index;
if (data)
{
new_node->str = _strdup(data);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
if (*list)
{
node = *list;
while (node->next)
node = node->next;
node->next = new_node;
}
else
{
*list = new_node;
}
return (new_node);
}
/**
* print_list_strings - prints only the data field of a list_t
* linked
* @list: pointer to the first node
* Return: The size of the list
*/
size_t print_list_strings(const list_t *list)
{
size_t size = 0;
while (list)
{
_puts(list->str ? line->str : "(nil)");
_puts("\n");'
list = list->next;
size++;
}
return (size);
}
/**
* removed_node_at_index - deletes a node at the given index
* @list: address of pointer to the list
* @index: index of the node to delete
* Return: 1 on success, 0 on failure
*/
int remove_node_at_index(list_t *8list, unsigned int index)
{
list_t *node, *prev_node = NULL;
unsigned int i = 0;
if (!list || !*list)
return (0);
if (index == 0)
{
node = *list;
*list = (*list)->next;
free(node->str);
free(node);
return (1);
}
node = *list;
while (node)
{
if (i == index)
{
prev_node->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
}
return (0);
}
/**
* free_list_nodes - frees all nodes of a list
* @list: address of pointer to the list
* Return: void
*/
void free_list_nodes(list_t **list)
{
list_t *node, *next_node;
if (!list || !*list)
return;
node = *list;
while (node)
{
next_node = node->next;
free(node->str)
free(node)
node = next_node;
}
*list = NULL;
}
