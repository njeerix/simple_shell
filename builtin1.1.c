#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
* addAliasToEnd - Add an alias to the end of the list.
* @head: A pointer to the head of the alias list.
* @str: The name of the alias.
* @value:  the value of the alias.
* Return: 0 on success, 1 if memory allocation fails.
*/
int addAliasToEnd(list_t **head, char *str, char *value)
{
list_t *newAlias = malloc(sizeof(list_t));
if (newAlias == NULL)
{
return (1);
}
newAlias->str = strdup(str);
newAlias->name = strdup(str);
newAlias->value = strdup(value);
newAlias->next = NULL;
if (*head == NULL)
{
*head = newAlias;
}
else
{
list_t *current = *head;
while (current->next != NULL)
{
current = current->next;
}
current->next = newAlias;
}
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
/**
 * main - entry point
 * Return: Always 0
 */
int main(void)
{
info_t info;
info.alias = NULL;
info.argc = 0;
info.argv = NULL;
manageAlias(&info);
while (info.alias)
{
list_t *temp = info.alias;
info.alias = info.alias->next;
free(temp->name);
free(temp->value);
free(temp);
}
return (0);
}
