#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    return 0;
  }

  FILE *fp;

  for (int i = 1; i < argc; i++) {
    fp = fopen(argv[i], "r");
    if (fp == NULL) {
      printf("wcat: cannot open file\n");
      exit(1);
    }

    // reads lines of files
    char buffer[100];
    while (fgets(buffer, 100, fp) != NULL) {
      printf("%s", buffer);
    }
    fclose(fp);
  }

  return 0;
}
