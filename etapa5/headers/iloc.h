#ifndef ILOC_H
#define ILOC_H

#include <stdio.h>

// operando iloc
typedef struct {
    enum {
        OPERAND_REGISTER,
        OPERAND_CONSTANT,
        OPERAND_LABEL
    } type;
    union {
        char *reg_name;   // rfp, rbss, r1, r2 etc
        int value;        // constantes
        char *label_name; // L1 L2 etc
    } u;
} iloc_operand_t;

//instrução iloc
typedef struct iloc_op {
    char *opcode;
    iloc_operand_t *src1;
    iloc_operand_t *src2;
    iloc_operand_t *dest1;
    iloc_operand_t *dest2;
    char *label;           
    char *comment;      // comentario de debug pro iloc.txt
    struct iloc_op *next;
} iloc_op_t;

// lista de instruções iloc
typedef struct {
    iloc_op_t *head;
    iloc_op_t *tail;
} iloc_list_t;

// funções pra manipular operandos e operações/instruções iloc
iloc_operand_t *iloc_operand_new_reg(const char *name);
iloc_operand_t *iloc_operand_new_const(int value);
iloc_operand_t *iloc_operand_new_label(const char *name);
void iloc_operand_free(iloc_operand_t *operand);

iloc_op_t *iloc_op_new(const char *opcode, iloc_operand_t *src1, iloc_operand_t *src2, iloc_operand_t *dest1, iloc_operand_t *dest2, const char *label, const char *comment);
void iloc_op_free(iloc_op_t *op);

// funções pra manipular listas de instruções iloc
iloc_list_t *iloc_list_new();
void iloc_list_add(iloc_list_t *list, iloc_op_t *op);
void iloc_list_concat(iloc_list_t *list1, iloc_list_t *list2);
void iloc_list_print(FILE *fp, iloc_list_t *list);
void iloc_list_free(iloc_list_t *list);

// funções pra nomes de rótulos e registradores
char *iloc_new_label();
char *iloc_new_reg_temp();

#endif