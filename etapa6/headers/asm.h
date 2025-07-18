#ifndef ASM_H
#define ASM_H

#include "iloc.h"
#include "tables.h"

// Funcao pra gerar assembly
// Recebe a lista de instruções ILOC e a tabela de símbolos do escopo global.
void asm_generate(iloc_list_t *iloc_code, struct table *global_scope);

#endif
