#include "main.h"
#include "test.h"
/** * main - execve example * * Return: Always 0. */
void print_double_ptr(char **ptr)
{
    int i = 0;
    while (ptr[i] != NULL)
    {
        printf("%s ", ptr[i]);
        i++;
    }
    printf("\n");
}
int execute_cmds(char **cmds, list_t *env, int cmd_num UNUSED);
int main(int argc, char *argv[], char *env[])
{
    list_t *env_list;
    char *tmp;
    char **arr;
    env_list = to_linked_list(env);
    printf("$ ");
    arr = get_cmd(env_list);
    execute_cmds(arr, env_list, 0);
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
        return (-1);
    }
    if (execve(path, cmd, NULL) == -1)
    {
        return (-1);
    }
    return (0);
}

char **get_cmd(list_t *env)
{
    char *cmd = NULL, **arr = NULL;
    size_t n = 0;
    int nread;
    nread = _getline(&cmd, &n, STDIN_FILENO);
    ctrl_d(nread, env, cmd);
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

int execute_cmds(char **cmds, list_t *env, int cmd_num UNUSED)
{
    char **cmd;
    while (1)
    {
        print_double_ptr(cmds);
        cmd = _strtok(cmd, cmds[], " ");
        print_double_ptr(cmd);
        __execve(cmd, env, cmd_num);
        free_double_ptr(cmd);
    }
}

int builtins(char **cmd, list_t *env, int cmd_num UNUSED)
{
    int exit_status UNUSED;
    if (_strcmp(cmd[0], "exit") == 0)
    {
        exit_status = __exit(cmd, env);
    }
    else if (_strcmp(cmd[0], "env") == 0)
    {
        _env(env);
    }
    else if (_strcmp(cmd[0], "setenv") == 0)
    {
        _env(env);
    }
    else if (_strcmp(cmd[0], "unsetenv") == 0)
    {
        _env(env);
    }
    else if (_strcmp(cmd[0], "cd") == 0)
    {
        _env(env);
    }
    else
    {
        return (0);
    }
    return (1);
}