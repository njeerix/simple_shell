#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
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
info_t info;
init_info(&info, NULL, NULL);
while (1)
{
char *input = NULL;
size_t len = 0;
ssize_t read;
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "$ ", 2);
read = getline(&input, &len, stdin);
if (read == -1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "\n", 1);
free(input);
break;
}
if (read > 1)
{
if (input[read - 1] == '\n')
input[read - 1] = '\0';
removeComments(input);
if (input[0] != '\0')
{
execute_command(&info, &input);
printErrorMessage(&info, "Command not found");
}
}
free(input);
}
free_info(&info);
return (0);
}
/**
 * init_info - initializes the info structure.
 * @info: pointer to the info structure to be initialized.
 * @env: array of environment variables.
 * @argv: array of command-line arguments.
 */
void init_info(info_t *info, char **env, char **argv)
{
if (info == NULL)
{
return;
}
info->env = env;
info->argv = argv;
if (argv != NULL && argv[0] != NULL)
{
info->name = strdup(argv[0]);
}
else
{
info->name = NULL;
}
}
/**
 * freed_info - frees resources associated with the info structure.
 * @info: pointer to the info structure to be freed.
 */
void free_info(info_t *info)
{
if (info == NULL)
{
return;
}
if (info->name != NULL)
{
free(info->name);
}
info->env = NULL;
info->argv = NULL;
info->name = NULL;
}
/**
 * execute_command -  executes a shell command.
 * @info: pointer to the info structure.
 * @arg_vector: array of command-line arguments.
 * Return: 0 on success, -1 on failure.
 */
int execute_command(info_t *info, char **arg_vector)
{
pid_t pid;
if (info == NULL || arg_vector == NULL || arg_vector[0] == NULL)
{
return (-1);
}
pid = fork();
if (pid == -1)
{
perror("fork");
return (-1);
}
if (pid == 0)
{
if (execve(arg_vector[0], arg_vector, info->environ) == -1)
{
perror("execve");
_exit(EXIT_FAILURE);
}
}
else
{
int status;
if (waitpid(pid, &status, 0) == -1)
{
perror("waitpid");
return (-1);
}
else
{
return (WEXITSTATUS(status));
}
}
return (-1);
}
