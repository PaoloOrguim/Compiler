%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "asd.h"
    #include "lexical_value.h"    /* struct valor_t */
    #include "tables.h"          /* entries, table and stack related code */
    #include "../headers/errors.h"          /* error codes */

    #define PLACEHOLDER 0

    #define MAX_PARAMS 32 // Defina um limite razoável para o número de parâmetros
    struct param_info temp_params[MAX_PARAMS];
    int temp_param_count = 0;

    extern asd_tree_t *arvore;  /* raiz da AST */

    struct table_stack *stack = NULL; // Pilha de tabelas
    int variable_type = 0; // Tipo da variavel
    int function_type = 0; // Tipo da funcao

    extern int yylex(void);     /* corrigir erro zoado*/

    int get_line_number(void);

    void yyerror (const char *mensagem);
%}

%define parse.error verbose

%union {
  valor_t    *lex_val;  /* para TK_ID e literais */
  asd_tree_t *no_ast;        /* para os nós da AST */
}

%token TK_PR_AS TK_PR_DECLARE TK_PR_ELSE TK_PR_FLOAT TK_PR_IF TK_PR_INT TK_PR_IS TK_PR_RETURN
%token TK_PR_RETURNS TK_PR_WHILE TK_PR_WITH TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE
%token <lex_val> TK_ID TK_LI_INT TK_LI_FLOAT
%token TK_ER

%type<no_ast> programa lista elemento def_func decl_var_global header tipo header_head pre_param_list
%type<no_ast> param_list parameter body command_block simple_command_list simple_command
%type<no_ast> init decl_var attribution call_func arg_list return_command
%type<no_ast> flow_ctrl conditional while expressao
%type<no_ast> n7 n6 n5 n4 n3 n2 n1 n0
%type<no_ast> push_table pop_table tipo_funcao

%%

programa
    : /*vazio*/                                                 { $$ = NULL; arvore = $$; } // Inicio da arvore
    | push_table lista pop_table ';'                              { $$ = $2; arvore = $$; }
    ;

lista
    : elemento                              { $$ = $1; }    // Elemento vira cabeca e se houver lista vira filho dos elementos anteriores
    | elemento ',' lista                    {
                                                if ($1 == NULL){
                                                    $$ = $3;
                                                } else if($3 == NULL){
                                                    $$ = $1;
                                                } else{
                                                    $$ = $1;
                                                    asd_add_child($$, $3);
                                                }
                                            }
    ;

elemento
    : def_func                              { $$ = $1; }    // Ambos passados pra cabeca
    | decl_var_global                       { $$ = $1; }
    ;

def_func
    : header TK_PR_IS body pop_table   { // No com a label do header. Body vira filho
                                                    $$ = asd_new($1->label, PLACEHOLDER);
                                                    if ($3 != NULL){
                                                        asd_add_child($$, $3);
                                                    }
                                                    asd_free($1);
                                                }
    ;

decl_var_global
    : TK_PR_DECLARE TK_ID TK_PR_AS tipo     {   
                                                // Verificar se a variavel ja foi declarada
                                                // Se sim, erro de variavel ja declarada
                                                // Se nao, criar variavel e adicionar na tabela
                                                char *name = $2->token_val;
                                                if(search_entry(stack->top, name) != NULL){
                                                    semantic_error(ERR_DECLARED, "Identificador ja declarado neste escopo", get_line_number());
                                                } else{
                                                    valor_t v;
                                                    v.line_number = get_line_number();
                                                    v.token_type = TK_ID;
                                                    v.token_val = strdup(name);
                                                    struct entry e = create_entry(
                                                        get_line_number(),
                                                        NATURE_VAR,
                                                        variable_type,
                                                        v,
                                                        0,
                                                        NULL
                                                    );
                                                    add_entry(stack->top, &e);
                                                    free(v.token_val);
                                                }
                                                // Pra variavel global cabeca fica nula e libera TK_ID
                                                $$ = NULL;
                                                if ($2){
                                                    free($2->token_val);
                                                    free($2);
                                                }
                                            }
    ;

header
    : header_head push_table pre_param_list {    // Nova pre_param_list para facilitar
                                                char *fname = $1->label; // O label do no AST de header_head é o nome da função
                                                struct entry *func_entry = search_entry_in_stack(stack, fname);
                                                if (func_entry != NULL && func_entry->nature == NATURE_FUNC) {
                                                    func_entry->num_params = temp_param_count;
                                                    if (temp_param_count > 0) {
                                                        // Aloca memoria para os parametros na entrada da tabela de simbolos
                                                        func_entry->params = malloc(temp_param_count * sizeof(struct param_info));
                                                        if (func_entry->params == NULL) {
                                                            fprintf(stderr, "Erro ao alocar memoria para params da funcao na tabela de simbolos\n");
                                                            exit(1);
                                                        }
                                                        // Copia os parametros da lista temporaria para a entrada da tabela
                                                        memcpy(func_entry->params, temp_params, temp_param_count * sizeof(struct param_info));
                                                    } else {
                                                        func_entry->params = NULL; // Garante que é NULL se não houver parâmetros
                                                    }
                                                }
                                                $$ = $1;
                                                asd_add_child($$, $3); // Adiciona a lista de parâmetros à AST da função
                                                temp_param_count = 0; // **RESETA O CONTADOR DE PARAMETROS APÓS USAR**
                                            }
    | header_head push_table                {
                                                char *fname = $1->label;
                                                struct entry *func_entry = search_entry_in_stack(stack, fname);
                                                if (func_entry != NULL && func_entry->nature == NATURE_FUNC) {
                                                    func_entry->num_params = 0;
                                                    func_entry->params = NULL; // Não há parâmetros
                                                }
                                                $$ = $1;
                                                temp_param_count = 0; // **RESETA O CONTADOR DE PARAMETROS APÓS USAR**
                                            }
    ; 

header_head
    : TK_ID TK_PR_RETURNS tipo_funcao              {
                                                char *fname = $1->token_val;
                                                if (search_entry(stack->top, fname) != NULL){
                                                    semantic_error(ERR_DECLARED, "Identificador ja declarado neste escopo", get_line_number());
                                                } else{
                                                    valor_t v;
                                                    v.line_number = get_line_number();
                                                    v.token_type = TK_ID;
                                                    v.token_val = strdup(fname);
                                                    struct entry e = create_entry(
                                                        get_line_number(),
                                                        NATURE_FUNC,
                                                        function_type,
                                                        v,
                                                        0,
                                                        NULL
                                                    );
                                                    add_entry(stack->top, &e);
                                                    free(v.token_val);
                                                }
                                                $$ = asd_new($1->token_val, PLACEHOLDER);
                                                if($1){
                                                    free($1->token_val);
                                                    free($1);
                                                }
                                                temp_param_count = 0; // **RESETA O CONTADOR DE PARAMETROS AQUI!**
                                            }
    ;

tipo
    : TK_PR_FLOAT                           { $$ = NULL; variable_type = TYPE_FLOAT; }  // Nao precisa de nenhum nome
    | TK_PR_INT                             { $$ = NULL; variable_type = TYPE_INT; }
    ;

tipo_funcao
    : TK_PR_FLOAT                           { $$ = NULL; function_type = TYPE_FLOAT; }  // Controlar o tipo da funcao separado do tipo da variavel
    | TK_PR_INT                             { $$ = NULL; function_type = TYPE_INT; }
    ;

pre_param_list
    : TK_PR_WITH param_list                 { 
                                                if($2 != NULL){
                                                    $$ = $2;
                                                }
                                            }

param_list
    : parameter                             { $$ = $1; }    // Mesma logica do elemento/lista
    | parameter ',' param_list              { 
                                                if($3==NULL)
                                                {
                                                    $$=$1;
                                                }else{
                                                    $$ = $1;
                                                    asd_add_child($$, $3);
                                                }
                                            }
    ;

parameter
    : TK_ID TK_PR_AS tipo                   {
                                                $$ = asd_new($1->token_val, PLACEHOLDER);
                                                if($1){
                                                    free($1->token_val);
                                                    free($1);
                                                }
                                            }
    ;

body
    : command_block                         { $$ = $1; }
    ;

command_block
    : '[' push_table simple_command_list pop_table ']'           { $$ = $3; }
    ;

simple_command_list
    : /*nothingness*/                        { $$ = NULL; }
    | simple_command simple_command_list    { // Logica para cabeca e simple_command_list virar filho
                                                if($1 == NULL){
                                                    $$ = $2;
                                                }else if($2 == NULL){
                                                    $$ = $1;
                                                }else{
                                                    $$ = $1;
                                                    asd_add_child($$, $2);
                                                }
                                            }
    ;

simple_command
    : command_block                         { $$ = $1; }
    | decl_var                              { $$ = $1; }
    | attribution                           { $$ = $1; }
    | call_func                             { $$ = $1; }
    | return_command                        { $$ = $1; }
    | flow_ctrl                             { $$ = $1; }
    ;

init
    : TK_PR_WITH TK_LI_INT              {  $$ = asd_new($2->token_val, TYPE_INT);
                                            if ($2){
                                                free($2->token_val);
                                                free($2);
                                            }
                                        }
    | TK_PR_WITH TK_LI_FLOAT            {  $$ = asd_new($2->token_val, TYPE_FLOAT);
                                            if ($2){
                                                free($2->token_val);
                                                free($2);
                                            }
                                        }
    | /*nada*/                         { $$ = NULL;}
    ;

decl_var
    : TK_PR_DECLARE TK_ID TK_PR_AS tipo init {
                                                char *varname = $2->token_val;
                                                // Verificar se a variavel ja foi declarada no escopo atual
                                                if(search_entry(stack->top, varname) != NULL){
                                                    semantic_error(ERR_DECLARED, "Identificador ja declarado neste escopo", get_line_number());
                                                }
                                                if (variable_type != $5->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Tipo de variavel diferente do tipo da inicializacao", get_line_number());
                                                }
                                                valor_t v;
                                                v.line_number = get_line_number();
                                                v.token_type = TK_ID;
                                                v.token_val = strdup(varname);
                                                struct entry e = create_entry(
                                                    get_line_number(),
                                                    NATURE_VAR,
                                                    variable_type,
                                                    v,
                                                    0,
                                                    NULL
                                                );
                                                add_entry(stack->top, &e);
                                                free(v.token_val);
                                                

                                                if($5 != NULL)  //se tiver inicializacao cria no e da os filhos com o valor do ID e da init
                                                {
                                                    $$ = asd_new("with", PLACEHOLDER);
                                                    asd_add_child($$, asd_new($2->token_val, PLACEHOLDER));
                                                    asd_add_child($$, $5);
                                                }
                                                else{ $$ = NULL;}
                                                if($2){ free($2->token_val); free($2);}
                                            }
    ;

attribution
    : TK_ID TK_PR_IS expressao              {   
                                                // Verificar se a variavel foi declarada em algum escopo
                                                char *varname = $1->token_val;
                                                struct entry *e = search_entry_in_stack(stack, varname);
                                                // Por algum motivo get_line_number() nao funciona aqui
                                                // Ele devolve o numero da linha do erro + 1
                                                // ???? Sor, se o senhor ver isso e quiser deixar nos comentarios do trabalho
                                                // por que na atribuição ele da o numero da linha do erro + 1
                                                // mas nas outras produções ele da o numero certo a gente ficaria grato
                                                // É como se o yylineno identificasse o /n antes de chegar nesse bloco de código
                                                // sendo que nas outras produções ele identifica o /n depois, pelo que parece ao menos
                                                // O certo deveria ser pegar o $x->line_number quando possível em vez de get_line_number()?
                                                if(e == NULL){
                                                    semantic_error(ERR_UNDECLARED, "Identificador nao declarado", $1->line_number);
                                                }
                                                if(e->nature == NATURE_FUNC){
                                                    semantic_error(ERR_FUNCTION, "Tentativa de fazer atribuicao em funcao", $1->line_number);
                                                }
                                                if (e->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Tipo de variavel diferente do tipo da atribuicao", $1->line_number);
                                                }

                                                // Atribuitcao no is com filhos do valor do TK_ID e a expressao
                                                $$ = asd_new("is", e->type);
                                                asd_add_child($$, asd_new($1->token_val, PLACEHOLDER));
                                                asd_add_child($$, $3);
                                                if($1){
                                                    free($1->token_val);
                                                    free($1);
                                                }
                                            }
    ;

call_func
    : TK_ID '(' arg_list ')'                {   
                                                char *fname = $1->token_val;
                                                struct entry *func_entry = search_entry_in_stack(stack, fname);

                                                if (func_entry == NULL) {
                                                    semantic_error(ERR_UNDECLARED, "Identificador nao declarado", $1->line_number);
                                                    $$ = asd_new("call", PLACEHOLDER);
                                                    if ($3 != NULL) asd_add_child($$, $3); // Adiciona os argumentos mesmo com erro
                                                } else if (func_entry->nature == NATURE_VAR) {
                                                    semantic_error(ERR_VARIABLE, "Erro: variavel sendo usada como funcao", $1->line_number);
                                                    $$ = asd_new("call", PLACEHOLDER);
                                                    if ($3 != NULL) asd_add_child($$, $3);
                                                } else {
                                                    int declared_param_count = func_entry->num_params;
                                                    // O nó $3 agora é o primeiro argumento da lista (se a regra arg_list foi mudada para recursiva à esquerda)
                                                    // Ou é o nó "arg_list_head" se a regra arg_list foi mudada para a primeira sugestão.
                                                    // Considerando a segunda sugestão para arg_list (recursiva à esquerda):
                                                    asd_tree_t *first_arg_node = $3;
                                                    int actual_arg_count = 0;

                                                    // Itera pelos argumentos passados (o primeiro e seus filhos)
                                                    // Se houver $3, ele é o primeiro argumento. Seus filhos são os restantes.
                                                    if (first_arg_node != NULL) {
                                                        actual_arg_count = 1; // Contamos o primeiro argumento
                                                        // Verifica o tipo do primeiro argumento
                                                        if (actual_arg_count <= declared_param_count && func_entry->params != NULL) {
                                                            if (first_arg_node->type != func_entry->params[actual_arg_count - 1].type) {
                                                                semantic_error(ERR_WRONG_TYPE_ARGS, "Tipo de argumento incompativel na chamada da funcao", $1->line_number);
                                                            }
                                                        }

                                                        // Itera pelos filhos (os argumentos subsequentes)
                                                        for (int i = 0; i < first_arg_node->number_of_children; i++) {
                                                            actual_arg_count++;
                                                            asd_tree_t *current_arg_node = first_arg_node->children[i];

                                                            // Verifica numero excessivo de argumentos
                                                            if (actual_arg_count > declared_param_count) {
                                                                semantic_error(ERR_EXCESS_ARGS, "Numero excessivo de argumentos na chamada da funcao", $1->line_number);
                                                                break; // Já encontramos um erro de excesso, podemos parar de verificar tipos aqui
                                                            }

                                                            // Verifica compatibilidade de tipo dos argumentos
                                                            if (func_entry->params != NULL && (actual_arg_count - 1) < declared_param_count) {
                                                                if (current_arg_node->type != func_entry->params[actual_arg_count - 1].type) {
                                                                    semantic_error(ERR_WRONG_TYPE_ARGS, "Tipo de argumento incompativel na chamada da funcao", $1->line_number);
                                                                }
                                                            }
                                                        }
                                                    }


                                                    // Verifica se faltam argumentos
                                                    if (actual_arg_count < declared_param_count) {
                                                        semantic_error(ERR_MISSING_ARGS, "Numero insuficiente de argumentos na chamada da funcao", $1->line_number);
                                                    }

                                                    // Cria o nó AST para a chamada da função
                                                    char *nome_da_funcao = malloc(strlen($1->token_val) + 6);
                                                    sprintf(nome_da_funcao, "call %s", $1->token_val);
                                                    $$ = asd_new(nome_da_funcao, func_entry->type);
                                                    free(nome_da_funcao);
                                                    if ($3 != NULL) asd_add_child($$, $3); // Anexa a lista de argumentos como filho
                                                }
                                                if ($1) {
                                                    free($1->token_val);
                                                    free($1);
                                                }
                                            }
    | TK_ID '('  ')'                        {
                                                {
                                                    char *fname = $1->token_val;
                                                    struct entry *func_entry = search_entry_in_stack(stack, fname);

                                                    if (func_entry == NULL) {
                                                        semantic_error(ERR_UNDECLARED, "Identificador nao declarado", $1->line_number);
                                                        $$ = asd_new("call", PLACEHOLDER);
                                                    } else if (func_entry->nature == NATURE_VAR) {
                                                        semantic_error(ERR_VARIABLE, "Erro: variavel sendo usada como funcao", $1->line_number);
                                                        $$ = asd_new("call", PLACEHOLDER);
                                                    } else {
                                                        // Nenhuma arg_list foi fornecida, entao actual_arg_count é 0
                                                        int declared_param_count = func_entry->num_params;

                                                        // Verifica se faltam argumentos (se a funcao espera algum)
                                                        if (declared_param_count > 0) {
                                                            semantic_error(ERR_MISSING_ARGS, "Numero insuficiente de argumentos na chamada da funcao (esperado mais de 0, recebido 0)", $1->line_number);
                                                        }

                                                        char *nome_da_funcao = malloc(strlen($1->token_val) + 6);
                                                        sprintf(nome_da_funcao, "call %s", $1->token_val);
                                                        $$ = asd_new(nome_da_funcao, func_entry->type);
                                                        free(nome_da_funcao);
                                                    }
                                                    if ($1) {
                                                        free($1->token_val);
                                                        free($1);
                                                    }
                                                }
                                            }
    ;

//optional_arg_list
//    : /*vazio*/                             { $$ = NULL; }
//    | arg_list                              { $$ = $1; }
//    ;

arg_list
    : expressao                             { $$ = $1; }
    | expressao ',' arg_list                {
                                                 // Adiciona a nova expressão como filho da arg_list existente
                                                asd_tree_t *current_list_head = $1;
                                                asd_add_child(current_list_head, $3); // $3 é a nova expressao
                                                $$ = current_list_head;
                                            }
    ;

return_command
    : TK_PR_RETURN expressao TK_PR_AS tipo  {   
                                                // Verificar se a funcao e o retorno tem o mesmo tipo
                                                if (function_type != variable_type){
                                                    semantic_error(ERR_WRONG_TYPE, "Tipo de retorno diferente do tipo da funcao", get_line_number());
                                                }
                                                // Verificar se a funcao e a expressao tem o mesmo tipo
                                                if (function_type != $2->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Tipo expressao retornada diferente do tipo da funcao", get_line_number());
                                                }
        
                                                //No return cujo filho e a expressao
                                                $$ = asd_new("return", function_type);
                                                asd_add_child($$, $2);
                                            }
    ;

flow_ctrl
    : conditional                           { $$ = $1; }
    | while                                 { $$ = $1; }
    ;

conditional
    : TK_PR_IF '(' expressao ')' command_block                              {   // Sem else
                                                                                $$ = asd_new("if", $3->type);
                                                                                if($3!=NULL){
                                                                                    asd_add_child($$, $3);
                                                                                }
                                                                                if($5 != NULL){
                                                                                    asd_add_child($$, $5); 
                                                                                }
                                                                                //if ($6) asd_add_child($$, $6);
                                                                            }
    | TK_PR_IF '(' expressao ')' command_block TK_PR_ELSE command_block     {   
                                                                                // Tipo dos dois blocos deve ser igual
                                                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                                                if($5->type != $7->type){
                                                                                    semantic_error(ERR_WRONG_TYPE, "Erro: tipo do bloco 'if' diferente do bloco 'else'", get_line_number());
                                                                                }
        
        
        
                                                                                // Com else command_block vira filho
                                                                                $$ = asd_new("if", $3->type);
                                                                                if($3!=NULL){
                                                                                    asd_add_child($$, $3);
                                                                                }
                                                                                if($5 != NULL){
                                                                                    asd_add_child($$, $5); 
                                                                                }
                                                                                if ($7 != NULL) asd_add_child($$, $7);
                                                                            }
    ;

while
    : TK_PR_WHILE '(' expressao ')' command_block               {
                                                                    $$ = asd_new("while", $3->type);
                                                                    if($3!=NULL){
                                                                        asd_add_child($$, $3);
                                                                    }
                                                                    if($5 != NULL){
                                                                        asd_add_child($$, $5); 
                                                                    }
                                                                }
    ;

expressao
    : n7                                    { $$ = $1; }
    ;

n7
    : n7 '|' n6                             {   
                                                // Verifica se os tipos sao iguais
                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: operacao '|' entre tipos incompativeis", get_line_number());
                                                }
        
                                                $$ = asd_new("|", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n6                                    { $$ = $1; }
    ;

n6
    : n6 '&' n5                             {   
                                                // Verifica se os tipos sao iguais
                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: operacao '&' entre tipos incompativeis", get_line_number());
                                                }
        
                                                $$ = asd_new("&", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n5                                    { $$ = $1; }
    ;

n5
    : n5 TK_OC_EQ n4                        {   
                                                // Verifica se os tipos sao iguais
                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '==' entre tipos incompativeis", get_line_number());
                                                }
        
                                                $$ = asd_new("==", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n5 TK_OC_NE n4                        {   
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '!=' entre tipos incompativeis", get_line_number());
                                                }
        
                                                $$ = asd_new("!=", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n4                                    { $$ = $1; }
    ;

n4
    : n4 '<' n3                             {   
                                                // Verifica se os tipos sao iguais
                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '<' entre tipos incompativeis", get_line_number());
                                                }
        
                                                $$ = asd_new("<", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n4 '>' n3                             {   
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '>' entre tipos incompativeis", get_line_number());
                                                }
        
                                                $$ = asd_new(">", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n4 TK_OC_LE n3                        {   
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '<=' entre tipos incompativeis", get_line_number());
                                                }
        
                                                $$ = asd_new("<=", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n4 TK_OC_GE n3                        {   
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '>=' entre tipos incompativeis", get_line_number());
                                                }
        
                                                $$ = asd_new(">=", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n3                                    { $$ = $1; }
    ;

n3
    : n3 '+' n2                             {   
                                                // Verifica se os tipos sao iguais
                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: soma entre tipos incompativeis", get_line_number());
                                                }

                                                $$ = asd_new("+", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n3 '-' n2                             {   
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: subtracao entre tipos incompativeis", get_line_number());
                                                }
        
                                                $$ = asd_new("-", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n2                                    { $$ = $1; }
    ;

n2
    : n2 '*' n1                             {   // Verifica se os tipos sao iguais
                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: multiplicacao entre tipos incompativeis", get_line_number());
                                                }

                                                $$ = asd_new("*", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n2 '/' n1                             {   
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: divisao entre tipos incompativeis", get_line_number());
                                                }
        
                                                $$ = asd_new("/", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n2 '%' n1                             {   
                                                if($1->type != $3->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: modulo entre tipos incompativeis", get_line_number());
                                                }
        
                                                $$ = asd_new("%", $1->type);
                                                asd_add_child($$, $1);
                                                asd_add_child($$, $3);
                                            }
    | n1                                    { $$ = $1; }
    ;

n1
    : '+' n1                                { $$ = asd_new("+", $2->type); asd_add_child($$, $2); }
    | '-' n1                                { $$ = asd_new("-", $2->type); asd_add_child($$, $2); }
    | '!' n1                                { $$ = asd_new("!", $2->type); asd_add_child($$, $2); }
    | n0                                    { $$ = $1; }
    ;

n0
    : TK_ID                                 {
                                                // Verificar se a variavel foi declarada em algum escopo
                                                char *varname = $1->token_val;
                                                struct entry *e = search_entry_in_stack(stack, varname);
                                                if (e == NULL){
                                                    semantic_error(ERR_UNDECLARED, "Identificador nao declarado", $1->line_number);
                                                }
                                                if (e->nature == NATURE_FUNC){
                                                    semantic_error(ERR_FUNCTION, "Erro: funcao sendo usada como variavel", $1->line_number);
                                                }
                                                $$ = asd_new($1->token_val, e->type);
                                                if($1){
                                                    free($1->token_val); 
                                                    free($1);
                                                }
                                            }
    | TK_LI_INT                             {
                                                $$ = asd_new($1->token_val, TYPE_INT);
                                                if($1){
                                                    free($1->token_val); 
                                                    free($1);
                                                }
                                            }
    | TK_LI_FLOAT                           {
                                                $$ = asd_new($1->token_val, TYPE_FLOAT);
                                                if($1){
                                                    free($1->token_val); 
                                                    free($1);
                                                }
                                            }
    | call_func                             { $$ = $1; }
    | '(' expressao ')'                     { $$ = $2; }
    ;

push_table:                                    {
                                                // Criar tabela
                                                struct table *table = create_table();
                                                // Colocar tabela na pilha
                                                push_table_stack(&stack, table);
                                                $$ = NULL;
                                            }

pop_table:                                 {
                                                // Tirar tabela do topo da pilha
                                                pop_table_stack(&stack);
                                                $$ = NULL;
                                            }

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Erro sintático na linha %d: %s\n", get_line_number(), msg);
}