# Nome do executável
EXEC = etapa4

# Diretórios
SRCDIR = src
INCDIR = headers

# Arquivos-fonte e gerados
LEX    = $(SRCDIR)/scanner.l
YACC   = $(SRCDIR)/parser.y
HEADERS = $(INCDIR)/asd.h $(INCDIR)/lexical_value.h $(INCDIR)/tables.h $(INCDIR)/errors.h
CFILES = $(SRCDIR)/main.c parser.tab.c lex.yy.c $(SRCDIR)/asd.c $(SRCDIR)/tables.c $(SRCDIR)/errors.c
OFILES = main.o parser.tab.o lex.yy.o asd.o tables.o errors.o

# Compilador e flags
CC     = gcc
CFLAGS = -Wall -g -fsanitize=address -I$(INCDIR)

# Target padrão
default: $(EXEC)

# Geração do scanner com Flex
lex.yy.c: $(LEX) $(HEADERS) parser.tab.h
	flex $(LEX)

# Geração do parser com Bison (gera parser.tab.c e parser.tab.h)
parser.tab.c parser.tab.h: $(YACC) $(HEADERS)
	bison -d $(YACC)

# Compilação dos arquivos .o
main.o: $(SRCDIR)/main.c parser.tab.h $(INCDIR)/asd.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c

parser.tab.o: parser.tab.c $(INCDIR)/asd.h $(INCDIR)/lexical_value.h $(INCDIR)/tables.h $(INCDIR)/errors.h
	$(CC) $(CFLAGS) -c parser.tab.c

lex.yy.o: lex.yy.c parser.tab.h $(INCDIR)/lexical_value.h $(INCDIR)/tables.h $(INCDIR)/errors.h
	$(CC) $(CFLAGS) -c lex.yy.c

asd.o: $(SRCDIR)/asd.c $(INCDIR)/asd.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/asd.c

tables.o: $(SRCDIR)/tables.c $(INCDIR)/tables.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/tables.c

errors.o: $(SRCDIR)/errors.c $(INCDIR)/errors.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/errors.c

# Linkagem
$(EXEC): $(OFILES)
	$(CC) $(CFLAGS) -o $(EXEC) $(OFILES)

# Limpeza
.PHONY: default clean
clean:
	rm -f $(EXEC) *.o lex.yy.c parser.tab.c parser.tab.h
