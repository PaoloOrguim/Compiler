#include <stdio.h>
#include "asd.h"
#include "iloc.h"
extern int yyparse(void);
extern int yylex_destroy(void);
asd_tree_t *arvore = NULL;
int main (int argc, char **argv)
{
    int ret = yyparse();
    //asd_print_graphviz(arvore);
    if (arvore != NULL && arvore->code != NULL) {
        iloc_list_print(stdout, arvore->code);
    }
    //iloc_list_free(arvore->code);
    //fprintf(stderr, "teste");
    asd_free(arvore);
    yylex_destroy();
    return ret;
}