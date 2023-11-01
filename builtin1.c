#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
* removeAlias - Removes an alias.
* @info: Parameter structure.
* @str: The alias string to remove.
* Return: Always 0 on success, 1 on error.
*/
int removeAlias(info_t *info, char *str)
{
int result;
char *equalSign = strchr(str, '=');
char tempChar;
if (!equalSign)
return (1);
tempChar = *equalSign;
*equalSign = 0;
result = deleteAlias(&(info->alias), str);
*equalSign = tempChar;
return (result);
}
/**
* createAlias - Sets an alias.
* @info: Parameter structure.
* @str: The alias string to set.
* Return: Always 0 on success, 1 on error.
*/
int createAlias(info_t *info, char *str)
{
char *equalSign = strchr(str, '=');
if (!equalSign)
return (1);
if (addAliasToEnd(&(info->alias), str, 0) == 0)
return (1);
return (0);
}
/**
* printSingleAlias - Prinnts a aingle alias.
* @node: The alias node.
* Return: Always 0 on success, 1 on error.
*/
int printSingleAlias(list_t *node)
{
char *equalSignPosition;
char *aliasPart;
if (!node)
return (1);
equalSignPosition = strchr(node->str, '=');
if (!equalSignPosition)
return (1);
aliasPart = node->str;
while (aliasPart <= equalSignPosition)
{
putchar(*aliasPart);
aliasPart++;
}
putchar('\'');
printf("%s'\'", equalSignPosition + 1);
return (0);
}
/**
* manageAlias - Manages aliases, displaying or creating them.
* @info: Structure containing potential arguments.
* Return: Always 0.
*/
int manageAlias(info_t *info)
{
int i;
list_t *aliasNode;
char *equalSignPosition;
if (info->argc == 1)
{
aliasNode = info->alias;
while (aliasNode)
{
printSingleAlias(aliasNode);
aliasNode = aliasNode->next;
}
}
else
{
for (i = 1; info->argv[i]; i++)
{
equalSignPosition = strchr(info->argv[i], '=');
if (equalSignPosition)
{
createAlias(info, info->argv[i]);
}
else
{
printSingleAlias(findAliasWithPrefix(info->alias, info->argv[i]));
}
}
}
return (0);
}
/**
* deleteAlias - Delete an alias from the list.
* @head: A pointer to the head of the alias list.
* @name: The name of the alias to delete.
* Return: 0 on success, 1 if the alias is not found.
*/
int deleteAlias(list_t **head, char *name)
{
list_t *current = *head;
list_t *prev = NULL;
while (current != NULL)
{
if (strcmp(current->name, name) == 0)
{
if (prev == NULL)
{
*head = current->next;
}
else
{
prev->next = current->next;
}
free(current->name);
free(current->value);
free(current);
return (0);
}
prev = current;
current = current->next;
}
return (1);
}
