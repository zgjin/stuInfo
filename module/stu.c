#include <stdlib.h>
#include <stdio.h>
#include <hiredis/hiredis.h>

#include "../include/stu.h"

// StuErrno needs to be released
StuErrno *AddStudent(const Student *student) {
  printf("start adding student\n");
  // 参数判断
  StuErrno *s = NULL;
  s = calloc(1, sizeof(StuErrno));
  if (s == NULL) {
    return NULL;
  }

  if (student == NULL) {
    s->errno = STU_ERR_NULL;
    return s;
  }
  if (student->id == 0) {
    s->errno = STU_ERR_INVALID;
    return s;
  }

  // 链接 redis 查询是否已经存在
  redisContext *c;

  const char *hostname = "127.0.0.1";
  int port = 6379;
  struct timeval timeout = { 1, 500000 }; // 1.5 seconds
  printf("start connecting to redis\n");
  c = redisConnectWithTimeout(hostname, port, timeout);
  if (c == NULL || c->err) {
    if (c) {
      printf("Connection error: %s\n", c->errstr);
      redisFree(c);
    } else {
      printf("Connection error: can't allocate redis context\n");
    }

    s->errno = REDIS_ERR_DB;
    return s;
  }

  printf("redis connect successfully\n");

  redisReply *reply;

  reply = redisCommand(c,"EXISTS %d", student->id);
  printf("redis exists cmd executed\n");
  if (reply->type != REDIS_REPLY_INTEGER) {
    printf("redis err: %s\n", reply->str);
    s->errno = REDIS_ERR_DB;
    freeReplyObject(reply);
    redisFree(c);
    return s;
  }
  printf("redis exists result: %lld\n", reply->integer);
  if (reply->integer == 1) {
    s->errno = STU_ERR_ALREADY_EXIST;
    freeReplyObject(reply);
    redisFree(c);
    return s;
  }
  freeReplyObject(reply);

  printf("start executing HMSET cmd\n");
  // add student
  reply = redisCommand(c, "HMSET %d \
    id %d name %s gender %s age %d math %f cn %f en %f",\
    student->id, student->id, student->name, student->gender,\
    student->math, student->cn, student->en);
  printf("hmset result: type=%d, str=%s", reply->type, reply->str);
  if (reply->type != REDIS_REPLY_STATUS) {
    s->errno = REDIS_ERR_DB;
    printf("redis err: %s\n", reply->str);
    freeReplyObject(reply);
    redisFree(c);
    return s;
  }
  freeReplyObject(reply);
  redisFree(c);

  s->id = student->id;
  s->errno = 0;

  return s;
};

StuErrno *DeleteStudentByID(int id) {
  return NULL;
}

StuErrno *UpdateStudentByID(int id, const Student *student) {
  return NULL;
}

StuWithErrno *GetStudentByID(int id) {
  return NULL;
}

void PrintfStudent(const Student *stu) {
  printf("student:{id=%d, name=%s, gender=%s, age=%d, math=%f, cn=%f, en=%f}",\
    stu->id, stu->name, stu->gender, stu->age, stu->math, stu->cn, stu->en);
}

void PrintfStudentWithErrno(const StuWithErrno *data) {
  if (data->err != NULL) {
    printf("student data: {err:{errno=%d, id=%d}, id=%d, name=%s, gender=%s, age=%d, math=%f, cn=%f, en=%f}",\
      data->err->errno, data->err->id, data->id, data->name, data->gender, data->age, data->math, data->cn, data->en);
  } else {
    printf("student:{id=%d, name=%s, gender=%s, age=%d, math=%f, cn=%f, en=%f}",\
      data->id, data->name, data->gender, data->age, data->math, data->cn, data->en);
  }
}