#ifndef SHELL_H
#define SHELL_H
extern char **environ;
#include <time.h>
#include <sys/types.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\n'
#define BUFFER_FLUSH 0
#define INFO_INIT { 0, '\0', 0, 0.0, NULL, NULL, NULL, 0, -1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, {NULL}, 0, 0, NULL, NULL, 0, 0, 0}
#define HISTORY_FILE "history.txt"
#define SIZE 256
/**
* struct history_s - structure to store command history.
* @command: the command string stored in the history.
* @timestamp: the timestamp when the command was executed.
*/
typedef struct history_s
{
char command[1024];
time_t timestamp;
} history_t;
/**
* struct list_s - As tructure for linked list elements.
* @str: the string (typically a malloc'ed string)
* @name: name associated with the list element (if applicable).
* @next: pointer to the next node in the linked list.
* @value: the value
*/
typedef struct list_s
{
char *str;
char *name;
char *value;
struct list_s *next;
} list_t;
/**
* struct info - a structure ro store shell information.
* @history: pointer to the command history data structure.
* @name: the name
* @age: the age
* @salary: the salary
* @env: Array of environment variables.
* @alias: linked list of aliases.
* @argv: array of command-line arguments.
* @argc: number of command_line arguments.
* @readfd: file descriptor for reading from a script.
* @str: string
* @arg: number of command_line
* @path: the path
*/
typedef struct info
{
struct info_t
{
int some_field;
char *name;
void *history;
} named_struct;
history_t *history;
char *name;
int age;
double salary;
char **env;
list_t *alias;
char **argv;
int argc;
int readfd;
char *str;
char *arg;
char *path;
char *executable_name;
char *command_buffer;
char **aliases;
char **environ;
int cmd_buf_type;
int status;
int exit_status;
char *arg_values[100];
int execution_status;
int error_number;
char **arguments;
char *command_path;
int count_lines;
int line_count;
int arg_count;
Node *command_history;
} info_t;
typedef struct
{
char *name;
char *command_name;
void (*function_void)(void);
int (*function_int)(info_t *);
} MyBuiltinTable;

int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);
int listHistory(info_t *info);
int removeAlias(info_t *info, char *str);
int createAlias(info_t *info, char *str);
int manageAlias(info_t *info);
int exitShell(info_t *info);
int changeDirectory(info_t *info);
int displayHelp(info_t *info);
void printErorString(const char *str);
int printErrorCharacter(char c);
int writeCharacterToFile(char c, int fd);
int printErrorStringToFile(const char *str, int fd);
int customAtoi(const char *s);
void printErrorMessage(info_t *info, const char *errorMsg);
void printDecimal(int fd, int num);
void removeComments(char *str);
void displayEnvironment(info_t *info);
void printCommandHistory(history_t *history);
void modifyEnvironmentVariable(const char *name, const char *value);
void removeEnvironmentVariable(const char *name);
char *_strncpy_custom(char *dest, const char *src, int n);
char *_strncat_custom(char *dest, const char *src, int n);
char *_strchr_custom(const char *s, char c);
void custom_sigintHandler(__attribute__((unused))int sig_num);
char *custom_strchr(const char *s, int c);
char *custom_strncat(char *dest, const char *src, size_t n);
char *custom_strncpy(char *dest, const char *src, size_t n);
void addNodeEnd(list_t **head, const char *str, int len);
void populateEnvironmentList(info_t *info);
int unsetEnvironmentVariable(info_t *info);
int setEnvironmentVariable(info_t *info);
char *findEnvironmentVariable(info_t *info, const char *name);
void displayEnvironment(info_t *info);
void printCommandHistory(history_t *history);
int deleteAlias(list_t **head, char *name);
int addAliasToEnd(list_t **head, char *str, char *value);
list_t *findAliasWithPrefix(list_t *head, char *prefix);
void printError(const char *message);
int _setEnvironmentVariable(const char *name, const char *value,
int overwrite);
int printSingleAlias(list_t *node);
int custom_setenv(info_t *info);
int custom_unsetenv(info_t *info, const char *var);
void release_info(info_t *info, int free_all);
void configure_info(info_t *info, char **av);
void initialize_info(info_t *info);
int renumber_history_entries(info_t *info);
int build_history_entry(info_t *info, char *command, int linecount);
int load_history(info_t *info);
int save_history(info_t *info);
char *generate_history_filename(info_t *info);
void free_list_nodes(list_t **list);
int remove_node_at_index(list_t *list, unsigned int index);
size_t print_list_strings(const list_t *list);
list_t *append_node(list_t **list, const char *data, int index);
list_t *prepend_node(list_t **list, const char *data, int index);
ssize_t get_index_of_node(list_t *head, list_t *node);
list_t *find_node_starts_with(list_t *list, char *prefix, char next_char);
size_t print_linked_list(const list_t *list);
char **list_to_array(list_t *list);
size_t list_length(const list_t *list);
int custom_main(int arg_count, char **arg_vector);
int custom_free(void **ptr);
char *copy_substring(char *source, int start, int stop);
int is_executable(info_t *info, char *filepath);
void *my_realloc(void *ptr, size_t old_size, size_t new_size);
void free_string_array(char **str_array);
char *my_memset(char *dest, char value, size_t size);
void custom_execute_command(info_t *info);
char *find_command(info_t *info);
int find_custom_builtin(info_t *info);
int custom_shell_loop(info_t *info);
char *custom_string_concatenate(char *destination, char *source);
char *custom_string_starts_with(const char *str, const char *prefix);
int custom_string_compare(char *str1, char *str2);
int custom_string_length(char *str);
void custom_flush_buffer(char *buf, int size);
int custom_character_print(char c);
void custom_string_print(const char *str);
char *custom_string_duplicate(const char *str);
char *custom_string_copy(char *dest, const char *src);
char **custom_string_split(char *str, const char *delimiters);
int custom_replace_string(char **old, char *new);
int custom_replaces_vars(info_t *info);
int custom_replaces_alias(info_t *info);
int custom_is_chain(info_t *info, char *buf, size_t *p);
char **split_arguments(char *input, const char *delimiter);
char *duplicate_string(const char *str);
void free_command_buffer(info_t *info);
void free_linked_list(struct Node **head_ref);
void replaces_variable(info_t *info);
void replace_aliases(info_t *info);
list_t *custom_node_starts_with(list_t *list, const char *str, char delimiter);
char *custom_convert_number(int value);
void custom_check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
list_t *custom_create_list_from_char_array(char **array);
int main(void);
int custom_interactive(void);
void custom_output_string(const char *str);
void custom_error_character(char c);
void custom_clear_info(info_t *info);
void custom_hello(void);
void custom_clean_info(info_t *info);
void custom_write_history(void);
void custom_clean_up_info(info_t *info);
char **custom_get_environ(void);
void custom_print_error(info_t *info, const char *message);
char *_getEnvironmentVariable(const char *varname __attribute__((unused)));
int custom_is_delimiter(char *character, const char *delimiters);
void custom_exit_function(void);
void custom_help_function(void);
void custom_environment_function(void);
void custom_set_environment_variable_function(info_t *info);
void custom_unset_environment_variable_function(info_t *info);
void custom_change_directory_function(info_t *info);
void custom_alias_function(info_t *info);
void custom_clean_up_info(info_t *info);
void custom_write_history(void);
void custom_error_character(char c);
void custom_output_string(const char *str);
int starts_with(const char *str, const char *prefix);
ssize_t _eputs(const char *str);
ssize_t _eputchar(char c);
void populate_new_history(info_t *shell_info);
void hsh(info_t *shell_info, char **arg_vector);
void populate_new_list(info_t *shell_info);
size_t _strlen(const char *s);
void AddCommandToHistory(info_t *shell_info, const char *command);
void populate_new_list(info_t *shell_info);
void hsh(info_t *shell_info, char **arg_vector);
void AddCommandToHistory(info_t *shell_info, const char *command);
void execute_command(info_t *shell_info, char **arg_vector);
void read_history(info_t *shell_info);
char *my_strdup(const char *str);
char **copy_environment(char **env);
int delete_node_at_index(list_t **list, unsigned int index);
void add_node_end(list_t **head, char *str, int overwrite);
char *create_env_string(const char *var, const char *value);
#endif
