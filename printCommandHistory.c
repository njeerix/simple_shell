#include "shell.h"
#include <stdio.h>
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
