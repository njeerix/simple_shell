#include "shell.h"
#include <stdio.h>
/**
* custom_string_length - Calculates the length of a string.
* @str: The input string.
* Return: The length of the string.
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
* custom_string_compare - Compares teo strings lexicographically.
* @str1: The first string.
* @str2: The second string.
* Return: Negative if str1 < str2, positive if str1
* > str2, zero if str1 == str2.
*/
int custom_string_compare(char *str1, char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
{
return (*str1 - *str2);
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
* custom_string_starts_with - checks if a string starts with a specified substring.
* @str: The string to search.
* @prefix: The substring to find at the beginning.
* Return: the address of the character after the prefix, or NULL
* if not found
*/
char *custom_string_starts_with(const char *str, const char *prefix)
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
* custom_string_concatenate - Concatenates teo strings.
* @destination: The destination buffer.
* @source: The source buffer to append.
* Return: a pointer to the destination buffer.
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
/**
 * main - entry point of the program
 * Return: Always 0 (success)
 */
int main(void)
{
char str1[] = "Hello, ";
char str2[] = "world!";
char result[100];
int length = custom_string_length(str1);
int comparison = custom_string_compare(str1, str2);
char *prefix = custom_string_starts_with(str1, "Hello");
printf("String 1: %s\n", str1);
printf("String 2: %s\n", str2);
printf("Length of String 1: %d\n", length);
if (comparison < 0)
{
printf("String 1 is less than String 2\n");
}
else if (comparison > 0)
{
printf("String 1 is greater than String 2\n");
}
else
{
printf("String 1 is equal to String 2\n");
}
if (prefix)
{
printf("String 1 starts with 'Hello', and the rest is : %s\n", prefix);
}
else
{
printf("String 1 doesn't start with 'Hello'\n");
}
custom_string_concatenate(result, str1);
custom_string_concatenate(result, str2);
printf("Concatenated String: %s\n", result);
return (0);
}
