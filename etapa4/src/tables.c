/*
    Paolo Gabriel Orguim Simioni - 00335061
    Arthur Olinto Dossena        - 00325370
*/

#include "../headers/tables.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Criar uma nova entrada
struct entry create_entry(int line_number, int nature, int type, valor_t value) {
    struct entry new_entry;
    new_entry.line_number = line_number;
    new_entry.nature = nature;
    new_entry.type = type;
    new_entry.value = value;
    return new_entry;
}

// Criar uma nova tabela
struct table *create_table() {
    struct table *new_table = malloc(sizeof(struct table));
    if(new_table != NULL) {
        new_table->total_entries = 0;
        new_table->entries = NULL;
    }
    return new_table;
}

// Adicionar uma entrada a tabela
void add_entry(struct table *table, struct entry *entry) {
    if (table == NULL || entry == NULL) {
        return;
    }
    table->total_entries++;
    table->entries = realloc(table->entries, table->total_entries * sizeof(struct entry *));
    if(table->entries != NULL) {
        table->entries[table->total_entries - 1] = malloc(sizeof(struct entry));
        if(table->entries[table->total_entries - 1] != NULL) {
            *(table->entries[table->total_entries - 1]) = *entry;
            entry->value.token_val = strdup(entry->value.token_val);
            if(entry->value.token_val == NULL) {
                fprintf(stderr, "Erro ao alocar memória para o valor do token\n");
            }
        }
    }
}

// Buscar uma entrada na tabela
struct entry *search_entry(struct table *table, char *name) {
    if (table == NULL || name == NULL) {
        return NULL;
    }
    for (int i = 0; i < table->total_entries; i++) {
        if (strcmp(table->entries[i]->value.token_val, name) == 0) {
            return table->entries[i];
        }
    }
    return NULL;
}

// Liberar a memória da tabela
void free_table(struct table *table) {
    if (table == NULL) {
        return;
    }
    int i;
    for (i = 0; i < table->total_entries; i++) {
        free(table->entries[i]->value.token_val);
        free(table->entries[i]);
    }
    free(table->entries);
    free(table);
}




// Criar a pilha de tabelas
struct table_stack *create_table_stack() {
    struct table_stack *new_table_stack = malloc(sizeof(struct table_stack));
    if(new_table_stack != NULL) {
        new_table_stack->top = NULL;
        new_table_stack->next = NULL;
    }
    return new_table_stack;
}

// Adicionar uma tabela a pilha
void push_table_stack(struct table_stack **stack, struct table *table) {
    if (table == NULL) {
        return;
    }
    if (*stack == NULL) {
        *stack = create_table_stack();
    }
    if ((*stack)->top != NULL) {
        struct table_stack *new_node = create_table_stack();
        new_node->top = (*stack)->top;
        new_node->next = (*stack)->next;
        (*stack)->next = new_node;
    }
    (*stack)->top = table;
}

// Remover a tabela do topo da pilha
void pop_table_stack(struct table_stack **stack) {
    if (stack == NULL) {
        return;
    }
    struct table_stack *temp = *stack;
    if ((*stack)->next != NULL) {
        *stack = (*stack)->next;
        free(temp->top);
        free(temp);
    } else {
        free_table((*stack)->top);
        free(*stack);
        *stack = NULL;
    }
}

// Liberar a memória da pilha de tabelas
void free_table_stack(struct table_stack *stack) {
    if (stack == NULL) {
        return;
    }
    while (stack->next != NULL) {
        struct table_stack *temp = stack;
        stack = stack->next;
        free_table(temp->top);
        free(temp);
    }
    free_table(stack->top);
    free(stack);
}

// Buscar uma entrada na pilha de tabelas
struct entry *search_entry_in_stack(struct table_stack *stack, char *name) {
    if (stack == NULL || name == NULL) {
        return NULL;
    }
    struct entry *entry = search_entry(stack->top, name);
    if (entry != NULL) {
        return entry;
    }
    while (stack->next != NULL) {
        stack = stack->next;
        entry = search_entry(stack->top, name);
        if (entry != NULL) {
            return entry;
        }
    }
    return NULL;
}