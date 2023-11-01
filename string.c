#include "shell.h"
/**
* Calculates the length of a string.
* @param str - The input string.
* Return - The length of the string.
*/
int custom_string_length(char *str)
{
int length = 0;
if (!str)
{
return (0);
}
while (*str++)
{
length++;
}
return (length);
}
/**
* Compares teo strings lexicographically.
* @param str1 - The first string.
* @param str2 - The second string.
* Return - Negative if str1 < str2, positive if str1
* > str2, zero if str1 == str2.
*/
int custom_string_compare(char *str1, char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
{
return (*str1 - *str2)
}
str1++;
str2++;
}
if (*str1 == *str2)
{
return (0);
}
else
{
return (*str1 < *str2 ? -1 : 1);
}
}
/**
* checks if a string starts with a specified substring.
* @param str - The string to search.
* @param prefix - The substring to find at the beginning.
* Return - the address of the character after the prefix, or NULL
* if not found
*/
char *custom_string_starts_with(cinst char *str, const char *prefix)
{
while (*prefix)
{
if (*prefix++ != *str++)
{
return (NULL);
}
}
return ((char *)str);
}
/**
* Concatenates teo strings.
* @param destination - The destination buffer.
* @param source - The source buffer to append.
* Return - a pointer to the destination buffer.
*/
char *custom_string_concatenate(char *destination, char *source)
{
char *result = destination;
while (*destination)
{
destination++;
}
while (*source)
{
*destination++ = *source++;
}
*destination = *source;
return (result);
}
