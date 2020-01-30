#include "./includes_malloc/ft_malloc.h"

void print(char *s)
{
	write (1, s, strlen(s));
}

int main ()
{
	char *addr;

    free(NULL);
	addr = (char*)malloc(16);
    free((void*)addr + 5);
    if (realloc((void*)addr + 5, 10) == NULL)
        print("Bonjours\n");
}