#include "shell.h"
#include <unistd.h>
/**
* interactive - returns true if shell is in interactive mode
* @info: struct address
* Return: 1 if interactive mode, 0 otherwise
*/
int interactive(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
* is_delim - checks if character is a delimiter
* @c: the char to check
* @delim: the delimiter string
* Return: 1 if true, 0 if false
*/
int is_delim(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);
return (0);
}
/**
* _isalpha - checks for alphabetic character
* @c: The character to input
* Return: 1 if c is alphabetic, 0 otherwise
*/
int _isalpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}
/**
* _atoi - converts a string to an integer
* @s: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*/
int _atoi(char *s)
{
int i = 0, sign = 1, output = 0;
while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
i++;
if (s[i] == '-')
{
sign = -1;
i++;
}
while (s[i] >= '0' && s[i] <= '9')
{
output = output * 10 + (s[i] - '0');
i++;
}
return (output *sign);
}
/**
 * main - entry point
 * Return: Always 0
 */
int main(void)
{
int interactive_result;
char delimiterString[] = " ,:";
char testAlpha = 'A';
char numString[] = "12345";
int convertedNum;
int is_delim_result;
int _isalpha_result;
info_t myInfo;
if ((interactive_result = interactive(&myInfo)) != 0)
{
printf("The shell is in interactive mode.\n");
}
else
{
printf("The shell is not in interactive mode.\n");
}
if ((is_delim_result = is_delim(testAlpha, delimiterString)) != 0)
{
printf("%c is a delimiter.\n", testAlpha);
}
else
{
printf("%c is not a selimiter.\n", testAlpha);
}
if ((_isalpha_result = _isalpha(testAlpha)) != 0)
{
printf("%c is an alphabetic character.\n", testAlpha);
}
else
{
printf("%c is not an alphabetic character.\n", testAlpha);
}
convertedNum = _atoi(numString);
printf("Converted number: %d\n", convertedNum);
return (0);
}
