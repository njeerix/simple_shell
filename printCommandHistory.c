#include "shell.h"
#include <stdio.h>
#include "node.h"
/**
* printCommandHistory - Print a command history entry.
* @history: A pointer to a history_t structure.
* This function prints a command history entry, including the command
* and timestap.
*/
void printCommandHistory(history_t *history)
{
if (history)
{
printf("%s", history->command);
printf(" [%lu]\n", (unsigned long)history->timestamp);
}
}
/**
 * main - Entry point fo the simple shel program
 * Return: Always 0 (success)
 */
int main(void)
{
history_t history_entry;
printCommandHistory(&history_entry);
return (0);
}
