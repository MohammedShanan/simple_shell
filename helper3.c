#include "main.h"
/**
 * which - get the path to the command executable
 * @cmd: command
 * @env: linked list of the environment variables
 * Return: absolute path to the command executable
 */
char *which(char *exe, list_t *env)
{
list_t *pth;
char **pth_arr = NULL, *tmp;
int i = 1;
pth = get_env("PATH", env);
pth_arr = _strtok(pth_arr, pth->str, "=:");
tmp = malloc(1024);
while (pth_arr[i] != NULL)
{
tmp = _strcpy(tmp, pth_arr[i]);
tmp = _strcat(tmp, "/");
tmp = _strcat(tmp, exe);
if (access(tmp, F_OK) == 0)
{
free_double_ptr(pth_arr);
return (tmp);
}
i++;
}
free(tmp);
free_double_ptr(pth_arr);
return (NULL);
}

/**
 * _strtok - read from a file
 * @arr: array to write to
 * @str: string to process
 * @delim: set of bytes that delimit the string
 * Return: an array of strings
 */
char **_strtok(char **arr, char *str, const char *delim)
{
int i, j, len, indx;
i = j = len = indx = 0;
arr = malloc(sizeof(char *) * 1024);
while (str[i])
{
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
/**
 * get_env - get the environment variable from env linked list
 * @var: environment variable
 * @env: linked list of the environment variables
 * Return: pointer to the environment variable
 */
list_t *get_env(char *var, list_t *env)
{
int i = 0;
list_t *value;
while (env != NULL)
{
while (var[i] == env->str[i])
{
i++;
}
if (var[i] == '\0' && env->str[i] == '=')
{
break;
}
i = 0;
env = env->next;
}
if (env == NULL)
{
return (NULL);
}
value = env;
return (value);
}
