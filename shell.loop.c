#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include "node.h"
#define MAX_COMMAND_LENGTH 100
/**
* custom_shell_loop - responsible for reading and executing commands
* @info: The custom shell information struct.
* @arguments: Command-line arguments passed to the progrm.
* Return: 0 on success, 1 on error, or an error code.
*/
int custom_shell_loop(info_t *info)
{
ssize_t read_result;
int builtin_result = 0;
while (read_result != -1 && builtin_result != -2)
{
custom_clear_info(info);
if (custom_interactive() == 0)
{
custom_output_string("$ ");
}
custom_error_character(BUFFER_FLUSH);
read_result = (ssize_t)custom_get_environ();
if (read_result != -1)
{
custom_clear_info(info);
builtin_result = find_custom_builtin(info);
if (builtin_result == -1)
{
find_command(info);
}
}
else if (custom_interactive() == 0)
{
custom_clean_info(info);
}
custom_write_history();
custom_clean_up_info(info);
if (!custom_interactive() && info->execution_status)
{
exit(info->execution_status);
}
if (builtin_result == -2)
{
if (info->execution_status == -1)
{
exit(info->execution_status);
}
exit(info->error_number);
}
}
return (builtin_result);
}
/**
* find_custom_builtin - searches for a built-in command int the custom shell
* @info: the custom shell information struct
* Return: -1 if built-in not found, 0 if built-in executed successfully.
* 1 if builtin-in found but not successful, 2 if built-in signals exit().
*/
int find_custom_builtin(info_t *info)
{
int i;
int built_in_result = -1;
MyBuiltinTable custom_builtin_table[] = {
{"exit", "exit", (void (*)(void))custom_exit_function, NULL},
{"env", "env", (void (*)(void))custom_environment_function, NULL},
{"help", "help", (void (*)(void))custom_help_function, NULL},
{"history", "history", NULL, NULL},
{"setenv", "setenv", (void (*)(void))custom_set_environment_variable_function, NULL},
{"unsetenv", "unsetenv", (void (*)(void))custom_unset_environment_variable_function, NULL},
{"cd", "cd", (void (*)(void))custom_change_directory_function, NULL},
{"alias", "alias", (void (*)(void))custom_alias_function, NULL},
{NULL, NULL, NULL, NULL}
};
for (i = 0; custom_builtin_table[i].command_name != NULL; i++)
{
if (strcmp(info->arg_values[0], custom_builtin_table[i].command_name) == 0)
{
info->line_count++;
if (custom_builtin_table[i].function_void != NULL)
{
custom_builtin_table[i].function_void();
}
else if (custom_builtin_table[i].function_int != NULL)
{
built_in_result = custom_builtin_table[i].function_int(info);
}
break;
}
}
return (built_in_result);
}
/**
* find_command - searches for a custom shell command in the PATH.
* @info:the custom shell information struct.
* Return: 1 if the command is found, 0 otherwise.
*/
char *find_command(info_t *info)
{
char *path = NULL;
int i, k;
if (info->count_lines == 1)
{
info->line_count++;
info->count_lines = 0;
}
k = 0;
for (i = 0; info->arguments[i]; i++)
{
if (!custom_is_delimiter(info->arguments[i], " \t\n"))
{
k++;
}
}
if (k == 0)
{
return (NULL);
}
path = find_command(info);
if (path)
{
return (path);
}
else
{
info->execution_status = 127;
custom_print_error(info, "not found\n");
return (NULL);
}
}
/**
* custom_execute_command - Forks a child process to execute a custom shell command.
* @info: The custom shell information struct.
*/
void custom_execute_command(info_t *info)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
perror ("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->command_path, info->arg_values, custom_get_environ()) == -1)
{
custom_clean_up_info(info);
if (errno == EACCES)
{
exit(126);
}
exit(1);
}
}
else
{
write(STDOUT_FILENO, &info->execution_status, sizeof(info->execution_status));
if (WIFEXITED(info->execution_status))
{
info->execution_status = WEXITSTATUS(info->execution_status);
if (info->execution_status == 126)
{
custom_print_error(info, "permission denied\n");
}
}
}
}
/**
 * main - entry point
 * Return: Always 0
 */
int main(void)
{
info_t info;
custom_clear_info(&info);
if (custom_interactive())
{
custom_output_string("$ ");
}
custom_error_character(BUFFER_FLUSH);
return (0);
}
/**
 * custom_hello - prnts a custom greeting message.
 */
void custom_hello(void)
{
printf("Hello from the custom function!\n");
}
/**
 * custom_clear_info - Clears and resets the information in the info structure.
 * @info: pointer to the info structure.
 */
void custom_clear_info(info_t *info)
{
if (info != NULL)
{
info->error_number = 0;
if (info->arguments)
{
info->arguments = NULL;
}
}
}
/**
 * custom_get_environ - Retrieves environment variables.
 * Return: double pointer to character arrays representing environment variables.
 */
char **custom_get_environ(void)
{
char **env_vars;
char **environ_copy = environ;
int env_count = 0;
int i;
while (environ_copy[env_count] != NULL)
{
env_count++;
}
env_vars = malloc((env_count + 1) * sizeof(char *));
if (env_vars == NULL)
{
return (NULL);
}
for (i = 0; i < env_count; i++)
{
env_vars[i] = strdup(environ_copy[i]);
if (env_vars[i] == NULL)
{
return (NULL);
}
}
env_vars[env_count] = NULL;
return (env_vars);
}
/**
 * custom_clean info - Cleans up and frees resources in the info structure.
 * @info: pointer to the infostructure.
 */
void custom_clean_info(info_t *info)
{
int i;
if (info != NULL)
{
info->error_number = 0;
if (info->arguments != NULL)
{
for (i = 0; info->arguments[i] != NULL; i++)
{
free(info->arguments[i]);
}
free(info->arguments);
info->arguments = NULL;
}
}
}
/**
 * custom_print_error - print an error message to stderr
 * @info: a pointer to the 'info_t' structuure containing information about the command.
 * @message: a string representing the specific error message.
 */
void custom_print_error(info_t *info, const char *message)
{
fprintf(stderr, "Error: %s - %s\n", info->command_path, message);
}
/**
 * _getEnvironmentVariable - Retrieves the value of an environment variable.
 * @varname: the name of the environment variable to retrieve
 * @envp: the array of environment variables
 * Returns: a pointer to the value of the environment variable if found. NULL if the variable
 * is not found in the environment.
 */
char *_getEnvironmentVariable(const char *varname, char **envp)
{
int i;
for (i = 0; envp[i] != NULL; i++)
{
if (strncmp(envp[i], varname, strlen(varname)) == 0)
{
char* value = strchr(envp[i], '=');
if (value != NULL)
{
value++;
return (value);
}
}
}
return (NULL);
}
/**
 * custom_is_delimiter - Checks if a character is a delimiter.
 * @character: The character to check.
 * @delimiters: a string containing the list of delimiters.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int custom_is_delimiter(char *character, const char *delimiters)
{
if (!delimiters || !*delimiters)
return (0);
while (*delimiters)
{
if (*character == *delimiters)
return (1);
delimiters++;
}
return (0);
}
/**custom_exit_function - Exits the custom shell
 */
void custom_exit_function(void)
{
exit(0);
}
/**
 * custom_environment_function - Displays environment variables
 */
void custom_environment_function(void)
{
char **env;
extern char **environ;
for (env = environ; *env; ++env)
{
puts(*env);
}
}
/**
 * custom_help_function - Displays help message for the custom shell
 */
void custom_help_function(void)
{
printf("Custom Shell Help:\n");
printf("Available Commands:\n");
printf("1. exit - Exit the shell.\n");
printf("2. env - Display environment variables.\n");
printf("3. help - Show this help message.\n");
}
/**
 * custom_set_environmnt_variable_function - Implements a custom function to set environment variables.
 * @info: pointer to the custom shell information struct.
 */
void custom_set_environment_variable_function(info_t *info)
{
(void)info;
printf("This is the setenv function.\n");
}
/**
 * custom_unset_environment_variable_function - implements a acustom function to unset environment variables.
 * @info: pointer to the custom shell information struct.
 */
void custom_unset_environment_variable_function(info_t *info)
{
(void)info;
printf("This is the unsetenv function.\n");
}
/**
 * custom_change_directory_function - Implements a custom function to change the current working directory.
 * @info: pointer to the custom shell information struct.
 */
void custom_change_directory_function(info_t *info)
{
(void)info;
printf("This is the cd function.\n");
}
/**
 * custom_alias_function - implements a custom function to handle alias function to hanndle alias commands.
 * @info: pointer to the custom shell information struct.
 */
void custom_alias_function(info_t *info)
{
(void)info;
printf("This is the alias function.\n");
}
/**
 * custom_interactive - implements interactive behaviour.
 * Return: 0 on successs, -1 on failure.
 */
int custom_interactive(void)
{
char input[256];
printf("CustomShell> ");
if (fgets(input, sizeof(input), stdin) == NULL)
{
return (-1);
}
printf("You entered: %s", input);
return (0);
}
/**
 * custom_output_string - outputs a string to the standard output.
 * @str: the string to be displayed.
 */
void custom_output_string(const char *str)
{
printf("%s", str);
}
/**
 * custom_error_character - outputs an error character to the standard error
 * @c: the error character to be displayed.
 */
void custom_error_character(char c)
{
fprintf(stderr, "Error: %c\n", c);
}
/**
 * custom_write_history - writes command history to a file.
 */
void custom_write_history(void)
{
FILE *history_file = fopen("history.txt", "a");
if (history_file != NULL)
{
fprintf(history_file, "Sample command entered\n");
fclose(history_file);
}
else
{
fprintf(stderr, "Error: Unable to open history file for writing\n");
}
}
/**
 * custom_clean_up_info  - Ckeans up resources associated with the custom hell information
 * @info: pointer to the custom shell information.
 */
void custom_clean_up_info(info_t *info)
{
int i;
if (info->arg_values != NULL)
{
for (i = 0; i < info->arg_count; i++)
{
free(info->arg_values[i]);
}
free(info->arg_values);
}
info->arg_count = 0;
}
