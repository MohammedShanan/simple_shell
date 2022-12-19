#include "main.h"
/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * @env: an array of environment variables
 * Return: 0
 */
int main(int argc UNUSED, char *argv[] UNUSED, char *env[])
{
list_t *env_list;
env_list = array_to_linked_list(env);
prompt(env_list);
return (0);
}
