#ifndef NODE_H
#define NODE_H
#define SIZE 256
/**
 * struct Node - Node structure for a simple linked list
 * @str: string data in the node
 * @next: pointer to the next node in the list
 */
typedef struct Node
{
char *data;
char command[SIZE];
char *str;
struct Node *next;
} Node;
#endif
