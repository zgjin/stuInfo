#include <stdio.h>
#include <stdlib.h>

#include "../include/api.h"
#include "../include/stu.h"

void AddStudentAction() {
  printf("add method is called\n");
  Student stu = {
    .id = 1,
    .name = "kim",
    .age = 28,
    .math = 99,
    .cn = 88,
    .en = 90,
  };

  StuErrno *errno;
  errno = AddStudent(&stu);
  if (errno == NULL || errno->errno != 0) {
    if (errno) {
      printf("add failed, %d\n", errno->errno);
    } else {
      printf("add failed\n");
    }
  }
  if (errno) {
    free(errno);
  }
}

void DeleteStudentByIDAction() {

}

void UpdateStudentByIDAction() {

}

void GetStudentByIDAction() {

}