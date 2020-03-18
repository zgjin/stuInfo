# STUINFO Makefile

# Fallback to gcc when $CC is not in $PATH.
CC:=$(shell sh -c 'type $${CC%% *} >/dev/null 2>/dev/null && echo $(CC) || echo gcc')

OBJDIR=zoo

OBJ=main.o api.o stu.o
APP=main

vpath %.c module
vpath %.h include
vpath %.o $(OBJDIR)
.PHONY: all
all: $(APP)
	$(CC) -o $(APP) $(OBJ) -lhiredis

.PHONY: $(APP)
$(APP): $(OBJ)

main.o: main.c api.h
api.o: api.c api.h stu.h
stu.o: stu.c stu.h

.PHONY: clean
clean:
	rm -rf *.o