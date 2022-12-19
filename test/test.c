#include "main.h"
#include "main.h"
int main(int argc UNUSED, char *argv[] UNUSED, char *env[])
{
list_t *env_list;
env_list = array_to_linked_list(env);
char *tmp = NULL;
size_t n = 0;
int i;
i = _getline(&tmp, &n, stdin);
prompt(env_list);
return (0);
}
/*linked list--------------------------------------------------------------*/
size_t list_len(const list_t *h)
{
unsigned int count = 0;
while (h)
{
h = h->next;
count++;
}
return (count);
}
list_t *add_node_end(list_t **head, char *str)
{
list_t *node;
list_t *last_node = NULL;
last_node = *head;
str = _strdup2(str);
if (str == NULL)
{
return (NULL);
}
node = malloc(sizeof(list_t));
if (node == NULL)
{
return (NULL);
}
node->str = str;
node->len = _strlen(node->str);
node->next = NULL;
if (*head == NULL)
{
*head = node;
}
else
{
while (last_node->next)
{
last_node = last_node->next;
}
last_node->next = node;
}
return (node);
}
void free_list(list_t *head)
{
list_t *tmp = NULL;
while (head)
{
tmp = head;
head = head->next;
free(tmp->str);
free(tmp);
}
}
list_t *array_to_linked_list(char *arr[])
{
int i = 0;
list_t *head = NULL;
while (arr[i] != NULL)
{
add_node_end(&head, arr[i]);
i++;
}
return (head);
}

/*helper 1----------------------------------------------------------------*/
char *_strcat(char *dest, char *src)
{
int i;
i = _strlen(dest);
while (*src)
{
*(dest + i) = *src;
i++, src++;
}
*(dest + i) = '\0';
return (dest);
}
int _strlen(char *s)
{
int len;
len = 0;
if (s == NULL)
{
return (0);
}
while (*s)
{
len++;
s++;
}
return (len);
}
char *_strcpy(char *dest, char *src)
{
int i;

for (i = 0; src[i]; i++)
{
dest[i] = src[i];
}
dest[i] = '\0';
return (dest);
}
char *_strdup2(char *str)
{
char *new_str;
int size;
if (str == NULL)
{
return (NULL);
}
size = _strlen(str) + 1;
new_str = malloc(size);
if (new_str == NULL)
{
return (NULL);
}
return (_strcpy(new_str, str));
}
int _strcmp(char *s1, char *s2)
{
while (*s1 || *s2)
{
if (*s1 != *s2)
{
return (*s1 - *s2);
}
s1++, s2++;
}
return (0);
}

/*helper 2----------------------------------------------------------------------------------*/
int is_c_in_str(char c, const char *str)
{
int i = 0;
while (str[i])
{
if (str[i] == c)
{
return (1);
}
i++;
}
return (0);
}
char *_strncpy(char *dest, char *src, int n, int indx)
{
int i;
i = 0;
while (i < n)
{
dest[i] = src[indx];
i++, indx++;
}
dest[i] = '\0';
return (dest);
}
void free_double_ptr(char **ptr)
{
int i = 0;
while (ptr[i] != NULL)
{
free(ptr[i]);
i++;
}
free(ptr);
}
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *p;
unsigned int i;
if (new_size == 0 && ptr != NULL)
{
free(ptr);
return (NULL);
}

if (ptr == NULL)
{
p = malloc(new_size);
if (p == NULL)
{
return (NULL);
}

return (p);
}

if (new_size == old_size)
{
return (ptr);
}
p = malloc(new_size);
if (p == NULL)
{
return (NULL);
}

for (i = 0; i < old_size; i++)
{
*((char *)p + i) = *((char *)ptr + i);
}
free(ptr);
return (p);
}
int c_to_num(char *s)
{
int i = 0, num = 0;
while (s[i])
{
if (s[i] >= '0' && s[i] <= '9')
{
num *= 10;
num += s[i] - '0';
}
else
{
return (-1);
}
i++;
}
return (num);
}

/*get command*/
char **get_cmd(list_t *env)
{
char *cmd = NULL, **arr = NULL;
size_t n = 0;
int nread;
nread = _getline(&cmd, &n, STDIN_FILENO);
ctrl_d(nread, env, cmd);
arr = _strtok(arr, cmd, " \n");
printf("cmd is %s\n", cmd);
free(cmd);
if (arr[0] == NULL)
{
free_double_ptr(arr);
return (NULL);
}
return (arr);
}
/**
 * get_cmd - read from a file
 * @buff: buffer to write to
 * @n: size of the  buffer
 * @stream: file to read from
 * Return: number of charater read from the file
 */
int _getline(char **buff, size_t *n, FILE *stream UNUSED)
{
char *str;
int nread;
size_t len = 0, len_buff = *n;
*buff = *n == 0 ? NULL : *buff;
str = malloc(1025);
if (str == NULL)
{
return (-1);
}
while (1)
{
nread = read(STDIN_FILENO, str, 1024);
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
if (str[nread - 1] == '\n')
{
break;
}
}
free(str);
return (len);
}

char *get_cmd_path(char **cmd, list_t *env)
{
char *pth = NULL;
if (access(cmd[0], F_OK) == 0)
{
pth = _strcpy(pth, cmd[0]);
return (pth);
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
return (NULL);
}
/*builtins ----------------------------------------------------*/
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
/*execute command----------------------------------------*/

/**
 * __execve - execute commands
 * @cmd: array containing the command and it's arguments
 * @env: linked list of the environment variables
 * @num: the command number
 * Return: 0
 */
int __execve(char **cmd, list_t *env, int cmd_num UNUSED)
{
char *path;
int is_builtin;
is_builtin = builtins(cmd, env, cmd_num);
if (is_builtin)
{
return (0);
}
path = get_cmd_path(cmd, env);
if (path == NULL)
{
return (-1);
}
if (fork() != 0)
{
wait(NULL);
free(path);
}
else if (execve(path, cmd, NULL) == -1)
{
return (-1);
}
return (0);
}

/**
 * builtins - execute builtins commands
 * @cmd: array containing the command and it's arguments
 * @env: linked list of the environment variables
 * @num: the command number
 * Return: 0
 */
int builtins(char **cmd, list_t *env, int cmd_num UNUSED)
{
int exit_status UNUSED;
if (_strcmp(cmd[0], "exit") == 0)
{
exit_status = __exit(cmd, env);
}
else if (_strcmp(cmd[0], "env") == 0)
{
_env(env);
}
else if (_strcmp(cmd[0], "setenv") == 0)
{
_env(env);
}
else if (_strcmp(cmd[0], "unsetenv") == 0)
{
_env(env);
}
else if (_strcmp(cmd[0], "cd") == 0)
{
_env(env);
}
else
{
return (0);
}
return (1);
}
void non_interactive(list_t *env UNUSED)
{
return;
}

/* helper 3--------------------------------------*/

char *which(char *exe, list_t *env)
{
list_t *pth;
char **pth_arr, *tmp;
int i = 1;
pth = get_env("PATH", env);
pth_arr = _strtok(pth_arr, pth->str, "=:");
tmp = malloc(1024);
while (pth_arr[i] != NULL)
{
printf("%s\n", pth_arr[i]);
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

list_t *get_env(char *var, list_t *env)
{
int i = 0, len_val;
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

/* unknown ----------------------*/
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
