#ifndef TABLES_H
#define TABLES_H

#include "lexical_value.h"

#define NATURE_VAR 0
#define NATURE_FUNC 1
#define NATURE_LIT 2

#define TYPE_UNDEFINED 0 
#define TYPE_INT       1
#define TYPE_FLOAT     2

// Para parametros de funcoes
struct param_info{
    int type;
    //char *name;
};

// Entradas
struct entry{
    int line_number; // Para mensagens de erro
    int offset;      // Deslocamento de memória
    int is_global;   // Flag para identificar variável global
    int nature;
    int type;
    valor_t value;

    // Caso de funcoes
    int num_params;
    struct param_info *params;
};

// Tabelas, com numero total de entradas e ponteiro para as entradas
struct table{
    int total_entries;
    int current_offset; // Mantém o próximo deslocamento de memória disponível
    struct entry **entries;
};

// Pilha de tabelas, com ponteiro para a tabela atual
struct table_stack{
    struct table *top;
    struct table_stack *next;
};

// Funções para manipular entradas e tabelas

// Cria uma nova entrada
struct entry create_entry(int line_number, int offset, int is_global, int nature, int type, valor_t value, int num_params, struct param_info *params);

// Cria uma nova tabela
// Adiciona uma entrada a tabela
// Busca uma entrada na tabela
// Libera a memória da tabela
struct table *create_table();
void add_entry(struct table *table, struct entry *entry_to_add);
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
