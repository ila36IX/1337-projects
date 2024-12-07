#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int	main(void)
{
	int		fd;
	int		fd2;
	char	*null;

	fd = open("./null", O_RDONLY);
	fd2 = open("./null", O_RDONLY);
	null = get_next_line(1);
	free(null);
}
