#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
  int fd = open("./zen_of_python2.txt", O_RDONLY);

  char *line;

 int i = 0;
  while ((line = get_next_line(fd)))
  {
    printf("%d: %s", i++, line);
    free(line);
  }
}
