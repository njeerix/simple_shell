#include " shell.h"
/**
* custom_string_split - splits a string into words based on delimiters.
* @param str - The input string to split.
* @param delimiters - The delimiters - the delimeter characters to
* split the string.
* Return: a pointer toa n arrays of strings, or NULL on failure.
*/
char **custom_string_split(char *str, const char *delimiters)
{
int i, j, k, m, numwords = 0;
char **words;
if (str == NULL || str[0] == '\0')
{
return (NULL);
}
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
for (i = 0, j = 0; j < numwords; j++)
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
for (k = 0; k < j; k++)
{
free(words);
return (NULL);
}
for (m = 0; m < k; m++)
{
words[j][m] = str[i++];
}
words[j][m] = '\0';
}
words[j] = NULL;
return (words);
}
