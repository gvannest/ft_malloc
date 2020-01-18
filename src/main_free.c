#include <stdlib.h>

int		main()
{
	char *ptr;

	ptr = (char*)0xffffffff;
	ptr = realloc(ptr, 1000);
	return (1);
}
