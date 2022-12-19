#include "main.h"
/**
 * free_double_ptr - free double pointer
 * @ptr: pointer to be freed
 */
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


/**
 * _realloc - allocate memory and set all values to 0
 * @ptr: pointer to the memory previously allocated (malloc(old_size))
 * @old_size: size previously allocated
 * @new_size: new size to reallocate
 * Return: pointer to reallocated memory
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *p;
    unsigned int i;
    if (new_size == 0 && ptr != NULL)
    {
        free(ptr);
        return (NULL);
    }

    if (ptr == NULL)
    {
        p = malloc(new_size);
        if (p == NULL)
        {
            return (NULL);
        }

        return (p);
    }

    if (new_size == old_size)
    {
        return (ptr);
    }
    p = malloc(new_size);
    if (p == NULL)
    {
        return (NULL);
    }

    for (i = 0; i < old_size; i++)
    {
        *((char *)p + i) = *((char *)ptr + i);
    }
    free(ptr);
    return (p);
}
/**
 * is_c_in_str - find if the charater is in the string or  not
 * @c: char to look for
 * @str: string to search 
 * Return: 1 if c is found in str 0 if not
 */
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
/**
 * _strncpy - copy n bytes form src to dest
 * @dest: copy source to this buffer
 * @src: this is the source to copy
 * @n: number of bytes to copy
 * @indx: index to start coping from
 * Return: pointer to dest
 */
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
/**
 * get_num - convert number from sting it int
 * @s: string
 * @indx: a pointer to the indx of the first digit of the number
 * Return: number as int
 */
int c_to_num(char *s)
{
    int i = 0, num = 0;
    while (s[i])
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            num *= 10;
            num += s[i] - '0';
        }
        else
        {
            return (-1);
        }
        i++;
    }
    return (num);
}