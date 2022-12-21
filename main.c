#include "main.h"
/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * @env: an array of environment variables
 * Return: 0
 */
int main(int argc, char *argv[], char *env[])
{
char **cmds_arr;
int n = 0;
list_t *env_list;
env_list = array_to_linked_list(env);
if (argc == 2)
{
execute_file(argv[1], env, env_list);
}
while (1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "$ ", 2);
else
non_interactive(env, env_list);
signal(SIGINT, ctrl_c);
cmds_arr = get_cmd(env_list, STDIN_FILENO);
if (cmds_arr == NULL)
{
n++;
continue;
}
execute_cmds(cmds_arr, env, &n, env_list);
}
return (0);
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
 * @env_list: linked list of environment
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

