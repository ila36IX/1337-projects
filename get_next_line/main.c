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
  line = get_next_line(fd);
  printf("%s", line);
  free(line);
  line = get_next_line(fd);
  printf("%s", line);
  free(line);
  close(fd);
  fd = open("./zen_of_python2.txt", O_RDONLY);
  line = get_next_line(fd);
  printf("%s", line);
  free(line);
}
