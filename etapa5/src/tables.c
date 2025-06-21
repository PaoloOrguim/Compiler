/*
    Paolo Gabriel Orguim Simioni - 00335061
    Arthur Olinto Dossena        - 00325370
*/

#include "../headers/tables.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Criar uma nova entrada
struct entry create_entry(int line_number, int nature, int type, valor_t value, int num_params, struct param_info *params_list) {
    struct entry new_entry;
    new_entry.line_number = line_number;
    new_entry.nature = nature;
    new_entry.type = type;
    new_entry.value = value;
    new_entry.num_params = 0;
    new_entry.params = NULL;
    if (nature == NATURE_FUNC && num_params > 0 && params_list != NULL) {
        new_entry.num_params = num_params;
        // Parametros copiados em add_entry
    }
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
void add_entry(struct table *table, struct entry *entry_to_add) {
    if (table == NULL || entry_to_add == NULL) {
        return;
    }
    table->total_entries++;
    table->entries = realloc(table->entries, table->total_entries * sizeof(struct entry *));
    if (table->entries == NULL) {
        fprintf(stderr, "Erro ao realocar memória para entradas da tabela\n");
        table->total_entries--; 
        exit(1); // Or better error handling
    }
    table->entries[table->total_entries - 1] = malloc(sizeof(struct entry));
    if (table->entries[table->total_entries - 1] == NULL) {
        fprintf(stderr, "Erro ao alocar memória para nova entrada\n");
        table->total_entries--;
        exit(1);
    }
    memcpy(table->entries[table->total_entries - 1], entry_to_add, sizeof(struct entry));

    // Deep copy for token_val if needed
    if (entry_to_add->value.token_val != NULL) {
        table->entries[table->total_entries - 1]->value.token_val = strdup(entry_to_add->value.token_val);
        if (table->entries[table->total_entries - 1]->value.token_val == NULL) {
            fprintf(stderr, "Erro ao alocar memória para token_val\n");
            exit(1);
        }
    }

    // Deep copy for params if it's a function
    if (entry_to_add->nature == NATURE_FUNC && entry_to_add->num_params > 0 && entry_to_add->params != NULL) {
        table->entries[table->total_entries - 1]->params = malloc(entry_to_add->num_params * sizeof(struct param_info));
        if (table->entries[table->total_entries - 1]->params == NULL) {
            fprintf(stderr, "Erro ao alocar memória para params\n");
            exit(1);
        }
        memcpy(table->entries[table->total_entries - 1]->params, entry_to_add->params, entry_to_add->num_params * sizeof(struct param_info));
    }
}

// Buscar uma entrada na tabela
struct entry *search_entry(struct table *table, char *name) {
    if (table == NULL || name == NULL) {
        return NULL;
    }
    for (int i = 0; i < table->total_entries; i++) {
        if (table->entries[i] != NULL && table->entries[i]->value.token_val != NULL &&
        strcmp(table->entries[i]->value.token_val, name) == 0) {
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
    if (table->entries != NULL) {
        for (int i = 0; i < table->total_entries; i++) {
            if (table->entries[i] != NULL) {
                if (table->entries[i]->value.token_val != NULL) {
                    free(table->entries[i]->value.token_val);
                    table->entries[i]->value.token_val = NULL;
                }
                if (table->entries[i]->nature == NATURE_FUNC && table->entries[i]->params != NULL) {
                    free(table->entries[i]->params); // Free params array for functions
                    table->entries[i]->params = NULL;
                }
                free(table->entries[i]);
                table->entries[i] = NULL;
            }
        }
        free(table->entries);
        table->entries = NULL;
    }
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
    if (*stack == NULL) { // First table in the stack
        *stack = create_table_stack();
         if (*stack == NULL) {
            fprintf(stderr, "Falha ao criar a pilha de tabelas\n");
            exit(1);
        }
        (*stack)->top = table;
        (*stack)->next = NULL; // Explicitly NULL for the first element's next
        return;
    }

    // For subsequent tables
    struct table_stack *new_node = create_table_stack();
    if (new_node == NULL) {
        fprintf(stderr, "Falha ao criar novo nó para a pilha de tabelas\n");
        exit(1);
    }
    new_node->top = table; // The new table becomes the top of the new node
    new_node->next = *stack; // The old stack becomes the next for the new node
    *stack = new_node; // The new node becomes the current stack
}

// Remover a tabela do topo da pilha
void pop_table_stack(struct table_stack **stack) {
    if (stack == NULL || *stack == NULL) {
        return;
    }
    struct table_stack *temp_node = *stack;
    *stack = (*stack)->next; // Move stack pointer to the next node

    free_table(temp_node->top); // Correctly use free_table for the table itself
    free(temp_node);            // Free the stack node
}

// Liberar a memória da pilha de tabelas
void free_table_stack(struct table_stack *stack) {
    while (stack != NULL) {
        struct table_stack *temp = stack;
        stack = stack->next;
        free_table(temp->top);
        free(temp);
    }
}

// Buscar uma entrada na pilha de tabelas
struct entry *search_entry_in_stack(struct table_stack *stack, char *name) {
    if (name == NULL) {
        return NULL;
    }
    struct table_stack *current_stack_node = stack;
    while (current_stack_node != NULL) {
        if (current_stack_node->top != NULL) {
            struct entry *entry = search_entry(current_stack_node->top, name);
            if (entry != NULL) {
                return entry;
            }
        }
        current_stack_node = current_stack_node->next;
    }
    return NULL;
}