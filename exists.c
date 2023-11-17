#include "shell.h"
/**
* _strncpy_custom - Custom string copy function
* @dest: Destination string
* @src: Source string
* @n: Maximum number of characters to copy
* Return: Pointer to the destination string
*/
char *_strncpy_custom(char *dest, const char *src, int n)
{
char *d = dest;
const char *s = src;
while (n > 0 && *s)
{
*d++ = *s++;
n--;
}
while (n > 0)
{
*d++ = '\0';
n--;
}
return (dest);
}
/**
* _strncat_custom - Custom string concatenation function
* @dest: Destination string
* @src: Source string
* @n: Maximum number of characters to concatenate
* Return: Pointer to the destination string
*/
char *_strncat_custom(char *dest, const char *src, int n)
{
char *d = dest;
const char *s = src;
while (*d)
d++;
while (n > 0 && *s)
{
*d++ = *s++;
n--;
}
*d = '\0';
return (dest);
}
/**
* _strchr_custom - Custom string character search function
* @s: String to search in
* @c: Character to search for
* Return: Pointer to the first occurence of the character, or
* NULL if not found
*/
char *_strchr_custom(const char *s, char c)
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
 * main - entry point of the progarm
 * Return: 0 on success, non_zero on failure
 */
int main(void)
{
char c;
char dest[100] = "Hello";
const char src[] = "World!";
int n = 5;
char *result;
_strncpy_custom(dest, src, n);
printf("Copied string: %s\n", dest);
_strncat_custom(dest, src, n);
printf("Concatenated string: %s\n", dest);
c = 'W';
result = _strchr_custom(dest, c);
if (result != NULL)
printf("Character '%c' found at position: %ld\n", c, result - dest);
else
printf("Character '%c' not found in the string\n", c);
return (0);
}
