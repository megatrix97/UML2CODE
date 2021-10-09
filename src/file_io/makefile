CC = g++
CPP_VER = c++17

CXXFLAGS = -c

SRC_FILES = $(wildcard *.cpp) $(wildcard cpp_emitter/*.cpp)
OBJ_FILES = OBJ_RECIEPE

${OBJ_FILES}: ${SRC_FILES}
	${CC} ${CXXFLAGS} $^ -std=${CPP_VER}

debug: CXXFLAGS += -g
debug: ${OBJ_FILES}

.PHONY: clean
clean:
	del *.o