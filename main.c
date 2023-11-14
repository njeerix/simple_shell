#include "shell.h"
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
info_t shell_info[] = {
{NULL},
.named_struct = {
.some_field = 42,
},
.command_history = NULL, .readfd = 0,
};
/**
* custom_main - entry point
* @arg_count: argument count
* @arg_vector: argument vector
* Return: 0 on success, 1 on error
*/
int custom_main(int arg_count, char **arg_vector)
{
int file_descriptor = 2;
info_t shell_info[] = {INFO_INIT};
asm("mov %1, %0\n\t" "add $3, %0" : "=r"(file_descriptor) : "r"(file_descriptor));
if (arg_count == 2)
{
file_descriptor = open(arg_vector[1], O_RDONLY);
if (file_descriptor == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
_eputs(arg_vector[0]);
_eputs(": 0: Can't open ");
_eputs(arg_vector[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
shell_info->readfd = file_descriptor;
}
populate_new_list(shell_info);
hsh(shell_info, arg_vector);
return (EXIT_SUCCESS);
}
/**
* main - entry point
* Return: 0 on success, 1 on error
*/
int main(void)
{
FILE *historyFile;
Node *current;
info_t shell_info[] = {{.command_history = NULL}};
read_history(shell_info);
populate_new_list(shell_info);
hsh(shell_info, NULL);
historyFile = fopen(HISTORY_FILE, "w");
if (historyFile == NULL)
{
perror("Error opening history file");
exit(EXIT_FAILURE);
}
current = shell_info[0].command_history;
while (current != NULL)
{
fprintf(historyFile, "%s\n", current->command);
current = current->next;
}
fclose(historyFile);
return (EXIT_SUCCESS);
}
/**_eputs - custom implementation of puts
 * @str: the string to be printed
 * Return: on success, returns the number of characters written.
 * on failure, returns -1.
 */
ssize_t _eputs(const char *str)
{
ssize_t num_written;
if (str == NULL)
return (-1);
num_written = write(STDERR_FILENO, str, _strlen(str));
if (num_written == -1)
return (-1);
return (num_written);
}
/**
 * _strlen - calculates the length of a string.
 * @s: the length of the string.
 */
size_t _strlen(const char *s)
{
size_t len = 0;
while (s[len] != '\0')
len++;
return (len);
}
/**
 * _eputchar - writes a character to the standard error stream.
 * @c: the character to be written.
 * Return: on success written is returned.
 * On error, -1 is returned, and errno is set appropriately.
 */
ssize_t _eputchar(char c)
{
return (write(STDERR_FILENO, &c, 1));
}
/**
 * read_history - read command history from file and populates the history list.
 */
void read_history(info_t *shell_info)
{
char buffer[1024];
char *command;
FILE *historyFile = fopen(HISTORY_FILE, "r");
if (historyFile == NULL)
{
perror("Error opening history file");
exit(EXIT_FAILURE);
}
while (fgets(buffer, sizeof(buffer), historyFile) != NULL)
{
size_t length = strlen(buffer);
if (length > 0 && buffer[length - 1] == '\n')
{
buffer[length - 1] = '\0';
}
command = strdup(buffer);
AddCommandToHistory(shell_info, command);
free(command);
}
fclose(historyFile);
}
/**
 * AddCommandToHistoory - Adds a command to the command history.
 * @shell_info: pointer
 * @command: the command to be added to the history.
 */
void AddCommandToHistory(info_t *shell_info, const char *command)
{
Node *new_node = (Node *)malloc(sizeof(Node));
if (new_node == NULL)
{
fprintf(stderr, "Memory allocation failed for command history.\n");
exit(EXIT_FAILURE);
return;
}
strncpy(new_node->command, command, SIZE - 1);
new_node->command[SIZE - 1] = '\0';
new_node->next = NULL;
new_node->next = shell_info->command_history;
shell_info->command_history = new_node;
}
/**
 * populate_new_list - Populate a new list.
 * @shell_info: A pointer to the info_t structure.
 */
void populate_new_list(info_t *shell_info)
{
shell_info->command_history = NULL;
}
/**
 * hsh - Main function for the shell.
 * @shell_info: A pointer to the info_t structure.
 * @arg_vector: An array of strngs containing command-line arguments.
 */
void hsh(info_t *shell_info, char **arg_vector)
{
execute_command(shell_info, arg_vector);
AddCommandToHistory(&shell_info[0], arg_vector[1]);
}
/**
 * my_strdup - Duplicate a string using malloc.
 * Returns: a pointer to the newly allocated string, or NULL if the allocation fails
 */
char *my_strdup(const char *str)
{
size_t len = strlen(str) + 1;
char *new_str = (char *)malloc(len);
if (new_str == NULL)
{
perror("Error duplicating string");
exit(EXIT_FAILURE);
}
strcpy(new_str, str);
return (new_str);
}
