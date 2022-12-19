#include "main.h"
void print_double_ptr(char **ptr)
{
    int i = 0;
    while (ptr[i] != NULL)
    {
        printf("%s ", ptr[i]);
        i++;
    }
    printf("\n");
}