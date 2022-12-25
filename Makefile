CC			:= gcc
SRCS     	:= $(wildcard *.c)
OBJ      	:= $(SRCS:%.c=%.o)
BIN      	:= prog.out
FLAGS		:= -W -Wall -Werror
DEBUG		:= -g -ggdb
GLUT		:= -I/usr/include -L/usr/lib -lGL -lGLU -lglut

all : clean ${BIN}

debug : clean ${OBJ}
	${CC} ${FLAGS} ${DEBUG} -o ${BIN} ${OBJ} ${GLUT}

${BIN} : ${OBJ}
	${CC} ${FLAGS} -o $@ $^ ${GLUT}

%.o : %.c
	${CC} -c $^

clean :
	rm -f *.o
	rm -f ${BIN}

use : ${BIN}
	./${BIN}