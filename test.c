#include "minishell.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char *line = "asdf asdf";
  char **p;

  p = ft_split(line, ' ');
  printf("%s\n", *p);
  return (0);
}