#include "shell.h"
/**
* custom_string_copy - Copies a sting from source to destination.
* @param dest- The destination buffer.
* @param src - The source string to copy.
* Return: A pointer to the destination buffer.
*/
char *custom_string_copy(char *dest, const char *src)
{
int i = 0;
if (dest == src || src == NULL)
{
return (dest);
}
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = '\0';
return (dest);
}
/**
* custom_string_duplicate -  Duplicates a string and allocates memory for the duplicate.
* @param str - the string to duplicate
* Return: a pointer to the duplicated string.
*/
char *custom_string_duplicate(const char *str)
{
int length = 0;
char *ret;
if (str == NULL)
{
return (NULL);
}
while (*str++)
{
length++;
}
ret = (char *)malloc(sizeof(char) * (length + 1));
if (ret == NULL)
{
return (NULL);
}
for (length++; length--;)
{
ret[length] = *(--str);
}
return (ret);
}
/**
* custom_string_print - printd a string to the standard output.
* @param str - the string to print.
*/
void custom_string_print(const char *str)
{
int i = 0;
if (str == NULL)
{
return;
}
while (str[i] != '\0')
{
custom_character_print(const char *str)
{
int i = 0;
if (str == NULL)
{
return;
}
while (str[i] != '\0')
{
custom_character_print(str[i]);
i++;
}
}
/**
* custom_character_print - Writes a character to the standard output.
* @param c - the character to print.
* Return: on success, 1. On error, -1 is returned, and errno is set
* appropriately.
*/
int custom_character_print(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || I >= WRITE_BUF_SIZE)
{
custom_flush_buffer(buf, i);
i = 0;
}
if (c != BUF_flush)
{
buf[i++] = c;
}
return (1);
}
/**
* custom_flush_buffer - flushes the output buffer to the standard output.
* @param buf - The buffer to flush.
* @param size - the size of the buffer.
*/
void custom_flush_buffer(char *buf, int size)
{
write(1, buf, size);
}
