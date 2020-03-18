#ifndef _STU_H
#define _STU_H

#define STU_OK 0
#define STU_ERR -1
#define STU_ERR_NULL 1
#define STU_ERR_NOT_FOUND 2
#define STU_ERR_INVALID 3
#define STU_ERR_ALREADY_EXIST 4
#define REDIS_ERR_DB 5

typedef struct Student {
  int id;
  char name[20];
  char gender[4];
  int age;
  float math;
  float cn;
  float en;
} Student;

typedef struct StuErrno {
  int errno;
  int id;
} StuErrno;

typedef struct StuWithErrno {
  StuErrno *err;
  int id;
  char name[20];
  char gender[4];
  int age;
  float math;
  float cn;
  float en;
} StuWithErrno;

StuErrno *AddStudent(const Student *student);

StuErrno *DeleteStudentByID(int id);

StuErrno *UpdateStudentByID(int id, const Student *student);

StuWithErrno *GetStudentByID(int id);

void PrintfStudent(const Student *student);

void PrintfStudentWithErrno(const StuWithErrno *data);

#endif