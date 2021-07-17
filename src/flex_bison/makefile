LEXCC = ..\..\..\..\..\Compilers\win_flex.exe
BISONCC = ..\..\..\..\..\Compilers\win_bison.exe

LEX_FILE = tokens.l
LEX_OUT = lex.yy.c
BISON_FILE = tokens.y
BISON_OUT = tokens.tab.c
BISON_FLAGS = -d

${BISON_OUT}: ${LEX_FILE} ${BISON_FILE}
	${BISONCC} ${BISON_FLAGS} ${BISON_FILE}
	${LEXCC} ${LEX_FILE}

.PHONY: clean 
clean:
	del tokens.tab.h ${BISON_OUT} ${LEX_OUT}