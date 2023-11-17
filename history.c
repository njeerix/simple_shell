#include "shell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
/**
* generate_history_filename - generates the history file's
* path
* @info: parameter struct
* Return: dynamically allocated string containing the history
* file path
*/
char *generate_history_filename(info_t *info)
{
char *home_dir;
char *history_path;
home_dir = _getenv(info, "HOME=");
if (home_dir == NULL)
{
return (NULL);
}
history_path = malloc(_strlen(home_dir) + _strlen(HISTORY_FILE) + 2);
if (history_path == NULL)
{
free(home_dir);
return (NULL);
}
_strcpy(history_path, "/");
_strcat(history_path, HISTORY_FILE);
free(home_dir);
return (history_path);
}
/**
* save_history - Saves command history to a file
* @info: The parameter struct
* Return: 1 on success, -1 on failure
*/
int save_history(info_t *info)
{
char *filename = generate_history_filename(info);
if (!filename)
return (0);
int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (0);
list_t *node = info->history;
while (node != NULL)
{
_putsfd(node->str, fd);
_putcharfd('\n', fd);
node = node->next;
}
close(fd);
return (1);
}
/**
* load_history - loads command history from a file
* @info: the parameter struct
* Return: the number of loaded history entries, 0 on failure
*/
int load_history(info_t *info)
{
char *filename = generate_history_filename(info);
if (!filename)
return (0);
int fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
struct stat st;
if (fstat(fd, &st) != 0)
{
close(fd);
return (0);
}
ssize_t file_size = st.st_size;
char *buffer = malloc(file_size + 1);
if (!buffer)
{
close(fd);
return (0);
}
ssize_t read_length = read(fd, buffer, file_size);
close(fd);
if (read_length <= 0)
{
free(buffer);
return (0);
}
buffer[file_size] = '\0';
int line_count = 0;
int last = 0;
for (int i = 0; i < file_size; i++)
{
if (buffer[i] == '\n')
{
buffer[i] = '\0';
build_history_entry(info, buffer + last, line_count++);
last = i + 1;
}
}
if (last != file_size)
build_history_entry(info, buffer + last, line_count++);
free(buffer);
info->history = line_count;
while (info->histcount-- >= HIST_MAX)
delete_history_entry(&(info->history), 0);
renumber_history_entries(info);
return (line_count);
}
/**
* build_history_entry - adds an entry to the command history
* @info: the parameter struct
* @command: the history to add
* @linecount: the history line count
* Return: Always 0
*/
int build_history_entry(info_t *info, char *command, int linecount)
{
list_t *node = NULL;
if (info->history)
node = info->history;
add_history_entry(&node, command, linecount);
if (!info->history)
info->history = node;
return (0);
}
/**
* renumber_history_entries - renumebrs the history entries after changes
* @info: the parameter struct
* Return: the new histcount
*/
int renumber_history_entries(info_t *info)
{
int count = 1;
int i;
history_t *node = info->history;
for (i = 0; i < info->histcount; i++)
{
node->entry_number = count++;
node = node->next;
info->history[i].entry_number = count++;
}
info->histcount = count;
return (info->histcount);
}
