#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct node {
  char *line;
  struct node *next;
} node_t;

void push(node_t *head, char *line) {
  node_t *current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  if ((current->next = (node_t *)malloc(sizeof(node_t))) == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }
  if ((current->next->line = (char *)malloc(strlen(line) + 1)) == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }
  strcpy(current->next->line, line);
  current->next->next = NULL;
}

void print_list(node_t *head, FILE *stream) {
  if (head == NULL)
    return;
  print_list(head->next, stream);
  fprintf(stream, head->line);
}

void free_list(node_t *head) {
  node_t *current = NULL;

  while ((current = head) != NULL) {
    head = head->next;
    free(current->line);
    free(current);
  }
}

int main(int argc, char *argv[]) {
  if (argc > 3) {
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(1);
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  node_t *head = (node_t *)malloc(sizeof(node_t));

  if (head == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }

  switch (argc) {
    // no args, read from stdin
  case 1:
    int first = 1;
    while ((nread = getline(&line, &len, stdin)) != -1) {
      if (first) {
        if ((head->line = (char *)malloc(strlen(line) + 1)) == NULL) {
          fprintf(stderr, "malloc failed\n");
          exit(1);
        }
        strcpy(head->line, line);
        head->next = NULL;
        first = 0;
        continue;
      }
      push(head, line);
    }
    print_list(head, stdout);
    free(line);
    exit(0);
    break;

  case 2:
    int _first = 1;
    FILE *istream = fopen(argv[1], "r");
    if (istream == NULL) {
      fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
      exit(1);
    }
    while ((nread = getline(&line, &len, istream)) != -1) {
      if (_first) {
        if ((head->line = (char *)malloc(strlen(line) + 1)) == NULL) {
          fprintf(stderr, "malloc failed\n");
          exit(1);
        }
        strcpy(head->line, line);
        head->next = NULL;
        _first = 0;
        continue;
      }
      push(head, line);
    }
    print_list(head, stdout);
    free(line);
    fclose(istream);
    exit(0);
    break;

  case 3:
    if (strcmp(argv[1], argv[2]) == 0) {
      fprintf(stderr, "reverse: input and output file must differ\n");
      exit(1);
    }
    int __first = 1;
    FILE *ifile;
    FILE *ofile;

    if ((ifile = fopen(argv[1], "r")) == NULL) {
      fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
      exit(1);
    }

    if ((ofile = fopen(argv[2], "w")) == NULL) {
      fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
      exit(1);
    }

    while ((nread = getline(&line, &len, ifile)) != -1) {
      if (__first) {
        if ((head->line = (char *)malloc(strlen(line) + 1)) == NULL) {
          fprintf(stderr, "malloc failed\n");
          exit(1);
        }
        strcpy(head->line, line);
        head->next = NULL;
        __first = 0;
        continue;
      }
      push(head, line);
    }
    print_list(head, ofile);
    free(line);
    fclose(ifile);
    fclose(ofile);
    exit(0);
    break;
  }

  free_list(head);
  return 0;
}
