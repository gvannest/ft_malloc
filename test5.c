// #include <stdlib.h>
#include "./includes_malloc/ft_malloc.h"

int main ()
{
    malloc(1024);
    void *ptr = malloc(1024 * 32);
    malloc(1024 * 1024);
    malloc(1024 * 1024 * 16);
    malloc(1024 * 1024 * 128);

    ft_printf("---show_alloc_mem---\n");
    show_alloc_mem();
    printf("\n\n");
    ft_printf("---Print header chunk---\n");
    print_header_chunk(ptr - HDR_SIZE);
    printf("\n\n");    
    ft_printf("---Dump hex memory---\n");
    dump_hex_memory(ptr, 64);
    printf("\n\n");
    ft_printf("---show_alloc_mem_complete---\n");
    show_alloc_mem_complete();
    return (0);
}