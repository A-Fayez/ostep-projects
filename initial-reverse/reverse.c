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

  current->next = (node_t *)malloc(sizeof(node_t));
  current->next->line = (char *)malloc(strlen(line) + 1);
  strcpy(current->next->line, line);
  current->next->next = NULL;
}

void print_list(node_t *head, FILE *stream) {
  if (head == NULL)
    return;
  print_list(head->next, stream);
  fprintf(stream, head->line);
}

int main(int argc, char *argv[]) {
  if (argc > 3) {
    fprintf(stderr, "usage: reverse <input> <output>");
    exit(1);
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  node_t *head = (node_t *)malloc(sizeof(node_t));
  switch (argc) {
    // no args, read from stdin
  case 1:
    int first = 1;
    while ((nread = getline(&line, &len, stdin)) != -1) {
      if (first) {
        head->line = (char *)malloc(strlen(line) + 1);
        strcpy(head->line, line);
        head->next = NULL;
        first = 0;
        continue;
      }
      push(head, line);
    }
    free(line);
    break;
  }
  print_list(head, stdout);
  return 0;
}
