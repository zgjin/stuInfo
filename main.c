#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/api.h"

int main(int argc, char *argv[]) {
  const char *action = NULL;

  action = (argc > 1) ? argv[1] : "default";

  if (strcmp(action, "add") == 0) {
    AddStudentAction();
  } else {
    printf("wrong action");
    exit(1);
  }
}