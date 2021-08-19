CC = g++

CORE_DIR = core
FILEIO_DIR = file_io
FLEXBISON_DIR = flex_bison

INCLUDE_DIR = -I${CORE_DIR}/include -I${FILEIO_DIR}/cpp_emitter/include -I${FILEIO_DIR}/include -I${FLEXBISON_DIR}

all: dependencies
	$(eval OBJ_FILES = $(wildcard core/*.o) $(wildcard file_io/*.o))
	${CC} -o parser flex_bison/lex.yy.c flex_bison/tokens.tab.c ${OBJ_FILES} main.cpp ${DEBUG_FLAGS}

dependencies:
	${MAKE} -C ${CORE_DIR} ${DEBUG}
	${MAKE} -C ${FILEIO_DIR} ${DEBUG}
	${MAKE} -C ${FLEXBISON_DIR}

debug: DEBUG += debug
debug: DEBUG_FLAGS += -g
debug: all

run: parser.exe test.blu
	.\parser.exe .\test.blu

clean:
	${MAKE} -C ${CORE_DIR} clean
	${MAKE} -C ${FILEIO_DIR} clean
	${MAKE} -C ${FLEXBISON_DIR} clean
	del parser.exe