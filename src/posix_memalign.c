// La fonction posix_memalign() alloue size octets et
// place l'adresse de la mémoire allouée dans *memptr.
// L'adresse de la mémoire allouée est un multiple de alignment,
// qui doit lui même être une puissance de deux et un multiple de sizeof(void *).


#include "ft_malloc.h"

#define ENOMEM 12
#define EINVAL 22

int     posix_memalign(void **memptr, size_t alignment, size_t size)
{
    if ((alignment / sizeof(void *)) || (alignment % 2))
        return (EINVAL);
    *memptr = ft_malloc(size);
    return (0);
}