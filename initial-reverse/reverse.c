#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc > 3) {
    fprintf(stderr, "usage: reverse <input> <output>");
    exit(1);
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  switch (argc) {
    // no args, read from stdin
  case 1:
    while ((nread = getline(&line, &len, stdin)) != 1) {
      fprintf(stdout, line);
    }
    free(line);
    exit(0);
    break;
  }
}
