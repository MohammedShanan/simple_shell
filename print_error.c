#include "main.h"
/**
 * cmd_not_found - execute builtins commands
 * @cmd: array containing the command and it's arguments
 * @env: linked list of the environment variables
 * @cmd_num: the command number
 */
void cmd_not_found(char **cmd, list_t *env, int cmd_num)
{
list_t *list;
char **prog_name = NULL, *n;
list = get_env("_", env);
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
/**
 * illegal_number - execute builtins commands
 * @cmd: array containing the command and it's arguments
 * @env: linked list of the environment variables
 * @cmd_num: the command number
 */
void illegal_number(char **cmd, list_t *env, int cmd_num)
{
list_t *list;
char **prog_name = NULL, *n;
list = get_env("_", env);
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
