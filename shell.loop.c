#include "shell.h"
/**
* custom_shell_loop - responsible for reading and executing commands
* @param info - The custom shell information struct.
* @param arguments - Command-line arguments passed to the progrm.
* Return: 0 on success, 1 on error, or an error code.
*/
int custom_shell_loop(MyShellInfo *info, char **arguments)
{
ssize_t read_result = 0;
int builtin_result = 0;
while (read_result != -1 && builtin_result != -2)
{
custom_clear_info(info);
if (custom_interactive(info))
{
custom_output_string("$ ");
}
custom_error_character(BUFFER_FLUSH);
read_result = custom_get_input(info);
if (read_result != -1)
{
custom_setup_info(info, arguments);
builtin_result = find_custom_builtin(info);
if (builtin_result == -1)
{
find_command(info);
}
}
else if (custom_interactive(info))
{
custom_clean_up_info(info, 0);
}
custom_write_history(info);
custom_clean_up_info(info, 1);
if (!custom_interactive(info) && info->execution_status)
{
exit(info->axecution_status);
}
if (builtin_result == -2)
{
if (info->error_number == -1)
{
exit(info->execution_status);
}
exit(info->error_number);
}
return (builtin_result);
}
/**
* searches for a built-in command int the custom shell
* @param info - the custom shell information struct
* Return: -1 if built-in not found, 0 if built-in executed successfully.
* 1 if builtin-in found but not successful, 2 if built-in signals exit().
*/
int find_custom_builtin(MyShellInfo *info)
{
int i;
int built_in_result = -1;
MyBuiltinTable custom_builtin_table[] = {{"exit", custom_exist},
{"env", custom_environment}, {"help" custom_help}, {"history", custom_history},
{"setenv", custom_set_environment_variable}, {"unsetenv", custom_unset_environment_variable},
{"cd", custom_change_directory}, {"alias", custom_alias}, {NULL, NULL}};
for (i = 0; custom_builtin_table[i].type; i++)
{
if (custom_string_compare(info->arg_values[0], custom_builtin_table[i].type) == 0)
{
info->line_count++;
built_in_result = custom_builtin_table[i].function(info);
break;
}
}
return (builtin_in result);
}
/**
* searches for a custom shell command in the PATH.
* @param info - the custom shell information struct.
*/
void find_command(MyShellInfo *info)
{
char *path = NULL;
int i, k;
info->command_path = info->arg_value[0];
if (info->count_lines == 1)
{
info->line_count++;
info->count_lines = 0;
}
for (i = 0; k = 0; info->arguments[i]; i++)
{
if (!custom_is_delimiter(info->arguments[i], " \t\n"))
{
k++;
}
}
if (!k)
{
return;
}
path = custom_find_command_path(info, custom_get_environment_variable(info, "PATH="),info->arg_values[0]);
if (path)
{
info->command_path = path;
custom_execute_command(info);
}
else
{
if ((custom_interactive(info) || custom_get_environment_variable(info, "PATH=") || info->arg_values[0][0]
== '/') && is_command(info, info->arg_values[0]))
{
custom_execute_command(info);
}
else if (*(info->arguments) 1= '\n')
{
info->execution_status = 127;
custom_print_error(info, "not found\n");
}
}
}
/**
* Forks a child process to execute a custom shell command.
* @param info - The custom shell information struct.
*/
void custom_execute_command(MyShellInfo *info)
{
pid_t child_pid;
child_pid = fork();
if  (child_pid == -1)
{
perror ("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->command_path, info->arg_values, custom_get_environment(info)) == -1)
{
custom_clean_up_info(info, 1);
if (errno == EACCES)
{
exit(126);
}
exit(1);
}
}
else
{
write(&(info->execution_status));
if (WIFEXITED(info->execution_ststus))
{
info->execution_status = WEXITSTATUS(info->execution_ststus);
if (info->execution_status == 126)
{
custom_print_error(info, "permission denied\n");
}
}
}
}
