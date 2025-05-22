# Nome do executável
EXEC = etapa3

# Arquivos-fonte e gerados
LEX    = scanner.l
YACC   = parser.y
HEADERS = asd.h lexical_value.h
CFILES = main.c parser.tab.c lex.yy.c asd.c
OFILES = main.o parser.tab.o lex.yy.o asd.o

# Compilador e flags
CC     = gcc
CFLAGS = -Wall -g -fsanitize=address -I.

# Target padrão
default: $(EXEC)

# Geração do scanner com Flex
lex.yy.c: $(LEX) $(HEADERS) parser.tab.h
	flex $(LEX)

# Geração do parser com Bison (gera parser.tab.c e parser.tab.h)
parser.tab.c parser.tab.h: $(YACC) $(HEADERS)
	bison -d $(YACC)

# Compilação dos arquivos .o
main.o: main.c parser.tab.h asd.h
	$(CC) $(CFLAGS) -c main.c

parser.tab.o: parser.tab.c asd.h lexical_value.h
	$(CC) $(CFLAGS) -c parser.tab.c

lex.yy.o: lex.yy.c parser.tab.h lexical_value.h
	$(CC) $(CFLAGS) -c lex.yy.c

asd.o: asd.c asd.h
	$(CC) $(CFLAGS) -c asd.c

# Linkagem
$(EXEC): $(OFILES)
	$(CC) $(CFLAGS) -o $(EXEC) $(OFILES)

# Limpeza
.PHONY: default clean
clean:
	rm -f $(EXEC) *.o lex.yy.c parser.tab.c parser.tab.h
