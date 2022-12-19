#include "main.h"
/**
 * prompt - prompt the user for the command
 * @env: linked list of the environment variables
 */
void prompt(list_t *env)
{
    char **cmd_arr;
    size_t cmd_num = 0;
    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);
        else
            non_interactive(env);
        signal(SIGINT, ctrl_c);
        cmd_arr = get_cmd(env);
        if (cmd_arr == NULL)
            continue;
        __execve(cmd_arr, env, cmd_num);
        free_double_ptr(cmd_arr);
        cmd_num++;
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

