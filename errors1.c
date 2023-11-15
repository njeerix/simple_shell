#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
/**
* customAtoi - converts a string to an integer
* @s: the string to be converted
* Return: The converted number if valid, INT_MIN on error
*/
int customAtoi(const char *s)
{
int digit;
int result = 0;
int sign = 1;
int i = 0;
if (!s)
return (INT_MIN);
if (s[0] == '-')
{
sign = -1;
i++;
}
for (; s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
digit = s[i] - '0';
if (result > (INT_MAX - digit) / 10)
return (INT_MIN);
result = result * 10 + digit;
}
else
{
return (INT_MIN);
}
}
return (result *sign);
}
/**
* printErrorMessage - prints an error message
* @info: the parameter & return info struct
* @errorMsg: string containing the error message
*/
void printErrorMessage(info_t *info, const char *errorMsg)
{
fprintf(stderr, "%s: %s\n", info->name, errorMsg);
}
/**
* printDecimal - prints a decimal (integer) number (base 10)
* @num: the nunt printDecimal number to print
* @fd: the file descriptor to write to
* Return: The number of characters printed
*/
void printDecimal(int fd, int num)
{
char buffer[12];
int count;
count = snprintf(buffer, sizeof(buffer), "%d", num);
if (count >= 0)
{
if (write(fd, buffer, count) < 0)
{
perror("write");
}
}
else
{
perror("snprintf");
}
}
/**
* removeComments - replaces the first instance of '#' with '\0'
* @str: The string to modify
*/
void removeComments(char *str)
{
int i = 0;
if (!str)
return;
for (i = 0; str[i] != '\0'; i++)
{
if (str[i] == '#' && (i == 0 || str[i - 1] == ' '))
{
str[i] = '\0';
break;
}
}
}
/**
 * main - the main entry point for the shell program.
 * Return: 0 on success, non-zero on failure.
 */
int main(void)
{
}
