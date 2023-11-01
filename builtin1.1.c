#include "shell.h"
#include <stdlib.h>
#include <string.h>
/**
* addAliasToEnd - Add an alias to the end of the list.
* @head: A pointer to the head of the alias list.
* @str: The alias string to add.
* @n: An integer parameter (description needed).
* Return: 0 on success, 1 if memory allocation fails.
*/
int addAliasToEnd(list_t **head, char *str, int n)
{
list_t *new_alias = malloc(sizeof(list_t));
if (new_alias == NULL)
{
return (1);
}
new_alias->str = strdup(str);
new_alias->name = strdup(str);
new_alias->value = NULL;
new_alias->next = NULL;
if (*head == NULL)
{
*head = new_alias;
}
else
{
list_t *current = *head;
while (current->next != NULL)
{
current = current->next;
}
current->next = new_alias;
}
(void)n;
return (0);
}
/**
* findAliasWithPrefix - Find an alias with the specified prefix.
* @head: A pointer to the head of the alias list.
* @prefix: The prefix to search for in alias names.
* Return: A pointer to the found alias or NULL if not found.
*/
list_t *findAliasWithPrefix(list_t *head, char *prefix)
{
while (head != NULL)
{
if (strncmp(head->name, prefix, strlen(prefix)) == 0)
{
return (head);
}
head = head->next;
}
return (NULL);
}
