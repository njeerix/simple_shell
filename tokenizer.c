#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
 * is_delimiter - checks if a character is a delimiter.
 * @c: The character to check.
 * @delimiters: the list of delimiter characters.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimiter(char c, const char *delimiters)
{
while (*delimiters != '\0')
{
if (c == *delimiters)
{
return (1);
}
delimiters++;
}
return (0);
}
/**
* custom_string_split - splits a string into words based on delimiters.
* @str: The input string to split.
* @delimiters: The delimiters - the delimeter characters to
* split the string.
* Return: a pointer toa n arrays of strings, or NULL on failure.
*/
char **custom_string_split(char *str, const char *delimiters)
{
char **words = NULL;
size_t numwords = 0;
size_t i, j, k, m;
if (str == NULL || delimiters == NULL)
return (NULL);
if (!delimiters)
{
delimiters = " ";
}
for (i = 0; str[i] != '\0'; i++)
{
if (!is_delimiter(str[i], delimiters) && (is_delimiter(str[i + 1],
delimiters) || !str[i + 1]))
{
numwords++;
}
}
if (numwords == 0)
{
return (NULL);
}
words = (char **)malloc((1 + numwords) * sizeof(char *));
if (!words)
{
return (NULL);
}
for (j = 0, i = 0; j < numwords; j++)
{
while (is_delimiter(str[i], delimiters))
{
i++;
}
k = 0;
while (!is_delimiter(str[i + k], delimiters) && str[i + k])
{
k++;
}
words[j] = (char *)malloc((k + 1) * sizeof(char));
if (!words[j])
{
for (m = 0; m < j; m++)
{
free(words[m]);
}
return (NULL);
}
for (m = 0; m < k; m++)
{
words[j][m] = str[i++];
}
words[j][k] = '\0';
}
words[numwords] = NULL;
return (words);
}
/**
 * main - entry point
 * Return: 0 always
 */
int main(void)
{
char str[] = "This is a sample string,split it.";
const char *delimiters = " ,";
char **words = custom_string_split(str, delimiters);
if (words != NULL)
{
int i = 0;
while (words[i] != NULL)
{
printf("Word %d: %s\n", i, words[i]);
free(words[i]);
i++;
}
free(words);
}
return (0);
}
