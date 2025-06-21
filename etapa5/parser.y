%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "asd.h"
    //#include "lexical_value.h"    /* struct valor_t */

    extern asd_tree_t *arvore;  /* raiz da AST */
    extern int yylex(void);     /* corrigir erro zoado*/
    int get_line_number(void);
    void yyerror (const char *mensagem);
    typedef struct {
        int    line_number;
        int    token_type;
        char  *token_val;
    } valor_t;
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

%%

programa
    : /*vazio*/                             { $$ = NULL; arvore = $$; } // Inicio da arvore
    | lista ';'                             { $$ = $1; arvore = $$; }
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
    : header TK_PR_IS body                   { // No com a label do header. Body vira filho
                                        $$ = asd_new($1->label);
                                        if ($3 != NULL){
                                            asd_add_child($$, $3);
                                        }
                                        asd_free($1);
                                    }
    ;

decl_var_global
    : TK_PR_DECLARE TK_ID TK_PR_AS tipo     {   // Pra variavel global cabeca fica nula e libera TK_ID
                                                $$ = NULL;
                                                if ($2){
                                                    free($2->token_val);
                                                    free($2);
                                                }
                                            }
    ;

header
    : header_head pre_param_list   {    // Nova pre_param_list para facilitar
                                            $$ = $1;
                                            asd_add_child($$, $2);
                                        }
    | header_head                       { $$ = $1; }
    ; 

header_head
    : TK_ID TK_PR_RETURNS tipo              {
                                                $$ = asd_new($1->token_val);
                                                if($1){
                                                    free($1->token_val);
                                                    free($1);
                                                }
                                            }
    ;

tipo
    : TK_PR_FLOAT                           { /*$$ = asd_new("float");*/ }  // Nao precisa de nenhum nome
    | TK_PR_INT                             { /*$$ = asd_new("int");*/ }
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
                                                $$ = asd_new($1->token_val);
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
    : '[' simple_command_list ']'           { $$ = $2; }
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
    : TK_PR_WITH TK_LI_INT              {  $$ = asd_new($2->token_val); // No com o valor do TK_LI_*
                                            if ($2){
                                                free($2->token_val);
                                                free($2);
                                            }
                                        }
    | TK_PR_WITH TK_LI_FLOAT            {  $$ = asd_new($2->token_val);
                                            if ($2){
                                                free($2->token_val);
                                                free($2);
                                            }
                                        }
    | /*nada*/                         { $$ = NULL;}
    ;

decl_var
    : TK_PR_DECLARE TK_ID TK_PR_AS tipo init {
                                                if($5 != NULL)  //se tiver inicializacao cria no e da os filhos com o valor do ID e da init
                                                {
                                                    $$ = asd_new("with");
                                                    asd_add_child($$, asd_new($2->token_val));
                                                    asd_add_child($$, $5);
                                                }
                                                else{ $$ = NULL;}
                                                if($2){ free($2->token_val); free($2);}
                                            }
    ;

attribution
    : TK_ID TK_PR_IS expressao              {   // Atribuitcao no is com filhos do valor do TK_ID e a expressao
                                                $$ = asd_new("is");
                                                asd_add_child($$, asd_new($1->token_val));
                                                asd_add_child($$, $3);
                                                if($1){
                                                    free($1->token_val);
                                                    free($1);
                                                }
                                            }
    ;

call_func
    : TK_ID '(' arg_list ')'                {   // No com o nome da funcao e filho arg_list se houver
                                                char *nome_da_funcao = malloc(strlen($1->token_val) + 6);
                                                sprintf(nome_da_funcao, "call %s", $1->token_val);
                                                $$ = asd_new(nome_da_funcao);
                                                free(nome_da_funcao);
                                                asd_add_child($$, $3);
                                                if($1){
                                                    free($1->token_val);
                                                    free($1);
                                                };
                                            }
    | TK_ID '('  ')'                        {
                                                char *nome_da_funcao = malloc(strlen($1->token_val) + 6);
                                                sprintf(nome_da_funcao, "call %s", $1->token_val);
                                                $$ = asd_new(nome_da_funcao);
                                                free(nome_da_funcao);
                                                if($1){
                                                    free($1->token_val);
                                                    free($1);
                                                };
                                            }
    ;

//optional_arg_list
//    : /*vazio*/                             { $$ = NULL; }
//    | arg_list                              { $$ = $1; }
//    ;

arg_list
    : expressao                             { $$ = $1; }
    | expressao ',' arg_list                {
                                                if($3==NULL)
                                                {
                                                    $$ = $1;
                                                }else{
                                                    $$ = $1;
                                                    asd_add_child($$, $3);
                                                }
                                            }
    ;

return_command
    : TK_PR_RETURN expressao TK_PR_AS tipo  {   //No return cujo filho e a expressao
                                                $$ = asd_new("return");
                                                asd_add_child($$, $2);
                                            }
    ;

flow_ctrl
    : conditional                           { $$ = $1; }
    | while                                 { $$ = $1; }
    ;

conditional
    : TK_PR_IF '(' expressao ')' command_block                              {   // Sem else
                                                                                $$ = asd_new("if");
                                                                                if($3!=NULL){
                                                                                    asd_add_child($$, $3);
                                                                                }
                                                                                if($5 != NULL){
                                                                                    asd_add_child($$, $5); 
                                                                                }
                                                                                //if ($6) asd_add_child($$, $6);
                                                                            }
    | TK_PR_IF '(' expressao ')' command_block TK_PR_ELSE command_block     {   // Com else command_block vira filho
                                                                                $$ = asd_new("if");
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
                                                                    $$ = asd_new("while");
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
    : n7 '|' n6                             { $$ = asd_new("|"); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n6                                    { $$ = $1; }
    ;

n6
    : n6 '&' n5                             { $$ = asd_new("&"); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n5                                    { $$ = $1; }
    ;

n5
    : n5 TK_OC_EQ n4                        { $$ = asd_new("=="); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n5 TK_OC_NE n4                        { $$ = asd_new("!="); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n4                                    { $$ = $1; }
    ;

n4
    : n4 '<' n3                             { $$ = asd_new("<"); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n4 '>' n3                             { $$ = asd_new(">"); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n4 TK_OC_LE n3                        { $$ = asd_new("<="); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n4 TK_OC_GE n3                        { $$ = asd_new(">="); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n3                                    { $$ = $1; }
    ;

n3
    : n3 '+' n2                             { $$ = asd_new("+"); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n3 '-' n2                             { $$ = asd_new("-"); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n2                                    { $$ = $1; }
    ;

n2
    : n2 '*' n1                             { $$ = asd_new("*"); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n2 '/' n1                             { $$ = asd_new("/"); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n2 '%' n1                             { $$ = asd_new("%"); asd_add_child($$, $1); asd_add_child($$, $3); }
    | n1                                    { $$ = $1; }
    ;

n1
    : '+' n1                                { $$ = asd_new("+"); asd_add_child($$, $2); }
    | '-' n1                                { $$ = asd_new("-"); asd_add_child($$, $2); }
    | '!' n1                                { $$ = asd_new("!"); asd_add_child($$, $2); }
    | n0                                    { $$ = $1; }
    ;

n0
    : TK_ID                                 { 
                                                $$ = asd_new($1->token_val);
                                                if($1){
                                                    free($1->token_val); 
                                                    free($1);
                                                }
                                            }
    | TK_LI_INT                             {
                                                $$ = asd_new($1->token_val);
                                                if($1){
                                                    free($1->token_val); 
                                                    free($1);
                                                }
                                            }
    | TK_LI_FLOAT                           {
                                                $$ = asd_new($1->token_val);
                                                if($1){
                                                    free($1->token_val); 
                                                    free($1);
                                                }
                                            }
    | call_func                             { $$ = $1; }
    | '(' expressao ')'                     { $$ = $2; }
    ;

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Erro sintático na linha %d: %s\n", get_line_number(), msg);
}