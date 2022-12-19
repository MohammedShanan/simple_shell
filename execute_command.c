#include "main.h"
/**
 * __execve - execute commands
 * @cmd: array containing the command and it's arguments
 * @env: linked list of the environment variables
 * @num: the command number
 * Return: 0
 */
int __execve(char **cmd, list_t *env, int cmd_num UNUSED)
{
char *path;
int is_builtin;
is_builtin = builtins(cmd, env, cmd_num);
if (is_builtin)
{
return (0);
}
path = get_cmd_path(cmd, env);
if (path == NULL)
{
return (-1);
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

/**
 * builtins - execute builtins commands
 * @cmd: array containing the command and it's arguments
 * @env: linked list of the environment variables
 * @num: the command number
 * Return: 0
 */
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
/**
 * non_interactive - handle non_interactive mode
 * @env: linked list of the environment variables
 */
void non_interactive(list_t *env UNUSED)
{
return;
}
