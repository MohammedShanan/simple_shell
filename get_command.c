#include "main.h"
/**
 * get_cmd - get the command form stdin
 * @env: linked list of the environment variables
 * Return: a command
 */
char **get_cmd(list_t *env_list)
{
char *cmd = NULL, **arr = NULL;
size_t n = 0;
int nread;
nread = _getline(&cmd, &n, STDIN_FILENO);
ctrl_d(nread, cmd, env_list);
remove_comments(cmd);
arr = _strtok(arr, cmd, ";\n");
free(cmd);
if (arr[0] == NULL)
{
free_double_ptr(arr);
return (NULL);
}
return (arr);
}
/**
 * _getline - read from a file
 * @buff: buffer to write to
 * @n: size of the  buffer
 * @stream: file to read from
 * Return: number of charater read from the file
 */
int _getline(char **buff, size_t *n, int stream)
{
char *str;
int nread;
size_t len = 0, len_buff = *n, counter = 0;
*buff = *n == 0 ? NULL : *buff;
str = malloc(1025);
if (str == NULL)
{
return (-1);
}
while (1)
{
nread = read(stream, str, 1024);
if (nread <= 0)
{
free(str);
return (0);
}
len += nread, len_buff += nread;
str[nread] = '\0';
if (len_buff > *n)
{
*buff = _realloc(*buff, *n, len_buff + 1);
}
*buff = *n == 0 ? _strcpy(*buff, str) : _strcat(*buff, str);
*n = len_buff;
counter++;
if (str[nread - 1] == '\n')
{
break;
}
}
free(str);
return (len);
}

/**
 * get_cmd_path - get the path to the command executable
 * @cmd: command
 * @env: linked list of the environment variables
 * Return: absolute path to the command executable
 */
char *get_cmd_path(char **cmd, list_t *env)
{
char *pth = NULL;
if (access(cmd[0], F_OK) == 0)
{
pth = malloc(_strlen(cmd[0]) + 1);
pth = _strcpy(pth, cmd[0]);
}
else
{
pth = which(cmd[0], env);
if (pth == NULL)
{
return (NULL);
}
}
if (access(pth, X_OK) == 0)
{
return (pth);
}
free(pth);
return (NULL);
}
