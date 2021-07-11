CC = g++
LEX = ..\..\..\Compilers\win_flex.exe
BISON = ..\..\..\Compilers\win_bison.exe
UML_SRC_FILES = $(wildcard *.cpp)
UML_OBJ_FILES = $(UML_SRC_FILES:.cpp=.o)
TEST_FILE = test.blu
LEX_FILE = tokens.l
LEX_OUT = lex.yy.c
MAIN = parser
OFLAGS = -o
CFLAGS = -c -g
BISON_FLAGS = -d
BISON_FILE = tokens.y
BISON_OUT = tokens.tab.c

${MAIN}: ${UML_OBJ_FILES} ${LEX_OUT}
	${CC} ${OFLAGS} $@ ${LEX_OUT} ${BISON_OUT} ${UML_OBJ_FILES} -g

${LEX_OUT}: ${LEX_FILE} ${BISON_FILE} 
	${BISON} ${BISON_FLAGS} ${BISON_FILE}
	${LEX} ${LEX_FILE}

${UML_OBJ_FILES}: ${UML_SRC_FILES}
	${CC} ${CFLAGS} $^



.PHONY: clean
clean:
	del lex.yy.c ${MAIN}.exe tokens.tab.c tokens.tab.h ${UML_OBJ_FILES}

.PHONY: run
run: 
	${MAIN}.exe ${TEST_FILE}