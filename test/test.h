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

char *_strcat(char *dest, char *src)
{
    int i;
    i = _strlen(dest);
    while (*src)
    {
        *(dest + i) = *src;
        i++, src++;
    }
    *(dest + i) = '\0';
    return (dest);
}
char *get_cmd_path(char **cmd, list_t *env)
{
    char *pth = NULL;
    if (access(cmd[0], F_OK) == 0)
    {
        pth = _strcpy(pth, cmd[0]);
        return (pth);
    }
    else
    {
        pth = which(cmd[0], env);
        if (pth == NULL)
        {
            return (NULL);
        }
    }
    if (access(pth, X_OK) == 0)
    {
        return (pth);
    }
    return (NULL);
}
char *which(char *exe, list_t *env)
{
    list_t *pth;
    char **pth_arr, *tmp;
    int i = 1;
    pth = get_env("PATH", env);
    pth_arr = _strtok(pth_arr, pth->str, "=:");
    tmp = malloc(1024);
    while (pth_arr[i] != NULL)
    {
        printf("%s\n", pth_arr[i]);
        tmp = _strcpy(tmp, pth_arr[i]);
        tmp = _strcat(tmp, "/");
        tmp = _strcat(tmp, exe);
        if (access(tmp, F_OK) == 0)
        {
            free_double_ptr(pth_arr);
            return (tmp);
        }
        i++;
    }
    free(tmp);
    free_double_ptr(pth_arr);
    return (NULL);
}

list_t *add_node_end(list_t **head, char *str)
{
    list_t *node;
    list_t *last_node = NULL;
    last_node = *head;
    if (str == NULL)
    {
        return (NULL);
    }
    if (_strdup2(str) == NULL)
    {
        return (NULL);
    }
    node = malloc(sizeof(list_t));
    if (node == NULL)
    {
        return (NULL);
    }
    node->str = _strdup2(str);
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
void _env(list_t *env)
{
    list_t *tmp = NULL;
    tmp = env;
    while (tmp)
    {
        printf("%s\n", tmp->str);
        tmp = tmp->next;
    }
}

list_t *get_env(char *var, list_t *env)
{
    int i = 0, len_val;
    list_t *value;
    while (env != NULL)
    {
        while (var[i] == env->str[i])
        {
            i++;
        }
        if (var[i] == '\0' && env->str[i] == '=')
        {
            break;
        }
        i = 0;
        env = env->next;
    }
    if (env == NULL)
    {
        return (NULL);
    }
    value = env;
    return (value);
}

void ctrl_d(int nread, list_t *env, char *cmd)
{
    if (nread == 0)
    {
        free_list(env);
        free(cmd);
        if (isatty(STDIN_FILENO))
        {
            write(STDOUT_FILENO, "\n", 1);
        }
        exit(0);
    }
}
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

int _getline(char **buff, size_t *n, FILE *stream UNUSED)
{
    char *str;
    int nread;
    size_t len = 0, len_buff = _strlen(*buff);
    str = malloc(1025);
    if (str == NULL)
    {
        return (-1);
    }
    while (1)
    {
        nread = read(STDIN_FILENO, str, 1024);
        if (nread <= 0)
        {
            free(str);
            return (0);
        }
        len += nread, len_buff += nread;
        str[nread] = '\0';
        if (len_buff > *n)
        {
            *buff = _realloc(*buff, *n, len_buff + 1);
        }
        *buff = *n == 0 ? _strcpy(*buff, str) : _strcat(*buff, str);
        *n = len_buff;
        if (str[nread - 1] == '\n')
        {
            break;
        }
    }
    free(str);
    return (len);
}

int __exit(char **cmd, list_t *env)
{
    int exit_st;
    exit_st = cmd[1] != NULL ? c_to_num(cmd[1]) : 0;
    if (exit_st == -1)
    {
        return (1);
    }
    free_list(env);
    free_double_ptr(cmd);
    exit(exit_st);
}

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