# Nome do executável
EXEC = etapa6

# Diretórios
SRCDIR = src
INCDIR = headers

# Arquivos-fonte e gerados
LEX     = $(SRCDIR)/scanner.l
YACC    = $(SRCDIR)/parser.y
# Add iloc.h to HEADERS
HEADERS = $(INCDIR)/asd.h $(INCDIR)/lexical_value.h $(INCDIR)/tables.h $(INCDIR)/errors.h $(INCDIR)/iloc.h $(INCDIR)/asm.h
# Add iloc.c to CFILES
CFILES = $(SRCDIR)/main.c parser.tab.c lex.yy.c $(SRCDIR)/asd.c $(SRCDIR)/tables.c $(SRCDIR)/errors.c $(SRCDIR)/iloc.c $(SRCDIR)/asm.c
# Add iloc.o to OFILES
OFILES = main.o parser.tab.o lex.yy.o asd.o tables.o errors.o iloc.o asm.o

# Compilador e flags
CC      = gcc
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
# main.o now depends on iloc.h
main.o: $(SRCDIR)/main.c parser.tab.h $(INCDIR)/asd.h $(INCDIR)/iloc.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c

# parser.tab.o now depends on iloc.h
parser.tab.o: parser.tab.c $(INCDIR)/asd.h $(INCDIR)/lexical_value.h $(INCDIR)/tables.h $(INCDIR)/errors.h $(INCDIR)/iloc.h
	$(CC) $(CFLAGS) -c parser.tab.c

# lex.yy.o dependencies remain the same, no iloc.h dependency needed here directly
lex.yy.o: lex.yy.c parser.tab.h $(INCDIR)/lexical_value.h $(INCDIR)/tables.h $(INCDIR)/errors.h
	$(CC) $(CFLAGS) -c lex.yy.c

# asd.o now depends on iloc.h since asd.h includes it
asd.o: $(SRCDIR)/asd.c $(INCDIR)/asd.h $(INCDIR)/iloc.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/asd.c

tables.o: $(SRCDIR)/tables.c $(INCDIR)/tables.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/tables.c

errors.o: $(SRCDIR)/errors.c $(INCDIR)/errors.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/errors.c

# Add compilation rule for iloc.o
iloc.o: $(SRCDIR)/iloc.c $(INCDIR)/iloc.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/iloc.c

# Adiciona regra de compilação para asm.o
asm.o: $(SRCDIR)/asm.c $(INCDIR)/asm.h $(INCDIR)/iloc.h $(INCDIR)/tables.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/asm.c

# Linkagem
$(EXEC): $(OFILES)
	$(CC) $(CFLAGS) -o $(EXEC) $(OFILES)

# Limpeza
.PHONY: default clean
clean:
	rm -f $(EXEC) *.o lex.yy.c parser.tab.c parser.tab.h