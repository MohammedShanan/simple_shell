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
 * @cmd: array containing the command and it's arguments
 * @env: linked list of the environment variables
 * @cmd_num: the command number
 * Return: 1 on error;
 */
int __exit(char **cmd, list_t *env, int cmd_num)
{
int exit_st = 0;
exit_st = cmd[1] != NULL ? c_to_num(cmd[1]) : 0;
if (exit_st == -1)
{
illegal_number(cmd, env, cmd_num);
return (1);
}
free_list(env);
free_double_ptr(cmd);
exit(exit_st);
}
/**
 * _setenv - set or modify an environment variable
 * @cmd: array containing the command and it's arguments
 * @env: linked list of the environment variables
 */
void _setenv(char **cmd, list_t *env)
{
char *str;
list_t *var;
int len_str;
printf("here 2");
if (cmd[1] == NULL || cmd[2] == NULL)
{
write(STDERR_FILENO, "Too few arguments\n", 18);
return;
}
len_str = _strlen(cmd[1]) + _strlen(cmd[2]) + 2;
str = malloc(len_str);
if (str == NULL)
{
return;
}
str = _strcpy(str, cmd[1]);
str = _strcat(str, "=");
str = _strcat(str, cmd[2]);
var = get_env(cmd[1], env);
printf("new env = %s", str);
if (var == NULL)
{
add_node_end(&env, str);
}
else
{
free(var->str);
var->str = _strdup2(str);
}
free(str);
}
/**
 * _unsetenv - unset environment variable
 * @cmd: array containing the command and it's arguments
 * @env: linked list of the environment variables
 */
void _unsetenv(char **cmd, list_t *env)
{
list_t *var;
if (cmd[1] == NULL)
{
write(STDERR_FILENO, "Too few arguments\n", 18);
return;
}
var = get_env(cmd[1], env);
while (env && var)
{
if (env->next != NULL)
{
if (env->next == var)
{
env->next = var->next;
free(var->str);
free(var);
return;
}
}
env = env->next;
}
write(STDERR_FILENO, "Cannot find variable\n", 21);
}
