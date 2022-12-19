#include "main.h"
int _strlen(char *s)
{
int len;
len = 0;
if (s == NULL)
{
return (0);
}
while (*s)
{
len++;
s++;
}
return (len);
}

char *_strdup2(char *str)
{
char *new_str;
int size;
if (str == NULL)
{
return (NULL);
}
size = _strlen(str) + 1;
new_str = (char *)malloc(size);
if (new_str == NULL)
{
return (NULL);
}
return (_strcpy(new_str, str));
}
char *_strcpy(char *dest, char *src)
{
int i;

for (i = 0; src[i]; i++)
{
dest[i] = src[i];
}
dest[i] = '\0';
return (dest);
}

int is_c_in_str(char c, const char *str)
{
int i = 0;
while (str[i])
{
if (str[i] == c)
{
return (1);
}
i++;
}
return (0);
}
void free_double_ptr(char **ptr)
{
int i = 0;
while (ptr[i] != NULL)
{
free(ptr[i]);
i++;
}
free(ptr);
}

char *_strncpy(char *dest, char *src, int n, int indx)
{
int i;
i = 0;
while (i < n)
{
dest[i] = src[indx];
i++, indx++;
}
dest[i] = '\0';
return (dest);
}

list_t *to_linked_list(char *env[])
{
int i = 0;
list_t *head;
head = NULL;
while (env[i] != NULL)
{
add_node_end(&head, env[i]);
i++;
}
return (head);
}

char *_strcat(char *dest, char *src, int len_dest)
{
int i;
i = len_dest;
while (*src)
{
*(dest + i) = *src;
i++, src++;
}
*(dest + i) = '\0';
return (dest);
}