#ifndef _ASD_H_
#define _ASD_H_

#include "iloc.h" // Include the ILOC header

typedef struct asd_tree {
  char *label;
  int number_of_children;
  struct asd_tree **children;
  int type;

  // Etapa5
  iloc_list_t *code; // Pointer to the ILOC code generated for this node
  char *temp;        // Temporary register name holding the result of this node's computation
} asd_tree_t;

/*
 * Função asd_new, cria um nó sem filhos com o label informado.
 */
asd_tree_t *asd_new(const char *label, int type);

/*
 * Função asd_tree, libera recursivamente o nó e seus filhos.
 */
void asd_free(asd_tree_t *tree);

/*
 * Função asd_add_child, adiciona child como filho de tree.
 */
void asd_add_child(asd_tree_t *tree, asd_tree_t *child);

/*
 * Função asd_print, imprime recursivamente a árvore.
 */
void asd_print(asd_tree_t *tree);

/*
 * Função asd_print_graphviz, idem, em formato DOT
 */
void asd_print_graphviz (asd_tree_t *tree);
#endif //_ASD_H_