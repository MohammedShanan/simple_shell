#ifndef MAIN_H
#define MAIN_H
#define UNUSED __attribute__((unused))
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <strings.h>

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 */
typedef struct list_s
{
char *str;
unsigned int len;
struct list_s *next;
} list_t;
void prompt(list_t *env);
int _getline(char **buff, size_t *n, FILE *stream);
char **_strtok(char **arr, char *str, const char *delim);
void ctrl_d(int nread, list_t *env, char *cmd);
char **get_cmd(list_t *env);
void ctrl_c(int n __attribute__((unused)));
/*helper functions 1*/
char *_strcat(char *dest, char *src);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strdup2(char *str);
int _strcmp(char *s1, char *s2);
/*helper functions 2*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int is_c_in_str(char c, const char *str);
char *_strncpy(char *dest, char *src, int n, int indx);
void free_double_ptr(char **ptr);
int c_to_num(char *s);
/*linked list*/
list_t *array_to_linked_list(char *arr[]);
size_t list_len(const list_t *h);
list_t *add_node_end(list_t **head, char *str);
void free_list(list_t *head);
/*builtins*/
int __exit(char **cmd, list_t *env);
void _env(list_t *env);
/*helper 3*/
list_t *get_env(char *var, list_t *env);
char *get_cmd_path(char **cmd, list_t *env);
char *which(char *exe, list_t *env);
/*execute commands 3*/
int builtins(char **cmd, list_t *env, int cmd_num);
int __execve(char **cmd, list_t *env, int cmd_num);
/*uncat*/
void ctrl_l(int n __attribute__((unused)));
void non_interactive(list_t *env);
#endif
