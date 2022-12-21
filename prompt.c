#include "main.h"
/**
 * prompt - prompt the user for the command
 * @env: linked list of the environment variables
 */
void prompt(char *env[])
{
char **cmds_arr;
int n = 0;
list_t *env_list;
env_list = array_to_linked_list(env);
while (1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "$ ", 2);
else
non_interactive(env, env_list);
signal(SIGINT, ctrl_c);
cmds_arr = get_cmd(env_list);
if (cmds_arr == NULL)
continue;
execute_cmds(cmds_arr, env, &n, env_list);
}
}
/**
 * ctrl_c - handle ctrl c signal
 * @n: value coming for the signal  function
 */
void ctrl_c(int n __attribute__((unused)))
{
write(STDOUT_FILENO, "\n$ ", 3);
}
/**
 * ctrl_d - handle ctrl d signal
 * @nread: number of charater read by _getline
 * @env: linked list of environment
 * @cmd: command
 */
void ctrl_d(int nread, char *cmd, list_t *env_list)
{
if (nread == 0)
{
free(cmd);
free_list(env_list);
if (isatty(STDIN_FILENO))
{
write(STDOUT_FILENO, "\n", 1);
}
exit(0);
}
}
