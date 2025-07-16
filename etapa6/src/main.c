#include <stdio.h>
#include "asd.h"
#include "iloc.h"
#include "asm.h"
#include "tables.h"

extern int yyparse(void);
extern int yylex_destroy(void);

asd_tree_t *arvore = NULL;
struct table *global_scope = NULL; // Variável global para a tabela de símbolos (Etapa 6)

int main (int argc, char **argv)
{
    int ret = yyparse();
    
    if (arvore != NULL) {
        // Gerar assembly (Etapa 6)
        asm_generate(arvore->code, global_scope);
    }

    asd_free(arvore);
    arvore = NULL;

    // (Etapa 6)
    free_table(global_scope); 
    global_scope = NULL; 

    yylex_destroy();
    return ret;
}
