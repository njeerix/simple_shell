#include <stddef.h>
#include "shell.h"
#include <stdio.h>
#define BUF_FLUSH '\0'
/**
* custom_strncpy - Custom string copy function
* @dest: Destination string
* @src: Source string
* @n: Maximum number if characters to copy
* Return: Pointer to the destination string
*/
char *custom_strncpy(char *dest, const char *src, size_t n)
{
char *destination = dest;
const char *source = src;
while (n > 0 && *source)
{
*destination++ = *source++;
n--;
}
while (n > 0)
{
*destination++ = '\0';
n--;
}
return (dest);
}
/**
* custom_strncat - Custom string concatenation function
* @dest: Destination string
* @src: Source string
* @n: Maximum number of characters to concatenate
* Return: Pointer to the destination string
*/
char *custom_strncat(char *dest, const char *src, size_t n)
{
char *destination = dest;
const char *source = src;
while (*destination)
destination++;
while (n > 0 && *source)
{
*destination++ = *source++;
n--;
}
*destination = '\0';
return (dest);
}
/**
* custom_strchr - Custom string character search function
* @s: String to search in
* @c: Character to search for
* Return: Pointer to the first occurence of the character, or NULL
* if not found
*/
char *custom_strchr(const char *s, int c)
{
while (*s)
{
if (*s == c)
return ((char *)s);
s++;
}
return (NULL);
}
/**
* custom_sigintHandler - Blocks Ctrl-C signal
* @sig_num: The signal number
* Return: void
*/
void custom_sigintHandler(__attribute__((unused))int sig_num)
{
printf("\n");
printf("$ ");
putchar(BUF_FLUSH);
}
/**
* main - Entry point for the shell program
* Return: Always 0
*/
int main(void)
{
info_t info;
info.env = NULL;
info.alias = NULL;
info.argv = NULL;
info.argc = 0;
info.readfd = 0;
info.history = NULL;
info.str = NULL;
interactive(&info);
return (0);
}
