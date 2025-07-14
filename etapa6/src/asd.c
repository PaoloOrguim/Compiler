#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "asd.h"

asd_tree_t *asd_new(const char *label, int type)
{
  asd_tree_t *ret = NULL;
  ret = calloc(1, sizeof(asd_tree_t));
  if (ret != NULL){
    ret->label = strdup(label);
    ret->number_of_children = 0;
    ret->children = NULL;
    ret->type = type;
    ret->code = NULL;
    ret->temp = NULL;
  }
  return ret;
}

void asd_free(asd_tree_t *tree)
{
  if (tree == NULL) return;
  
  for (int i = 0; i < tree->number_of_children; i++){
    asd_free(tree->children[i]);
  }
  
  if (tree->children) free(tree->children);
  if (tree->label) free(tree->label);
  if (tree->code) iloc_list_free(tree->code);
  if (tree->temp) free(tree->temp);
  
  free(tree);
}

void asd_add_child(asd_tree_t *tree, asd_tree_t *child)
{
  if (tree != NULL && child != NULL){
    tree->number_of_children++;
    tree->children = realloc(tree->children, tree->number_of_children * sizeof(asd_tree_t*));
    tree->children[tree->number_of_children-1] = child;
  }
}

static void _asd_print_graphviz (FILE *foutput, asd_tree_t *tree)
{
  if (tree == NULL) return;

  fprintf(foutput, "  %ld [ label=\"%s\" ];\n", (long)tree, tree->label ? tree->label : "null_label");
  for (int i = 0; i < tree->number_of_children; i++){
      if (tree->children[i] != NULL) {
          fprintf(foutput, "  %ld -> %ld;\n", (long)tree, (long)tree->children[i]);
          _asd_print_graphviz(foutput, tree->children[i]);
      }
  }
}

void asd_print_graphviz(asd_tree_t *tree)
{
  FILE *foutput = stdout;
  if (tree != NULL){
    fprintf(foutput, "digraph grafo {\n");
    _asd_print_graphviz(foutput, tree);
    fprintf(foutput, "}\n");
  }
}
