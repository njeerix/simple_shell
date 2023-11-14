#include "shell.h"
#include <stdlib.h>
/**
* custom_free - frees a pointer and sets it to NULL
* @ptr: pointer to free
* Return: 1 if freed, otherwise 0.
*/
int custom_free(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
/**
 * main - entry point
 * Return: always 0
 */
int main()
{
return (0);
}
