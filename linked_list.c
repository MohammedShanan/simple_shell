#include "main.h"
/**
 * array_to_linked_list - make and array into a liked list
 * @array: array to process
 * Return: the array content as a linked list
 */
list_t *array_to_linked_list(char *arr[])
{
int i = 0;
list_t *head = NULL;
while (arr[i] != NULL)
{
add_node_end(&head, arr[i]);
i++;
}
return (head);
}
/**
 * list_len - return number of nodes in linked list
 * @h: linked list
 * Return: number of nodes in linked list
 */

size_t list_len(const list_t *h)
{
unsigned int count = 0;
while (h)
{
h = h->next;
count++;
}
return (count);
}

/**
 * add_node_end - add node to end of linked list
 * @head: linked list
 * @str: data for new node
 * Return: address of new element, or NULL if failed
 */

list_t *add_node_end(list_t **head, char *str)
{
list_t *node;
list_t *last_node = NULL;
last_node = *head;
str = _strdup2(str);
if (str == NULL)
{
return (NULL);
}
node = malloc(sizeof(list_t));
if (node == NULL)
{
return (NULL);
}
node->str = str;
node->len = _strlen(node->str);
node->next = NULL;
if (*head == NULL)
{
*head = node;
}
else
{
while (last_node->next)
{
last_node = last_node->next;
}
last_node->next = node;
}
return (node);
}
/**
 * free_list - free linked list
 * @head: linked list
 */
void free_list(list_t *head)
{
list_t *tmp = NULL;
while (head)
{
tmp = head;
head = head->next;
free(tmp->str);
free(tmp);
}
}
