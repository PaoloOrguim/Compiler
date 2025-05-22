#ifndef TABLES_H
#define TABLES_H

#include "lexical_value.h"

// Entradas
struct entry{
    int line_number;
    int nature;
    int type;
    valor_t value;
};

// Tabelas, com numero total de entradas e ponteiro para as entradas
struct table{
    int total_entries;
    struct entry **entries;
};

// Pilha de tabelas, com ponteiro para a tabela atual
struct table_stack{
    struct table *top;
    struct table_stack *next;
};

// Funções para manipular entradas e tabelas

// Cria uma nova entrada
struct entry create_entry(int line_number, int nature, int type, valor_t value);

// Cria uma nova tabela
// Adiciona uma entrada a tabela
// Busca uma entrada na tabela
// Libera a memória da tabela
struct table *create_table();
void add_entry(struct table *table, struct entry *entry);
struct entry *search_entry(struct table *table, char *name);
void free_table(struct table *table);

// Cria uma nova pilha de tabelas
// Adiciona uma tabela a pilha
// Remove a tabela do topo da pilha
// Libera a memória da pilha de tabelas
// Busca uma entrada na pilha de tabelas
struct table_stack *create_table_stack();
void push_table_stack(struct table_stack **stack, struct table *table);
void pop_table_stack(struct table_stack **stack);
void free_table_stack(struct table_stack *stack);
struct entry *search_entry_in_stack(struct table_stack *stack, char *name);

#endif