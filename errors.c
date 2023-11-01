#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#ifndef FLUSH_BUFFER
#define FLUSH_BUFFER 0
#endif
/**
* printErrorString - Prints an error message string to stderr.
* @str: The error message string to be printed.
* Return: Nothing.
*/
void printErrorString(const char *str)
{
if (!str)
return;
fprintf(stderr, "%s", str);
}
/**
* printErrorCharacter - Writes a character to stderr.
* @c: The character to print.
* Return: On success, 1.
* On error, -1 id returned, and errno is set appropriately.
*/
int printErrorCharacter(char c)
{
if (c == FLUSH_BUFFER || ferror(stderr))
{
fflush(stderr);
}
return (fputc(c, stderr));
}
/**
* writeCharacterToFile - Writes a character to the specifies file decsriptor.
* @c: The character to write.
* @fd: The file descriptor to write to.
* Return: On success, 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int writeCharacterToFile(char c, int fd)
{
if (c == FLUSH_BUFFER || fd < 0 || fd > 2 || ferror(stdout))
{
fflush(stdout);
}
return (write(fd, &c, 1));
}
/**
* printErrorStringToFile - Writes an error message string to the
* specified file descriptor.
* @str: The error message string to be written.
* @fd: The file descriptor to write tp/
* Return: The numbe rof characters written.
*/
int printErrorStringToFile(const char *str, int fd)
{
int charsWritten = 0;
if (!str)
return (0);
while (*str)
{
if (writeCharacterToFile(*str++, fd) != -1)
charsWritten++;
else
return (-1);
}
return (charsWritten);
}
