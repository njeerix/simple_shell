#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
* listHistory - Displays the command history with line numbers.
* @info: Structure containing potential arguments.
* Return: Always 0.
*/
int listHistory(info_t *info)
{
printCommandHistory(info->history);
return (0);
}
