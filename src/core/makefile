CC = g++

CXXFLAGS = -c

SRC_FILES = $(wildcard *.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

${OBJ_FILES}: ${SRC_FILES}
	${CC} ${CXXFLAGS} $^

debug: CXXFLAGS += -g
debug: ${OBJ_FILES}

.PHONY:clean
clean:
	del *.o