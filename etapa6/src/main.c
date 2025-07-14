#include <stdio.h>
#include "asd.h"
#include "iloc.h"
#include "asm.h" // Inclui o novo cabeçalho do assembly
#include "tables.h"

extern int yyparse(void);
extern int yylex_destroy(void);

asd_tree_t *arvore = NULL;
struct table *global_scope = NULL; // Variável global para a tabela de símbolos (Etapa 6)

int main (int argc, char **argv)
{
    int ret = yyparse();
    
    if (arvore != NULL) {
        // Gera o código assembly em vez do ILOC ou do .dot (Etapa 6)
        asm_generate(arvore->code, global_scope);
    }

    // Libera toda a memória
    asd_free(arvore);
    arvore = NULL;

    // CORREÇÃO: Agora main() é responsável por liberar a tabela global. (Etapa 6)
    free_table(global_scope); 
    global_scope = NULL; 

    yylex_destroy();
    return ret;
}
