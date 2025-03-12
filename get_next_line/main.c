#include "./get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int	main(void)
{
	char	*s;
	int		fd;

	fd = open("file.txt", O_RDONLY);
	s = get_next_line(fd);
	printf("- %s", s);
	free(s);
	s = get_next_line(fd);
	printf("- %s", s);
	free(s);
	s = get_next_line(fd);
	printf("- %s", s);
	free(s);
	s = get_next_line(fd);
	printf("- %s", s);
	free(s);
	s = get_next_line(fd);
	printf("- %s", s);
	free(s);
	s = get_next_line(fd);
	printf("- %s", s);
}
