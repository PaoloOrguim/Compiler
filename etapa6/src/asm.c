#include "asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função auxiliar para obter o offset de um registrador temporário na pilha.
int get_temp_offset(const char *temp_reg) {
    if (temp_reg == NULL) return 0;
    return (atoi(temp_reg + 1) + 1) * 4;
}

// NOVA FUNÇÃO: Encontra o nome de uma variável global pelo seu offset.
const char* find_global_variable_by_offset(struct table *global_scope, int offset) {
    if (global_scope == NULL) {
        return "unknown_global"; // Fallback
    }
    for (int i = 0; i < global_scope->total_entries; i++) {
        struct entry *e = global_scope->entries[i];
        if (e != NULL && e->nature == NATURE_VAR && e->is_global && e->offset == offset) {
            return e->value.token_val;
        }
    }
    return "unknown_global_offset"; // Fallback se não encontrar
}


void asm_generate(iloc_list_t *iloc_code, struct table *global_scope) {
    if (iloc_code == NULL) return;

    // --- 1. Segmento de Dados (.data) ---
    printf("\t.data\n");
    if (global_scope != NULL) {
        for (int i = 0; i < global_scope->total_entries; i++) {
            struct entry *e = global_scope->entries[i];
            if (e != NULL && e->nature == NATURE_VAR) {
                printf(".globl %s\n", e->value.token_val);
                printf("\t.align 4\n");
                printf("%s:\n", e->value.token_val);
                printf("\t.long 0\n"); // Inicializa todas as globais com 0
            }
        }
    }
    printf("\n");

    // --- 2. Segmento de Texto (.text) ---
    printf("\t.text\n");

    iloc_op_t *current_op = iloc_code->head;
    char current_func_name[256] = "";

    while (current_op != NULL) {
        if (current_op->label != NULL) {
            printf("%s:\n", current_op->label);
        }

        if (strcmp(current_op->opcode, "nop") == 0 && current_op->comment != NULL && strstr(current_op->comment, "Function entry")) {
            strcpy(current_func_name, current_op->label);
            printf(".globl %s\n", current_func_name);
            printf("%s:\n", current_func_name);
            printf("\tpushq %%rbp\n");
            printf("\tmovq %%rsp, %%rbp\n");
            printf("\tsubq $400, %%rsp\n"); 
        } 
        else if (strcmp(current_op->opcode, "loadI") == 0) {
            int offset = get_temp_offset(current_op->dest1->u.reg_name);
            printf("\tmovl $%d, -%d(%%rbp)\n", current_op->src1->u.value, offset);
        }
        else if (strcmp(current_op->opcode, "loadAI") == 0) {
            int dest_offset = get_temp_offset(current_op->dest1->u.reg_name);
            if (strcmp(current_op->src1->u.reg_name, "rfp") == 0) {
                printf("\tmovl -%d(%%rbp), %%eax\n", current_op->src2->u.value);
            } else { // "rbss"
                // CORREÇÃO: Usa a função de busca para obter o nome real da variável.
                const char* var_name = find_global_variable_by_offset(global_scope, current_op->src2->u.value);
                printf("\tmovl %s(%%rip), %%eax\n", var_name);
            }
            printf("\tmovl %%eax, -%d(%%rbp)\n", dest_offset);
        }
        else if (strcmp(current_op->opcode, "storeAI") == 0) {
            int src_offset = get_temp_offset(current_op->src1->u.reg_name);
            printf("\tmovl -%d(%%rbp), %%eax\n", src_offset);

            if (strcmp(current_op->dest1->u.reg_name, "rfp") == 0) {
                printf("\tmovl %%eax, -%d(%%rbp)\n", current_op->dest2->u.value);
            } else { // "rbss"
                // CORREÇÃO: Usa a função de busca para obter o nome real da variável.
                const char* var_name = find_global_variable_by_offset(global_scope, current_op->dest2->u.value);
                printf("\tmovl %%eax, %s(%%rip)\n", var_name);
            }
        }
        else if (strcmp(current_op->opcode, "add") == 0) {
            int offsetA = get_temp_offset(current_op->src1->u.reg_name);
            int offsetB = get_temp_offset(current_op->src2->u.reg_name);
            int offsetC = get_temp_offset(current_op->dest1->u.reg_name);
            printf("\tmovl -%d(%%rbp), %%eax\n", offsetA);
            printf("\tmovl -%d(%%rbp), %%ecx\n", offsetB);
            printf("\taddl %%ecx, %%eax\n");
            printf("\tmovl %%eax, -%d(%%rbp)\n", offsetC);
        }
        else if (strcmp(current_op->opcode, "sub") == 0) {
            int offsetA = get_temp_offset(current_op->src1->u.reg_name);
            int offsetB = get_temp_offset(current_op->src2->u.reg_name);
            int offsetC = get_temp_offset(current_op->dest1->u.reg_name);
            printf("\tmovl -%d(%%rbp), %%eax\n", offsetA);
            printf("\tmovl -%d(%%rbp), %%ecx\n", offsetB);
            printf("\tsubl %%ecx, %%eax\n");
            printf("\tmovl %%eax, -%d(%%rbp)\n", offsetC);
        }
        else if (strcmp(current_op->opcode, "mult") == 0) {
            int offsetA = get_temp_offset(current_op->src1->u.reg_name);
            int offsetB = get_temp_offset(current_op->src2->u.reg_name);
            int offsetC = get_temp_offset(current_op->dest1->u.reg_name);
            printf("\tmovl -%d(%%rbp), %%eax\n", offsetA);
            printf("\timull -%d(%%rbp), %%eax\n", offsetB);
            printf("\tmovl %%eax, -%d(%%rbp)\n", offsetC);
        }
        else if (strncmp(current_op->opcode, "cmp_", 4) == 0) {
            int offsetA = get_temp_offset(current_op->src1->u.reg_name);
            int offsetB = get_temp_offset(current_op->src2->u.reg_name);
            int offsetC = get_temp_offset(current_op->dest1->u.reg_name);
            
            printf("\tmovl -%d(%%rbp), %%eax\n", offsetA);
            printf("\tmovl -%d(%%rbp), %%edx\n", offsetB); // Usa edx para o segundo operando
            printf("\tcmpl %%edx, %%eax\n");              // Compara eax com edx

            // --- LÓGICA DE TRADUÇÃO CORRETA ---
            const char *suffix = current_op->opcode + 4; // Pega o sufixo (ex: "LT", "EQ")
            char set_instruction[32];

            if (strcmp(suffix, "LT") == 0) {
                strcpy(set_instruction, "setl");
            } else if (strcmp(suffix, "LE") == 0) {
                strcpy(set_instruction, "setle");
            } else if (strcmp(suffix, "GT") == 0) {
                strcpy(set_instruction, "setg");
            } else if (strcmp(suffix, "GE") == 0) {
                strcpy(set_instruction, "setge");
            } else if (strcmp(suffix, "EQ") == 0) {
                strcpy(set_instruction, "sete");
            } else if (strcmp(suffix, "NE") == 0) {
                strcpy(set_instruction, "setne");
            } else {
                // Fallback para caso encontre um opcode inesperado
                strcpy(set_instruction, "nop # UNKNOWN_CMP"); 
            }

            printf("\t%s %%al\n", set_instruction);
            // ------------------------------------

            printf("\tmovzbl %%al, %%eax\n");
            printf("\tmovl %%eax, -%d(%%rbp)\n", offsetC);
        }
        else if (strcmp(current_op->opcode, "cbr") == 0) {
            int offset = get_temp_offset(current_op->src1->u.reg_name);
            printf("\tmovl -%d(%%rbp), %%eax\n", offset);
            printf("\tcmpl $0, %%eax\n");
            printf("\tjne %s\n", current_op->dest1->u.label_name);
            printf("\tjmp %s\n", current_op->dest2->u.label_name);
        }
        else if (strcmp(current_op->opcode, "jumpI") == 0) {
            printf("\tjmp %s\n", current_op->dest1->u.label_name);
        }
        else if (strcmp(current_op->opcode, "i2i") == 0) {
            int offsetA = get_temp_offset(current_op->src1->u.reg_name);
            printf("\tmovl -%d(%%rbp), %%eax\n", offsetA);
            printf("\tleave\n");
            printf("\tret\n\n");
        }

        current_op = current_op->next;
    }
}