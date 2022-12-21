#include "main.h"
/**
 * __execve - execute command
 * @cmd: array containing the command and it's arguments
 * @env: linked list of the environment variables
 * @cmd_num: the command number
 * Return: 0
 */
int __execve(char **cmd, list_t *env, int cmd_num)
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
else if (execve(path, cmd, environ) == -1)
{
return (-1);
}
return (0);
}

/**
 * builtins - execute builtins commands
 * @cmd: array containing the command and it's arguments
 * @env: linked list of the environment variables
 * @cmd_num: the command number
 * Return: 0
 */
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
_setenv(cmd, env);
}
else if (_strcmp(cmd[0], "unsetenv") == 0)
{
_unsetenv(cmd, env);
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
/**
 * non_interactive - handle non_interactive mode
 * @env: linked list of the environment variables
 */
void non_interactive(list_t *env)
{
char **cmds;
int n = 0, exit_st;
cmds = get_cmd(env);
exit_st = execute_cmds(cmds, env, &n);
free_list(env);
exit(exit_st);
}
/**
 *execute_cmds - execute builtins commands
* @cmds: array containing the commands
* @env: linked list of the environment variables
* @cmd_num: the command number
* Return: 0
*/
int execute_cmds(char **cmds, list_t *env, int *cmd_num)
{
char **cmd;
int i = 0, exit_st = 0;
while (cmds[i] != NULL)
{
*cmd_num = *cmd_num + 1;
cmd = _strtok(cmd, cmds[i], " ");
if (cmd[0] != NULL)
{
exit_st = __execve(cmd, env, *cmd_num);
}
free_double_ptr(cmd);
i++;
}
free_double_ptr(cmds);
return (exit_st);
}
