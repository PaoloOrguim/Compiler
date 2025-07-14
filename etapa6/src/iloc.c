#include "iloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int label_counter = 0;
static int reg_temp_counter = 0;

// cria um operando do tipo registrador
iloc_operand_t *iloc_operand_new_reg(const char *name) {
    iloc_operand_t *operand = (iloc_operand_t *)malloc(sizeof(iloc_operand_t));
    if (operand == NULL) {
        perror("Failed to allocate iloc_operand_t");
        exit(EXIT_FAILURE);
    }
    operand->type = OPERAND_REGISTER;
    operand->u.reg_name = strdup(name);
    if (operand->u.reg_name == NULL) {
        perror("Failed to duplicate register name");
        exit(EXIT_FAILURE);
    }
    return operand;
}

// cria um operando do tipo inteiro constante
iloc_operand_t *iloc_operand_new_const(int value) {
    iloc_operand_t *operand = (iloc_operand_t *)malloc(sizeof(iloc_operand_t));
    if (operand == NULL) {
        perror("Failed to allocate iloc_operand_t");
        exit(EXIT_FAILURE);
    }
    operand->type = OPERAND_CONSTANT;
    operand->u.value = value;
    return operand;
}

// cria um operando do tipo label
iloc_operand_t *iloc_operand_new_label(const char *name) {
    iloc_operand_t *operand = (iloc_operand_t *)malloc(sizeof(iloc_operand_t));
    if (operand == NULL) {
        perror("Failed to allocate iloc_operand_t");
        exit(EXIT_FAILURE);
    }
    operand->type = OPERAND_LABEL;
    operand->u.label_name = strdup(name);
    if (operand->u.label_name == NULL) {
        perror("Failed to duplicate label name");
        exit(EXIT_FAILURE);
    }
    return operand;
}

// libera a memoria
void iloc_operand_free(iloc_operand_t *operand) {
    if (operand == NULL) return;
    if (operand->type == OPERAND_REGISTER && operand->u.reg_name != NULL) {
        free(operand->u.reg_name);
    }
    if (operand->type == OPERAND_LABEL && operand->u.label_name != NULL) {
        free(operand->u.label_name);
    }
    free(operand);
}

// cria uma nova instrução iloc
iloc_op_t *iloc_op_new(const char *opcode, iloc_operand_t *src1, iloc_operand_t *src2, iloc_operand_t *dest1, iloc_operand_t *dest2, const char *label, const char *comment) {
    iloc_op_t *op = (iloc_op_t *)malloc(sizeof(iloc_op_t));
    if (op == NULL) {
        perror("Failed to allocate iloc_op_t");
        exit(EXIT_FAILURE);
    }
    op->opcode = strdup(opcode);
    if (op->opcode == NULL) {
        perror("Failed to duplicate opcode");
        exit(EXIT_FAILURE);
    }
    op->src1 = src1;
    op->src2 = src2;
    op->dest1 = dest1;
    op->dest2 = dest2;
    op->label = (label != NULL) ? strdup(label) : NULL;
    op->comment = (comment != NULL) ? strdup(comment) : NULL;
    op->next = NULL;
    return op;
}

// libera a isntrução inteira
void iloc_op_free(iloc_op_t *op) {
    if (op == NULL) return;
    free(op->opcode);
    iloc_operand_free(op->src1);
    iloc_operand_free(op->src2);
    iloc_operand_free(op->dest1);
    iloc_operand_free(op->dest2);
    if (op->label != NULL) free(op->label);
    if (op->comment != NULL) free(op->comment);
    free(op);
}

// cria uma lista de instruções iloc
iloc_list_t *iloc_list_new() {
    iloc_list_t *list = (iloc_list_t *)malloc(sizeof(iloc_list_t));
    if (list == NULL) {
        perror("Failed to allocate iloc_list_t");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// adiciona uma instrução na lista
void iloc_list_add(iloc_list_t *list, iloc_op_t *op) {
    if (list == NULL || op == NULL) return;
    if (list->head == NULL) {
        list->head = op;
        list->tail = op;
    } else {
        list->tail->next = op;
        list->tail = op;
    }
}

// concatena duas listas numa só
void iloc_list_concat(iloc_list_t *list1, iloc_list_t *list2) {
    if (list1 == NULL || list2 == NULL) return;

    if (list2->head != NULL) {
        if (list1->head == NULL) {
            list1->head = list2->head;
            list1->tail = list2->tail;
        } else {
            list1->tail->next = list2->head;
            list1->tail = list2->tail;
        }
    }

    // pra consertar aquele leak de memoria
    free(list2);
}

// printa a lista
void iloc_list_print(FILE *fp, iloc_list_t *list) {
    if (list == NULL || list->head == NULL) return;
    iloc_op_t *current = list->head;
    while (current != NULL) {
        if (current->label != NULL) {
            fprintf(fp, "%s: ", current->label);
        }
        fprintf(fp, "%s", current->opcode);

        if (current->src1 != NULL) {
            fprintf(fp, " ");
            if (current->src1->type == OPERAND_REGISTER) fprintf(fp, "%s", current->src1->u.reg_name);
            else if (current->src1->type == OPERAND_CONSTANT) fprintf(fp, "%d", current->src1->u.value);
            else if (current->src1->type == OPERAND_LABEL) fprintf(fp, "%s", current->src1->u.label_name);
        }
        if (current->src2 != NULL) {
            fprintf(fp, ", ");
            if (current->src2->type == OPERAND_REGISTER) fprintf(fp, "%s", current->src2->u.reg_name);
            else if (current->src2->type == OPERAND_CONSTANT) fprintf(fp, "%d", current->src2->u.value);
            else if (current->src2->type == OPERAND_LABEL) fprintf(fp, "%s", current->src2->u.label_name);
        }

        const char* separator = " =>"; 
        if (strcmp(current->opcode, "cbr") == 0 || // se for algum desvio, muda a setinha conforme o doc do sor
            strcmp(current->opcode, "jumpI") == 0 ||
            strcmp(current->opcode, "jump") == 0) {
            separator = " ->";
        }

        if (current->dest1 != NULL || current->dest2 != NULL) {
            fprintf(fp, "%s", separator);
            
            if (strcmp(current->opcode, "storeAI") == 0 || strcmp(current->opcode, "cstoreAI") == 0) {
                if (current->dest1 != NULL) {
                    fprintf(fp, " ");
                    if (current->dest1->type == OPERAND_REGISTER) fprintf(fp, "%s", current->dest1->u.reg_name);
                }
                if (current->dest2 != NULL && current->dest2->type == OPERAND_CONSTANT) {
                    fprintf(fp, ", %d", current->dest2->u.value); 
                }
            } else if (strcmp(current->opcode, "cbr") == 0) { 
                 if (current->dest1 != NULL) {
                    fprintf(fp, " ");
                    if (current->dest1->type == OPERAND_LABEL) fprintf(fp, "%s", current->dest1->u.label_name);
                }
                if (current->dest2 != NULL) {
                    fprintf(fp, ", ");
                    if (current->dest2->type == OPERAND_LABEL) fprintf(fp, "%s", current->dest2->u.label_name);
                }
            }
            else {
                if (current->dest1 != NULL) {
                    fprintf(fp, " ");
                    if (current->dest1->type == OPERAND_REGISTER) fprintf(fp, "%s", current->dest1->u.reg_name);
                    else if (current->dest1->type == OPERAND_CONSTANT) fprintf(fp, "%d", current->dest1->u.value);
                    else if (current->dest1->type == OPERAND_LABEL) fprintf(fp, "%s", current->dest1->u.label_name);
                }
                if (current->dest2 != NULL) {
                    fprintf(fp, ", ");
                    if (current->dest2->type == OPERAND_REGISTER) fprintf(fp, "%s", current->dest2->u.reg_name);
                    else if (current->dest2->type == OPERAND_CONSTANT) fprintf(fp, "%d", current->dest2->u.value);
                    else if (current->dest2->type == OPERAND_LABEL) fprintf(fp, "%s", current->dest2->u.label_name);
                }
            }
        }
        
        if (current->comment != NULL) {
            fprintf(fp, " // %s", current->comment);
        }
        fprintf(fp, "\n");
        current = current->next;
    }
}

// libera a lista inteira
void iloc_list_free(iloc_list_t *list) {
    if (list == NULL) return;
    iloc_op_t *current = list->head;
    while (current != NULL) {
        iloc_op_t *next = current->next;
        iloc_op_free(current);
        current = next;
    }
    free(list);
}

// gera um novo label unico com o label_counter
char *iloc_new_label() {
    char *label = (char *)malloc(20 * sizeof(char));
    if (label == NULL) {
        perror("Failed to allocate label");
        exit(EXIT_FAILURE);
    }
    sprintf(label, "L%d", label_counter++);
    return label;
}

// gera um novo registrador unico com o reg_temp_counter
char *iloc_new_reg_temp() {
    char *temp_reg = (char *)malloc(20 * sizeof(char));
    if (temp_reg == NULL) {
        perror("Failed to allocate temporary register");
        exit(EXIT_FAILURE);
    }
    sprintf(temp_reg, "r%d", reg_temp_counter++);
    return temp_reg;
}
