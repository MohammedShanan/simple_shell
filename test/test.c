#include "main.h"
void print_double_ptr(char **ptr);

int main(int argc UNUSED, char *argv[] UNUSED, char *env[])
{
    list_t *env_list;
    env_list = array_to_linked_list(env);
    prompt(env_list);
    return (0);
}
/*linked list--------------------------------------------------------------*/
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

/*helper 1----------------------------------------------------------------*/
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

/*helper 2----------------------------------------------------------------------------------*/
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

/*erro handling --------------------------------------------------*/
void cmd_not_found(char **cmd, list_t *env, int cmd_num)
{
    list_t *list;
    char **prog_name, *n;
    list = get_env("_", env);
    printf("Error\n");
    prog_name = _strtok(prog_name, list->str, "=");
    write(STDOUT_FILENO, prog_name[1], _strlen(prog_name[1]));
    write(STDOUT_FILENO, ": ", 2);
    n = num_to_str(cmd_num);
    write(STDOUT_FILENO, n, _strlen(n));
    free(n);
    write(STDOUT_FILENO, ": ", 2);
    write(STDOUT_FILENO, cmd[0], _strlen(cmd[0]));
    write(STDOUT_FILENO, ": ", 2);
    write(STDOUT_FILENO, "not found\n", 10);
    free_double_ptr(prog_name);
}
void illegal_number(char **cmd, list_t *env, int cmd_num)
{
    list_t *list;
    char **prog_name, *n;
    list = get_env("_", env);
    printf("Error\n");
    prog_name = _strtok(prog_name, list->str, "=");
    write(STDOUT_FILENO, prog_name[1], _strlen(prog_name[1]));
    write(STDOUT_FILENO, ": ", 2);
    n = num_to_str(cmd_num);
    write(STDOUT_FILENO, n, _strlen(n));
    free(n);
    write(STDOUT_FILENO, ": ", 2);
    write(STDOUT_FILENO, "exit: Illegal number: ", 22);
    write(STDOUT_FILENO, cmd[1], _strlen(cmd[1]));
    write(STDOUT_FILENO, "\n", 1);
}

/*get command*/

int _getline(char **buff, size_t *n, FILE *stream UNUSED)
{
    char *str;
    int nread;
    size_t len = 0, len_buff = *n, counter = 0;
    *buff = *n == 0 ? NULL : *buff;
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
        counter++;
        if (str[nread - 1] == '\n')
        {
            break;
        }
    }
    free(str);
    return (len);
}

char *get_cmd_path(char **cmd, list_t *env)
{
    char *pth = NULL;
    if (access(cmd[0], F_OK) == 0)
    {
        pth = malloc(_strlen(cmd[0]) + 1);
        pth = _strcpy(pth, cmd[0]);
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
    free(pth);
    return (NULL);
}

char **get_cmd(list_t *env)
{
    char *cmd = NULL, **arr = NULL;
    size_t n = 0;
    int nread;
    nread = _getline(&cmd, &n, STDIN_FILENO);
    ctrl_d(nread, env, cmd);
    remove_comments(cmd);
    arr = _strtok(arr, cmd, ";\n");
    printf("cmd is %s\n", cmd);
    free(cmd);
    if (arr[0] == NULL)
    {
        free_double_ptr(arr);
        return (NULL);
    }
    return (arr);
}
/*builtins ----------------------------------------------------*/
void _setenv(char **cmd, list_t *env, int cmd_num)
{
    char *str;
    list_t *var;
    int len_str;
    if (cmd[1] == NULL || cmd[2] == NULL)
    {
        write(STDERR_FILENO, "Too few arguments\n", 18);
        return;
    }
    len_str = _strlen(cmd[1]) + _strlen(cmd[2]) + 2;
    str = malloc(len_str);
    if (str == NULL)
    {
        return;
    }
    str = _strcpy(str, cmd[1]);
    str = _strcat(str, "=");
    str = _strcat(str, cmd[2]);
    var = get_env(cmd[1], env);
    if (var == NULL)
    {
        add_node_end(&env, str);
    }
    else
    {
        free(var->str);
        var->str = _strdup2(str);
    }
    free(str);
}
void _unsetenv(char **cmd, list_t *env, int cmd_num)
{
    char *str;
    list_t *var, *tmp;
    int len_str;
    if (cmd[1] == NULL)
    {
        write(STDERR_FILENO, "Too few arguments\n", 18);
        return;
    }
    var = get_env(cmd[1], env);
    while (env && var)
    {
        if (env->next != NULL)
        {
            if (env->next == var)
            {
                env->next = var->next;
                free(var->str);
                free(var);
                return;
            }
        }
        env = env->next;
    }
    write(STDERR_FILENO, "Cannot find variable\n", 21);
}

void _env(list_t *env)
{
    while (env)
    {
        write(STDOUT_FILENO, env->str, env->len);
        write(STDOUT_FILENO, "\n", 1);
        env = env->next;
    }
}

int __exit(char **cmd, list_t *env, int cmd_num)
{
    int exit_st;
    exit_st = cmd[1] != NULL ? c_to_num(cmd[1]) : 0;
    if (exit_st == -1)
    {
        illegal_number(cmd, env, cmd_num);
        return (1);
    }
    free_list(env);
    free_double_ptr(cmd);
    exit(exit_st);
}
/*execute command----------------------------------------*/


int __execve(char **cmd, list_t *env, int cmd_num UNUSED)
{
    char *path;
    if (builtins(cmd, env, cmd_num))
    {
        return (0);
    }
    path = get_cmd_path(cmd, env);
    if (path == NULL)
    {
        cmd_not_found(cmd, env, cmd_num);
        return (127);
    }
    if (fork() != 0)
    {
        wait(NULL);
        free(path);
    }
    else if (execve(path, cmd, NULL) == -1)
    {
        return (-1);
    }
    return (0);
}

int builtins(char **cmd, list_t *env, int cmd_num)
{
    int exit_status = 1;
    if (_strcmp(cmd[0], "exit") == 0)
    {
        exit_status = __exit(cmd, env, cmd_num);
    }
    else if (_strcmp(cmd[0], "env") == 0)
    {
        _env(env);
    }
    else if (_strcmp(cmd[0], "setenv") == 0)
    {
        _setenv(cmd, env, cmd_num);
    }
    else if (_strcmp(cmd[0], "unsetenv") == 0)
    {
        _unsetenv(cmd, env, cmd_num);
    }
    else if (_strcmp(cmd[0], "cd") == 0)
    {
        _env(env);
    }
    else
    {
        return (0);
    }
    return (exit_status);
}
void non_interactive(list_t *env)
{
    char **cmds;
    int n = 0, exit_st;
    cmds = get_cmd(env);
    exit_st = execute_cmds(cmds, env, &n);
    free_list(env);
    exit(exit_st);
}
int execute_cmds(char **cmds, list_t *env, int *cmd_num)
{
    char **cmd;
    int i = 0;
    while (cmds[i] != NULL)
    {
        print_double_ptr(cmds);
        cmd = _strtok(cmd, cmds[i], " ");
        if (cmd[0] != NULL)
        {
            __execve(cmd, env, *cmd_num);
        }
        print_double_ptr(cmd);
        free_double_ptr(cmd);
        i++;
        *cmd_num = *cmd_num + 1;
    }
    free_double_ptr(cmds);
}
/* helper 3--------------------------------------*/

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

list_t *get_env(char *var, list_t *env)
{
    int i = 0;
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
char *num_to_str(int n)
{
    int digit, i = 0, len_n = 1;
    char *s;
    double tens = 1;
    while (tens * 10 <= n)
    {
        tens *= 10;
        len_n++;
    }
    s = malloc(len_n + 1);
    if (s == NULL)
    {
        return (NULL);
    }
    while (tens >= 1)
    {
        digit = n / tens;
        s[i] = digit + '0';
        n = (n - (tens * digit));
        tens /= 10;
        i++;
    }
    s[i] = '\0';
    return (s);
}

void remove_comments(char *cmd)
{
    int i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '#')
        {
            if (i == 0)
            {
                cmd[0] = '\0';
                break;
            }
            else
            {
                if (cmd[i - 1] == ' ')
                {
                    cmd[i - 1] = '\0';
                    break;
                }
            }
        }
        i++;
    }
}
char **_strtok(char **arr, char *str, const char *delim)
{
    int i, j, len, indx, len_str;
    i = j = len = indx = 0;
    len_str = _strlen(str);
    arr = malloc(sizeof(char *) * 1024);
    while (i <= len_str)
    {
        if (is_c_in_str(str[i], delim) || str[i] == '\0')
        {
            if (len != 0)
            {
                arr[j] = malloc(len + 1);
                if (arr[j] == NULL)
                {
                    free_double_ptr(arr);
                }
                arr[j] = _strncpy(arr[j], str, len, indx);
                j++;
            }
            indx += len + 1;
            len = 0, i++;
            continue;
        }
        len++, i++;
    }
    arr[j] = NULL;
    return (arr);
}

/* unknown ----------------------*/
void prompt(list_t *env)
{
    char **cmds_arr;
    int n = 0;
    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);
        else
            non_interactive(env);
        signal(SIGINT, ctrl_c);
        cmds_arr = get_cmd(env);
        if (cmds_arr == NULL)
            continue;
        execute_cmds(cmds_arr, env, &n);
    }
}
void ctrl_c(int n __attribute__((unused)))
{
    write(STDOUT_FILENO, "\n$ ", 3);
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





void print_double_ptr(char **ptr)
{
    int i = 0;
    while (ptr[i] != NULL)
    {
        printf("%s--", ptr[i]);
        i++;
    }
    printf("\n");
}

