int		main()
{
	char *ptr;

	ptr = 0xffffffff;
	free(ptr);
	return (1);
}
