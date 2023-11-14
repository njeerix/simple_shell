#include "shell.h"
#include <sys/stat.h>
/**
* is_executable - checks if a file is an executable command
* @info: the info struct
* @filepath: path to the file
* Return: 1 if it's an exucatable. 0 otherwise
*/
int is_executable(info_t *info, char *filepath)
{
struct stat file_stat;
(void)info;
if (!filepath || stat(filepath, &file_stat))
return (0);
if (S_ISREG(file_stat.st_mode) && (file_stat.st_mode & S_IXUSR))
{
return (1);
}
return (0);
}
/**
* copy_substring - duplicates a substring from a string
* @source: the source string
* @start: starting index of the substring
* @stop: stopping index of the substring
* Return: pointer to the copied substring
*/
char *copy_substring(char *source, int start, int stop)
{
static char buffer[1024];
int i = 0, k = 0;
for (k = 0, i = start; i < stop; i++)
{
if (source[i] != ':')
{
buffer[k++] = source[i];
}
}
buffer[k] = '\0';
return (buffer);
}
/**
* find_command_path - finds the full path of a command in the PATH string
* @info: the info struct
* @pathstr: the PATH string
* @cmd: the command to find
* Return: full path of the command if found, or NULL
*/
char *find_command_path(info_t *info, char *pathstr, char *cmd)
{
int i= 0, current_position = 0;
char *path;
if ((strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_executable(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = copy_substring(pathstr, current_position, i);
if (!*path)
{
strcat(path, "/");
strcat(path, cmd);
}
if (is_executable(info, path))
return (path);
if (!pathstr[i])
break;
current_position = i;
}
i++;
}
return (NULL);
}
/**
 * starts_with - checks if astring starts with a given prefix.
 * @str: a null-terminated string to check.
 * @prefix: a null-terminated string representing the prefix to check for.
 * Return: 1 if the string starts with the prefix, 0 otherwise.
 */
int starts_with(const char *str, const char *prefix)
{
(void)str;
(void)prefix;
return (0);
}
/**
 * main - entry point
 * Return: always 0
 */
int main()
{
return (0);
}
