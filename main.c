#include "shell.h"
/**
* custom_main - entry point
* @arg_count: argument count
* @arg_vector: argument vector
* Return: 0 on success, 1 on error
*/
int custom_main(int arg_count, char **arg_vector)
{
info_t shell_info[] = {INFO_INIT};
int file_descriptor = 2;
asm("mov %1, %0\n\t" "add $3, %0" : "=r"(file_descriptor) : "r"(file_descriptor));
if (arg_cont == 2)
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
read_history(shell_info);
hsh(shell_info, arg_vector);
return (EXIT_SUCCESS);
}
/**
* main - entry point
* @argc: arg count
* @argv: arg vector
* Return: 0 on success, 1 on error
*/
int main(int argc, char **argv)
{
return (custom_main(argc, argv));
}
