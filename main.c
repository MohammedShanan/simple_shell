#include "main.h"
int main(int argc UNUSED, char *argv[] UNUSED, char *env[])
{
    list_t *env_list;
    env_list = array_to_linked_list(env);
    prompt(env_list);
    return (0);
}