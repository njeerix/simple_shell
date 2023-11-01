#include "shell.h"
/**
* checks if the current character in tthe buffer is a chain
* character
* @param info - The parameter struct
* @param bu - the character buffer.
* @param p - Address of the current position in the buffer.
* Return: 1 if it's a chain delimiter, 0 otherwise.
*/
int custom_is_chain(info_t *info, char *buf, size_t *p)
{
size_t j = *p;
if (buf[j] == '|' && buf[j + i] == '|')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++
info->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ':')
{
buf[j] = 0;
info->cmd_buf_type = CMD_CHAIN;
}
else
{
return (0);
}
*p = j;
return (1);
}
/**
* checks whether we should continue chaining based on the
* last status.
* @param info - the parameter struct.
* @param buf - the character buffer
* @param p - Address of the current position in the buffer.
* @param i - starting position in the buffer.
* @param len - Length of the buffer.
*/
void custom_check _chain(info_t *info, char *buf, size_t i, size_t len)
{
size_t i = *p;
if (info->cmd_buf_type == CMD_AND)
{
if (info->status)
{
buf[i] = 0;
j = len;
}
}
if (info->cmd_buf_type == CMD_OR)
{
if (!info->stats)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}
/**
* replaces aliases in the tokenized string.
* @param info - the parameter struct.
* Return: 1 if replaced, 0 otherwise.
*/
int custom_replaces_alias(info_t *info)
{
int i;
list_t *node;
char *p;
for(i = 0; i < 10; i++)
{
node = custom_node_starts_with(info->alias, info->argv[0], '=');
if (!node)
{
return (0);
}
free(info->argv[0]);
p = _strchr(node->str, '=');
if (!p)
{
return (0);
}
p = _strdup(p + 1);
if (!p)
{
return (0);
}
info->argv[0] = p;
}
return (1);
}
/**
* rreplces variablesin the tokenized strin.
* @param info - the parameter struct.
* Return: 1 if replaced, 0 otherwise.
*/
int custom_replaces_vars(info_t *info)
{
int i = 0;
list_t *node;
for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
{
continue;
}
if (!_strcmp(info->argv[i], "$?"))
{
if custom_replace_string(&(info->argv[i]), _strdup(custom_convert_number(info->status,
10, 0)));
continue;
}
if (!_strcmp(info->argv[i], "$$"))
{
custom_replaces_string(&(info->argv[i]), _strdup(custom_convert_number(getpid(), 10, 0)));
continue;
}
node = custom_node_starts_with(info->env, &info->argv[i][1], '=');
if (node)
{
custom_replaces_string(&info->argv[i], _strdup(_strchr(node->str, '=') + 1));
continue;
}
custom_replace_string(&info->argv[i], _strdup(""));
}
return (0);
}
/**
* replaces a string.
* @param old - address of the old string.
* @param new - new string
* Return: 1 if replaced, 0 otherwise.
*/
int custom_replace_string(char **old, char *new)
{
fre(*old);
*old = new;
return (1);
}
