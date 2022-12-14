#include "main.h"
/**
 * _strcat - concatenate two strings
 * @dest: string to be appended to
 * @src: string to append
 * Return: concatenated string
 */

char *_strcat(char *dest, char *src)
{
int i, j = 0;
i = _strlen(dest);
while (src[j])
{
*(dest + i) = src[j];
i++, j++;
}
*(dest + i) = '\0';
return (dest);
}
/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: length
 */

int _strlen(char *s)
{
int len;
len = 0;
if (s == NULL)
{
return (0);
}
while (s[len])
{
len++;
}
return (len);
}
/**
 * _strcpy - copies the string pointed to by src,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest
 * @dest: copy source to this buffer
 * @src: this is the source to copy
 * Return: copy of original source
 */

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

/**
 * _strdup2 - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 * @str: string to duplicate
 * Return: pointer to duplicated string in allocated memory
 */

char *_strdup2(char *str)
{
char *new_str;
int size;
if (str == NULL)
{
return (NULL);
}
size = _strlen(str) + 1;
new_str = malloc(size);
if (new_str == NULL)
{
return (NULL);
}
return (_strcpy(new_str, str));
}

/**
 * _strcmp - compare two strings
 * @s1: one string
 * @s2: one string
 * Return: int that tells num spaces in between
 */

int _strcmp(char *s1, char *s2)
{
while (*s1 || *s2)
{
if (*s1 != *s2)
{
return (*s1 - *s2);
}
s1++, s2++;
}
return (0);
}
