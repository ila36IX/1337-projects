#include "./get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char *s;
	int fd = open("file.txt", O_RDONLY);

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
