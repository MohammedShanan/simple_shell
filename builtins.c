#include "main.h"
/**
 * _env - print environemnt variables
 * @env: a linked list of the environemnt variables
 * Return:value of environemnt variable
 */
void _env(list_t *env)
{
while (env)
{
write(STDOUT_FILENO, env->str, env->len);
write(STDOUT_FILENO, "\n", 1);
env = env->next;
}
}
/**
 * __exit - exit the program
 * @cmd: command
 * @env: linked list of the e
 * Return:
 */
int __exit(char **cmd, list_t *env)
{
int exit_st;
exit_st = cmd[1] != NULL ? c_to_num(cmd[1]) : 0;
if (exit_st == -1)
{
return (1);
}
free_list(env);
free_double_ptr(cmd);
exit(exit_st);
}
