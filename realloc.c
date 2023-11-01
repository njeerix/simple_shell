#include "shell.h"
/**
* my_memset - fills memory with a constant byte
* @dest: the pointer ro the memory area
* @value: the byte to fill *dest with
* @size: the number of bytes to fill
* Return: a pointer to the memory area dest
*/
char *my_memset(char *dest, char value, size_t size)
{
size_t i;
for (i = 0; i < size; i++)
{
dest[i] = value;
}
return (dest);
}
/**
* free_string_array - frees an array of strings
* @str_array: the array of strings to free
*/
void free_string_array(char **str_array)
{
char **p +str_array;
if (!str_array)
return;
while (*str_array)
{
free(*str_array++);
}
free(p);
}
/**
* my_realloc - reallocates a block of memory
* @ptr: pointer to the previously allocated block
* @old_size: byte size of the previous block
* @new_size: byte size of the new block
* Return: pointer to the reallocated block
*/
void *my_realloc(void *ptr, size_t old_size, size_t new_size)
{
char *new_ptr;
if (!ptr)
{
return (malloc(new_size));
}
if (!new_size)
{
free(ptr);
return (NULL);
}
if (new_size == old_size)
{
return (ptr);
}
new_ptr = malloc(new_size);
if (!new_ptr)
{
return (NULL);
}
size_t min_size = old_size < new_size ? old_size : new_size;
my_memset(new_ptr, 0, new_size);
for (size_t i = 0; i < min_size; i++)
{
new_ptr[i] = ((char *)ptr)[i];
}
free(ptr);
return (new_ptr);
}
