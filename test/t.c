#include "main.h"
#include "test.h"
/** * main - execve example * * Return: Always 0. */
int main(int argc, char *argv[], char *env[])
{
    list_t *env_list;
    char **arr;
    char *tmp;
    char **cmd;
    cmd = malloc(sizeof(command));
    env_list = to_linked_list(env);
    tmp = which("ls", env_list);
    arr = _strtok(arr, "ls  -l\n", " \n");
    cmd->cmd = arr;
    cmd->cmd_num = 0;
    cmd->exit_st = 0;
    __execve(cmd, env_list);
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
char **_strtok(char **arr, char *str, const char *delim)
{
    int i, j, len, indx;
    i = j = len = indx = 0;
    char *_str;
    char s;
    arr = malloc(sizeof(char *) * 1024);
    while (str[i])
    {
        s = str[i];
        if (is_c_in_str(str[i], delim))
        {
            if (len != 0)
            {
                arr[j] = malloc(len + 1);
                if (arr[j] == NULL)
                {
                    free_double_ptr(arr);
                }
                arr[j] = _strncpy(arr[j], str, len, indx);
                _str = arr[j];
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
char *get_cmd_path(char **cmd, list_t *env)
{
    int access_st;
    char *pth, *tmp;
    access_st = access(cmd->cmd[0], F_OK);
    pth = malloc(1024);
    if (pth == NULL)
    {
        return (NULL);
    }
    if (access_st == 0)
    {
        pth = _strcpy(pth, cmd->cmd[0]);
        return (pth);
    }
    else
    {
        tmp = which(cmd->cmd[0], env);
        if (tmp != NULL)
        {
            pth = _strcpy(pth, tmp);
            free(tmp);
        }
        else
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

int __execve(char **cmd, list_t *env)
{
    char path[1024], *tmp;
    _strcpy(path, which(cmd->cmd[0], env));
    if (path == NULL)
    {
        return (0);
    }
    if (execve(path, cmd->cmd, NULL) == -1)
    {
        perror("Error:");
        return (-1);
    }
    return (0);
}

char *which(char *exe, list_t *env)
{
    list_t *pth;
    char **pth_arr;
    char *tmp;
    int i = 1;
    pth = get_env("PATH", env);
    pth_arr = _strtok(pth_arr, pth->str, ";");
    while (pth_arr[i] != NULL)
    {
        tmp = _strdup2(pth_arr[i]);
        tmp = _strcat(tmp, "\\", _strlen(tmp));
        tmp = _strcat(tmp, exe, _strlen(tmp));
        printf("%s\n", tmp);
        if (access(tmp, F_OK) == 0)
        {
            free_double_ptr(pth_arr);
            return (tmp);
        }
        i++;
    }
    return (NULL);
}
