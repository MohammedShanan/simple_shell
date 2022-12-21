#include "main.h"
/**
 * __execve - execute command
 * @cmd: array containing the command and it's arguments
 * @env: linked list of the environment variables
 * @cmd_num: the command number
 * Return: 0
 */
int __execve(char **cmd, char *env[], int cmd_num, list_t *env_list)
{
char *path;
if (builtins(cmd, env_list, cmd_num))
{
return (0);
}
path = get_cmd_path(cmd, env_list);
if (path == NULL)
{
cmd_not_found(cmd, env_list, cmd_num);
return (127);
}
if (fork() != 0)
{
wait(NULL);
free(path);
}
else if (execve(path, cmd, env) == -1)
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
printf("here 0");
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
printf("here 1");
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
void non_interactive(char *env[], list_t *env_list)
{
char **cmds;
int n = 0, exit_st;
cmds = get_cmd();
exit_st = execute_cmds(cmds, env, &n, env_list);
exit(exit_st);
}
/**
 *execute_cmds - execute builtins commands
* @cmds: array containing the commands
* @env: linked list of the environment variables
* @cmd_num: the command number
* Return: 0
*/
int execute_cmds(char **cmds, char *env[], int *cmd_num, list_t *env_list)
{
char **cmd;
int i = 0, exit_st = 0;
while (cmds[i] != NULL)
{
*cmd_num = *cmd_num + 1;
cmd = _strtok(cmd, cmds[i], " ");
if (cmd[0] != NULL)
{
    exit_st = __execve(cmd, env, *cmd_num, env_list);
}
free_double_ptr(cmd);
i++;
}
free_double_ptr(cmds);
return (exit_st);
}
