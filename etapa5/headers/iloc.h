#ifndef ILOC_H
#define ILOC_H

#include <stdio.h>

// Estrutura para um operando ILOC
typedef struct {
    enum {
        OPERAND_REGISTER,
        OPERAND_CONSTANT,
        OPERAND_LABEL
    } type;
    union {
        char *reg_name;   // For registers (e.g., "r1", "rfp", "rbss")
        int value;        // For constants
        char *label_name; // For labels (e.g., "L1")
    } u;
} iloc_operand_t;

// Estrutura para uma operação ILOC
typedef struct iloc_op {
    char *opcode;
    iloc_operand_t *src1;
    iloc_operand_t *src2;
    iloc_operand_t *dest1;
    iloc_operand_t *dest2; // For operations like storeAI with two dest operands
    char *label;           // Optional label for the instruction
    char *comment;         // Optional comment
    struct iloc_op *next;
} iloc_op_t;

// Estrutura para uma lista de operações ILOC (representa o código ILOC gerado)
typedef struct {
    iloc_op_t *head;
    iloc_op_t *tail;
} iloc_list_t;

// Funções para manipulação de operandos e operações ILOC
iloc_operand_t *iloc_operand_new_reg(const char *name);
iloc_operand_t *iloc_operand_new_const(int value);
iloc_operand_t *iloc_operand_new_label(const char *name);
void iloc_operand_free(iloc_operand_t *operand);

iloc_op_t *iloc_op_new(const char *opcode, iloc_operand_t *src1, iloc_operand_t *src2, iloc_operand_t *dest1, iloc_operand_t *dest2, const char *label, const char *comment);
void iloc_op_free(iloc_op_t *op);

// Funções para manipulação da lista de operações ILOC
iloc_list_t *iloc_list_new();
void iloc_list_add(iloc_list_t *list, iloc_op_t *op);
void iloc_list_concat(iloc_list_t *list1, iloc_list_t *list2);
void iloc_list_print(FILE *fp, iloc_list_t *list);
void iloc_list_free(iloc_list_t *list);

// Funções para geração de nomes de rótulos e temporários
char *iloc_new_label();
char *iloc_new_reg_temp();

#endif